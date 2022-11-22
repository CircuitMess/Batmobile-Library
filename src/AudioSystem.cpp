#include "AudioSystem.h"
#include <SPIFFS.h>
#include "Pins.hpp"

AudioSystem::AudioSystem() : task("Playback", [](Task* task){
	auto system = static_cast<AudioSystem*>(task->arg);
	system->player();
}, 4096, this), output(PIN_SPKR, PIN_SPKR_EN), playQueue(4, sizeof(PlayJob)){

	output.setSource(source);
}

AudioSystem::~AudioSystem(){
	stop();
}

void AudioSystem::begin(){
	if(task.running) return;

	task.start(1, 0);
}

void AudioSystem::stop(){
	task.stop(true);
	delete source;
	delete dataSource;
}

void AudioSystem::play(File file){
	FileDataSource* dataSource = new FileDataSource(file);
	SourceAAC* source = new SourceAAC(*dataSource);

	PlayJob job = { dataSource, source };
	playQueue.send(&job);

	running = true;
}

void AudioSystem::player(){
	while(task.running){
		while(playQueue.count()){
			PlayJob next;
			if(!playQueue.receive(&next)) continue;

			if(source){
				source->close();
			}

			delete source;
			delete dataSource;

			dataSource = next.dataSource;
			source = next.source;

			output.setSource(source);
			output.start();
		}

		bool wasRunning = output.isRunning();
		output.loop(0);
		if(wasRunning && !output.isRunning()){
			running = false;
		}
	}
}

void AudioSystem::setVolume(uint8_t volume){
	output.setGain((float) volume / 255.0f);
}

bool AudioSystem::isPlaying(){
	return running;
}
