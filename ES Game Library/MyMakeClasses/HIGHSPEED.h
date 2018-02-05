#pragma once
#include "../ESGLib.h"
#include "ImageFont.h"

class HIGHSPEED{

public:

	HIGHSPEED(int startspeedcount = 0) :
		CHANGETIME_(100){

		this->chenge_flag_ = false;

		this->nowspeedcount_ = startspeedcount;

		this->now_speed_ = this->HighSpeedCalclation();
		this->target_speed_ = this->now_speed_;
		this->dir_speed_ = 0.0f;

		this->remaincount_ = 0;

		this->color_ = Color(1.0f, 1.0f, 1.0f);
	}

	~HIGHSPEED() = default;

	void HighSpeedUpdate(int elapsedtime){
	
		if (this->chenge_flag_){

			this->remaincount_ -= elapsedtime;

			if (this->remaincount_ < 0){

				this->chenge_flag_ = false;
				this->now_speed_ = this->target_speed_;
				this->color_ = Color(1.0f, 1.0f, 1.0f);
				return;

			}

			float rate = (float)elapsedtime / (float)this->CHANGETIME_;
			float movement = rate * this->dir_speed_;

			this->now_speed_ += movement;

			float pluspal = rate * 0.5f;
			this->color_ = this->color_ + Color(pluspal,pluspal,pluspal);

		}
	
	};

	void ChengeHighSpeed(LONG ScrollWheelValue){

		this->chenge_flag_ = true;

		if (ScrollWheelValue < 0){

			this->color_ = Color(0.5f,0.5f,1.0f);

		}
		else{
			this->color_ = Color(1.0f, 0.5f, 0.5f);
		}

		this->nowspeedcount_ += ScrollWheelValue / 120;

		this->target_speed_ = this->HighSpeedCalclation();
		this->dir_speed_ = this->target_speed_ - this->now_speed_;

		this->remaincount_ = this->CHANGETIME_;

	};

	void Draw(){

		Vector2 drawsize;
		Vector2 smollcellsize = IMAGEFONT.GetCellSize() / 4.0f;
		drawsize = IMAGEFONT.GetDrawSize(smollcellsize, "HIGHSPEED %d", this->nowspeedcount_);
		IMAGEFONT.SetImageString(Vector3(1280.0f - drawsize.x, 72.0f, 0.0f), smollcellsize, this->color_, true, "HIGHSPEED %d", this->nowspeedcount_);

	}

	float GetHighSpeed(){ return this->now_speed_; }

private:

	float HighSpeedCalclation(){

		float speedrate;

		if (this->nowspeedcount_ < 0){
			
			if (this->nowspeedcount_ < -8) this->nowspeedcount_ = -8;

			int speedcount = -this->nowspeedcount_;

			speedrate = 1.0f + ((float)speedcount * 0.5f);

			this->color_ = Color(0.5f,0.5f,1.0f);

		}
		else if (this->nowspeedcount_ > 0){

			if (this->nowspeedcount_ > 8)this->nowspeedcount_ = 8;

			speedrate = 1.0f / ((float)this->nowspeedcount_ * 2.0f);

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

	int nowspeedcount_;
	bool chenge_flag_;
	float target_speed_;
	float now_speed_;
	float dir_speed_;
	int remaincount_;
	Color color_;

};