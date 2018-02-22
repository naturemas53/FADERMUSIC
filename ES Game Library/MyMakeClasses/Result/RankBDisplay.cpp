#include "RankBDisplay.h"

RankBDisplay::RankBDisplay() :AbstructRankDisplay(Vector2(252.0f, 320.0f), Vector3(870.0f, 360.0f, 0.0f)),
STARTPOS_(Vector3(1280, 360.0f, 0.0f)),
MOVETIME_(150){

	this->ranksprite_ = GraphicsDevice.CreateSpriteFromFile(_T("result/rank/result_rank_B.png"));
	this->sound_ = SoundDevice.CreateSoundFromFile(_T("result/otherrank.wav"));

	this->time_ = 0;

}

RankBDisplay::~RankBDisplay(){

	GraphicsDevice.ReleaseSprite(this->ranksprite_);
	SoundDevice.ReleaseSound(this->sound_);

}

int RankBDisplay::Update(int elapsedtime){

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

void RankBDisplay::Draw(){

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

void RankBDisplay::Skip(){

	this->AbstructRankDisplay::Skip();

	this->time_ = 0;
}