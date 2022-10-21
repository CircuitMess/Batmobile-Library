#ifndef BATMOBILE_LIBRARY_COMLISTENER_H
#define BATMOBILE_LIBRARY_COMLISTENER_H


class ComListener {
public:
	virtual void onBallHue();
	virtual void onBoost();
	virtual void onDriveDir();
	virtual void onDriveMode();
	virtual void onDriveSpeed();
	virtual void onHonk();
	virtual void onVolume();
};


#endif //BATMOBILE_LIBRARY_COMLISTENER_H
