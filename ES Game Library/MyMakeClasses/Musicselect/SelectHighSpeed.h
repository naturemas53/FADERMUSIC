#pragma once
#include "../../ESGLib.h"

class SelectHighSpeed{

public:

	SelectHighSpeed();
	~SelectHighSpeed();

	void Draw();

	void PlusCount();
	void MinusCount();

	int GetSpeedCount(){ return this->speedcount_; }

private:

	SPRITE sprite_;

	int speedcount_;

	SOUND plussound_;
	SOUND minussound_;

};