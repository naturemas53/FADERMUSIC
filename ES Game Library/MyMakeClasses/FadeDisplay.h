#pragma once
#include "../ESGLib.h"

class FadeDisplay{

public:

	enum FADESTATE{

		FADEIN,
		FADEOUT

	};

	FadeDisplay(FADESTATE startstate = FADEIN);
	~FadeDisplay();

	int Update();
	void Draw();

	void SetFadeState(FADESTATE state){
	
		this->fadestate_ = state;

		switch (this->fadestate_){

		case FADEIN:

			this->count_ = this->MAXCOUNT_;

			break;

		case FADEOUT:

			this->count_ = 0;

			break;

		default:
			break;


		}
	
	}

	void Skip(){

		switch (this->fadestate_){

		case FADEIN:

			this->count_ = 0;

			break;

		case FADEOUT:

			this->count_ = this->MAXCOUNT_;

			break;

		default:
			break;


		}

	}

private:


	const int MAXCOUNT_;

	RENDERTARGET blackscreen_;
	//float alpha_;

	int count_;
	FADESTATE fadestate_;


};