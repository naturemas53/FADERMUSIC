#include "SelectSceneState.h"

SPRITE SelectSceneState::sprite_ = nullptr;

SelectSceneState::SelectSceneState(){

	if (this->sprite_ == nullptr){
		this->sprite_ = GraphicsDevice.CreateSpriteFromFile(_T("musicselect/menu/menu.png"));
	}
	this->time_ = 0;
	this->state_ = SelectSceneState::ON;
	this->desidenum_ = 0;
}

SelectSceneState::~SelectSceneState(){

	if (this->sprite_ != nullptr){

		//GraphicsDevice.ReleaseSprite(this->sprite_);
		this->sprite_ = nullptr;

	}

	//GraphicsDevice.ReleaseSprite(this->alpha_);

}

void SelectSceneState::Update(float mouseheight, int elapsedtime, Context* context){

	switch (this->state_){

	case SelectSceneState::ON:
		this->time_ += elapsedtime;

		if (this->time_ > this->RIGHTTIME_){

			this->time_ -= (this->time_ - this->RIGHTTIME_);
			this->state_ = SelectSceneState::OFF;

		}

		break;

	case SelectSceneState::OFF:
		this->time_ -= elapsedtime;

		if (this->time_ < 0){

			this->time_ *= -1;
			this->state_ = SelectSceneState::ON;

		}
		break;

	}

	this->ClassUpdate(mouseheight,context);

}

void SelectSceneState::Draw(){

	SPRITE sp = this->sprite_;
	Vector3 pos = Vector3_Zero;
	pos.x = 1280.0f - 100.0f; //100 ‚Í‰æ‘œ‚Ì‰¡•
	pos.y = 100.0f;

	SpriteBatch.Begin();
	SpriteBatch.Draw(*sp,pos);
	SpriteBatch.End();

	float timerate = (float) this->time_ / (float)this->RIGHTTIME_;

	GraphicsDevice.SetBlendMode(DXGBLEND_ADD);
	SpriteBatch.Begin();
	SpriteBatch.Draw(*this->alpha_, pos, Color(1.0f,1.0f,1.0f,timerate));
	SpriteBatch.End();
	GraphicsDevice.SetBlendMode(DXGBLEND_NORMAL);

	this->ClassDraw();

}