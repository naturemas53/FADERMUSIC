#include "SongPlayState.h"
#include "LevelState.h"
#include "HighSpeedState.h"
#include "../CONTROLL.h"

void SongPlayState::AlphaRead(){

	this->alpha_ = GraphicsDevice.CreateSpriteFromFile(_T("musicselect/menu/menu_PLAY.png"));

}

void SongPlayState::ClassUpdate(float mouseheight, Context* context){

	if (this->desidenum_)return;
	if (this->datamanager_ == nullptr) return;

	if (mouseheight < (1.0f / 3.0f)){

		context->SetState(&LEVELSTATE);
		return;

	}
	if (mouseheight > (1.0f / 3.0f) * 2.0f){

		context->SetState(&HIGHSPEEDSTATE);
		return;

	}

	if (CONTROLL::GetInstance().BufferIsPress(LEFT)){

		this->datamanager_->MoveIncrement();
		return;
	}

	if (CONTROLL::GetInstance().BufferIsPress(CENTER)){

		this->desidenum_ = 1;
		return;
	}

	if (CONTROLL::GetInstance().BufferIsPress(RIGHT)){

		this->datamanager_->MoveDecrement();
		return;
	}

}

void SongPlayState::ClassDraw(){



}