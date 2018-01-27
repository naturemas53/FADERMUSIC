#pragma once
#include "../ESGLib.h"

class HIGHSPEED{

public:

	HIGHSPEED(int startspeedcount = 0) :
		CHANGETIME_(300){

		this->chenge_flag_ = false;

		this->nowspeedcount = startspeedcount;

		this->now_speed_ = this->HighSpeedCalclation();
		this->target_speed_ = this->now_speed_;
		this->dir_speed_ = 0.0f;

		this->remaincount_ = 0;

	}

	~HIGHSPEED() = default;

	void HighSpeedUpdate(int elapsedtime){
	
		if (this->chenge_flag_){

			this->remaincount_ -= elapsedtime;

			if (this->remaincount_ < 0){

				this->chenge_flag_ = false;
				this->now_speed_ = this->target_speed_;
				return;

			}

			float rate = (float)elapsedtime / (float)this->CHANGETIME_;
			float movement = rate * this->dir_speed_;

			this->now_speed_ += movement;

		}
	
	};

	void ChengeHighSpeed(LONG ScrollWheelValue){

		this->chenge_flag_ = true;

		this->nowspeedcount += ScrollWheelValue / 120;

		this->target_speed_ = this->HighSpeedCalclation();
		this->dir_speed_ = this->target_speed_ - this->now_speed_;

		this->remaincount_ = this->CHANGETIME_;

	};

	float GetHighSpeed(){ return this->now_speed_; }

private:

	float HighSpeedCalclation(){

		float speedrate;

		if (this->nowspeedcount < 0){
			
			if (this->nowspeedcount < -8) this->nowspeedcount = -8;

			int speedcount = -this->nowspeedcount;

			speedrate = 1.0f + ((float)speedcount * 0.5f);

		}
		else if (this->nowspeedcount > 0){

			if (this->nowspeedcount > 8)this->nowspeedcount = 8;

			speedrate = 1.0f / ((float)this->nowspeedcount * 2.0f);

		}
		else{

			speedrate = 1.0f;

		}

		float highspeed = 0.25f * speedrate;

		if (highspeed <= 0.0f) highspeed = 0.000001f;
		if (highspeed >= 1.0f) highspeed = 0.999999f;

		return highspeed; 

	}

	const int CHANGETIME_;

	int nowspeedcount;
	bool chenge_flag_;
	float target_speed_;
	float now_speed_;
	float dir_speed_;
	int remaincount_;

};