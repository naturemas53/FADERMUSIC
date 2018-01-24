#pragma once
#include "../ESGLib.h"

class HIGHSPEED{

public:

	HIGHSPEED(int startspeedcount) :
		CHANGETIME_(500){

		this->chenge_flag_ = false;

		this->nowspeedcount = startspeedcount;

		this->start_speed_ = this->HighSpeedCalclation();
		this->target_speed_ = this->start_speed_;

	}

	~HIGHSPEED();

	float HighSpeedUpdate(unsigned elapsedtime){
	
		if (this->chenge_flag_){



		}
	
	};

	void ChengeHighSpeed(LONG ScrollWheelValue);

private:

	float HighSpeedCalclation(){

		float speedrate;

		if (this->nowspeedcount < 0){



		}
		else if (this->nowspeedcount > 0){


		}
		else{

			speedrate = 1.0f;

		}

		return 0.5f * speedrate;

	}

	const unsigned CHANGETIME_;

	int nowspeedcount;
	bool chenge_flag_;
	float target_speed_;
	float start_speed_;

};