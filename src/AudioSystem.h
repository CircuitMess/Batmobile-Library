#ifndef SYNTHIA_FIRMWARE_SIMPLEPLAYBACKSYSTEM_H
#define SYNTHIA_FIRMWARE_SIMPLEPLAYBACKSYSTEM_H

#include <Util/Task.h>
#include <Sync/Queue.h>
#include <Audio/OutputDAC.h>
#include <Audio/SourceAAC.h>
#include <Data/FileDataSource.h>

class AudioSystem {
public:
	AudioSystem();
	virtual ~AudioSystem();

	void begin();

	void play(File file);
	void stop();

	void setVolume(uint8_t volume);

	bool isPlaying();

private:
	OutputDAC output;

	FileDataSource* dataSource = nullptr;
	SourceAAC* source = nullptr;

	Task task;

	struct PlayJob {
		FileDataSource* dataSource;
		SourceAAC* source;
	};
	Queue playQueue;

	void player();

	bool running = false;

};

#endif //SYNTHIA_FIRMWARE_SIMPLEPLAYBACKSYSTEM_H
