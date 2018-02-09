#include "HighSpeedState.h"
#include "SongPlayState.h"
#include "../CONTROLL.h"

void HighSpeedState::AlphaRead(){

	this->alpha_ = GraphicsDevice.CreateSpriteFromFile(_T("musicselect/menu/menu_HIGHSPEED.png"));

}

void HighSpeedState::ClassUpdate(float mouseheight, Context* context){

	if (this->highspeed_ == nullptr) return;
	if (mouseheight < (1.0f / 3.0f) * 2.0f){

		context->SetState(&PLAYSTATE);
		return;
	}

	if (CONTROLL::GetInstance().BufferIsPress(LEFT)){

		this->highspeed_->MinusCount();

	}

	if (CONTROLL::GetInstance().BufferIsPress(CENTER)){

		//‚È‚µ

	}

	if (CONTROLL::GetInstance().BufferIsPress(RIGHT)){

		this->highspeed_->PlusCount();

	}

}

void HighSpeedState::ClassDraw(){



}