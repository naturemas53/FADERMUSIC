#include "RankDDisplay.h"

RankDDisplay::RankDDisplay() :AbstructRankDisplay(Vector2(276.0f, 320.0f), Vector3(860.0f, 360.0f, 0.0f)),
STARTPOS_(Vector3(1280, 360.0f, 0.0f)),
MOVETIME_(150){

	this->ranksprite_ = GraphicsDevice.CreateSpriteFromFile(_T("result/rank/result_rank_D.png"));

	this->time_ = 0;

}

RankDDisplay::~RankDDisplay(){

	GraphicsDevice.ReleaseSprite(this->ranksprite_);

}

int RankDDisplay::Update(int elapsedtime){

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

void RankDDisplay::Draw(){

	Vector3 pos = Vector3_Zero;

	if (this->state_ == AbstructRankDisplay::EFFECT){

		Vector3 dir = this->POS_ - this->STARTPOS_;
		float timerate = (float)this->time_ / (float)this->MOVETIME_;

		pos = this->STARTPOS_ + (dir * timerate);

	}
	else{

		pos = this->POS_;

	}

	float alpha = 1.0f;
	if (this->state_ == AbstructRankDisplay::WAIT){

		alpha = 0.0f;

	}

	SPRITE sp = this->ranksprite_;

	Color color = Color(1.0f, 1.0f, 1.0f, alpha);

	SpriteBatch.Begin();
	SpriteBatch.Draw(*sp, pos, color);
	SpriteBatch.End();

}

void RankDDisplay::Skip(){

	this->AbstructRankDisplay::Skip();

	this->time_ = 0;
}