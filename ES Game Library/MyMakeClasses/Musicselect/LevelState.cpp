#include "LevelState.h"
#include "SongPlayState.h"
#include "../CONTROLL.h"

void LevelState::AlphaRead(){

	this->alpha_ = GraphicsDevice.CreateSpriteFromFile(_T("musicselect/menu/menu_DIFFICLTY.png"));

}

void LevelState::ClassUpdate(float mouseheight, Context* context){

	if (this->levelmanager_ == nullptr)return;

	if (mouseheight > (1.0f / 3.0f)){

		context->SetState(&PLAYSTATE);
		return;

	}

	if (CONTROLL::GetInstance().BufferIsPress(LEFT)){

		this->levelmanager_->SetLevel(LO);

	}

	if (CONTROLL::GetInstance().BufferIsPress(CENTER)){
		this->levelmanager_->SetLevel(MID);

	}

	if (CONTROLL::GetInstance().BufferIsPress(RIGHT)){
		this->levelmanager_->SetLevel(HIGH);

	}

}

void LevelState::ClassDraw(){



}