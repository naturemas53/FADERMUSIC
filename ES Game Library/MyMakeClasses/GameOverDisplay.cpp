#include "GameOverDisplay.h"

GameOverDisplay::GameOverDisplay():
STATETIME_(250){

	this->sprite_ = GraphicsDevice.CreateSpriteFromFile(_T("GAMEOVER.png"));
	this->sound_ = SoundDevice.CreateSoundFromFile(_T("gameover.wav"));
	this->state_ = GameOverDisplay::WAIT;
	this->time_ = 0;

}

GameOverDisplay::~GameOverDisplay(){

	GraphicsDevice.ReleaseSprite(this->sprite_);
	SoundDevice.ReleaseSound(this->sound_);

}

int GameOverDisplay::Update(int elapsedtime){

	switch (this->state_){

	case GameOverDisplay::MOVEDOWN:

		this->time_ += elapsedtime;
		if (this->time_ > this->STATETIME_){

			this->time_ -= this->STATETIME_;
			this->state_ = GameOverDisplay::SCALEUP;
			this->sound_->Play();

		}

		break;

	case GameOverDisplay::SCALEUP:

		this->time_ += elapsedtime;
		if (this->time_ > this->STATETIME_){

			this->time_ = this->STATETIME_;
			return 1;

		}

		break;

	default:
			break;

	}

	return 0;

}

void GameOverDisplay::Draw(){

	Vector3 pos = Vector3_Zero;
	float scale = 1.0f;
	float timerate = (float) this->time_ / (float) this->STATETIME_;

	switch (this->state_){

	case GameOverDisplay::WAIT:
		pos.y = -1280.0f;
		break;

	case GameOverDisplay::MOVEDOWN:

		pos.y = -720.0f * (1.0f - timerate);

		break;

	case GameOverDisplay::SCALEUP:

		scale += timerate;

		break;

	}

	SpriteBatch.Begin();

	SpriteBatch.Draw(*this->sprite_,pos,Color(255,255,255));

	if (this->state_ == GameOverDisplay::SCALEUP){

		SpriteBatch.Draw(*this->sprite_, pos,Color(1.0f,1.0f,1.0f,(1.0f - timerate)),Vector3_Zero,
			Vector3(1280.0f / 2.0f,720.0f / 2.0f,0.0f),scale);

	}

	SpriteBatch.End();

}