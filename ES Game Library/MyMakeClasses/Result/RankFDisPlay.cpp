#include "RankFDisPlay.h"

RankFDisplay::RankFDisplay() : AbstructRankDisplay(Vector2(276.0f, 320.0f)),
STARTPOS_(Vector3(1280, 360.0f, 0.0f)),
MOVETIME_(150){

	this->ranksprite_ = GraphicsDevice.CreateSpriteFromFile(_T("result/rank/result_rank_F.png"));

	this->sound_ = nullptr;

	this->time_ = 0;

}

RankFDisplay::~RankFDisplay(){

	GraphicsDevice.ReleaseSprite(this->ranksprite_);

}

int RankFDisplay::Update(int elapsedtime){

	switch (this->state_){

	case AbstructRankDisplay::EFFECT:

		this->time_ += elapsedtime;

		if (this->time_ > this->MOVETIME_){

			this->time_ = 0;
			this->state_ = AbstructRankDisplay::STOP;

		}

		break;

	case AbstructRankDisplay::STOP:

		return 1;

		break;

	default:

		break;
	}

	return 0;

}

void RankFDisplay::Draw(){

	Vector3 pos = Vector3_Zero;

	float alpha = 1.0f;
	if (this->state_ == AbstructRankDisplay::EFFECT){

		float timerate = (float)this->time_ / (float)this->MOVETIME_;

		alpha = timerate;

	}
	else{

		alpha = 1.0f;

	}

	if (this->state_ == AbstructRankDisplay::WAIT){

		alpha = 0.0f;

	}

	SPRITE sp = this->ranksprite_;

	Color color = Color(1.0f, 1.0f, 1.0f, alpha);

	SpriteBatch.Begin();
	SpriteBatch.Draw(*sp, this->POS_, color);
	SpriteBatch.End();

}

void RankFDisplay::Skip(){

	this->AbstructRankDisplay::Skip();

	this->time_ = 0;
}