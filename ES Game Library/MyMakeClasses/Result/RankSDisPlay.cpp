#include "RankSDisplay.h"

RankSDisPlay::RankSDisPlay() : AbstructRankDisplay(Vector2(223.0f,320.0f)){

	this->ranksprite_ = GraphicsDevice.CreateSpriteFromFile(_T("result/rank/result_rank_S.png"));

	this->datas_.push_back(ScaleData(0, 100.0f));
	this->datas_.push_back(ScaleData(200, 0.3f));
	this->datas_.push_back(ScaleData(100, 1.0f));

	this->nowdata_ = this->datas_.begin();
	this->nowtime_ = 0;
	this->scale_ = this->nowdata_->targetscale_;

}

RankSDisPlay::~RankSDisPlay(){

	GraphicsDevice.ReleaseSprite(this->ranksprite_);

}

int RankSDisPlay::Update(int elapsedtime){

	float dirscale;
	float timerate;
	ScaleData nextdata;

	auto nowitr = this->nowdata_;
	auto e_itr = this->datas_.end();
	e_itr--;

	switch (this->state_){

	case AbstructRankDisplay::EFFECT:

		this->nowtime_ += elapsedtime;
		nextdata = *(this->nowdata_ + 1);

		if (this->nowtime_ > nextdata.time_){

			this->nowtime_ -= nextdata.time_;

			this->nowdata_++;
			if (this->nowdata_ == e_itr){

				this->nowtime_ = 0;
				this->scale_ = this->nowdata_->targetscale_;
				this->state_ = AbstructRankDisplay::STOP;
				break;
			}

			nextdata = *(this->nowdata_ + 1);

		}

		dirscale = nextdata.targetscale_ - nowitr->targetscale_;
		timerate = (float)this->nowtime_ / (float)nextdata.time_;

		this->scale_ = nowdata_->targetscale_ + (dirscale * timerate);

		break;

	case AbstructRankDisplay::STOP:

		return 1;

		break;

	default:
		break;

	}

	return 0;

}

void RankSDisPlay::Skip(){

	this->AbstructRankDisplay::Skip();

	this->nowtime_ = 0;
	auto itr = this->datas_.end();
	itr--;

	this->scale_ = itr->targetscale_;

}


void RankSDisPlay::Draw(){

	if (this->state_ == AbstructRankDisplay::STOP){

		auto itr = this->datas_.end();
		itr--;

		this->scale_ = itr->targetscale_;

	}

	SPRITE sp = this->ranksprite_;
	Vector2 size = this->SIZE_;

	Color color = Color(255, 255, 255);
	if (this->state_ == AbstructRankDisplay::WAIT){

		color.A(0.0f);

	}

	SpriteBatch.Begin();

	SpriteBatch.Draw(*sp, this->POS_, color, Vector3_Zero, Vector3(size.x / 2.0f, size.y / 2.0f, 0.0f), this->scale_);

	SpriteBatch.End();

}