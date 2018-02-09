#include "LongBreakBomb.h"

std::map<Color_by_Name, SPRITE>* LongBreakBomb::sprites_ = nullptr;


LongBreakBomb::LongBreakBomb() :AbstructBomb(0,1,1,Vector2(92.0f,93.0f)),
FADEOUTTIME_(1500),
REDUCINGTIME_(3000),
DIAMONDSCALE_(180.0f / 54.0f - 1.0f){

	if (this->sprites_ == nullptr){

		this->sprites_ = new std::map<Color_by_Name, SPRITE>;

		(*this->sprites_)[Color_Red] = GraphicsDevice.CreateSpriteFromFile(_T("notes/long/diamond_red.png"));
		(*this->sprites_)[Color_Green] = GraphicsDevice.CreateSpriteFromFile(_T("notes/long/diamond_green.png"));
		(*this->sprites_)[Color_Blue] = GraphicsDevice.CreateSpriteFromFile(_T("notes/long/diamond_blue.png"));

	}

	this->xscale_ = 1.0f;
	this->alpha_ = 0.5f;
	this->time_ = this->REDUCINGTIME_;
	this->useflag_ = true;
	this->mycolor_ = Color_Red;

}

LongBreakBomb::~LongBreakBomb(){

	if (this->sprites_ != nullptr){

		for (auto sprite : (*this->sprites_) ){

			GraphicsDevice.ReleaseSprite(sprite.second);

		}


		delete this->sprites_;
		this->sprites_ = nullptr;

	}

}

void LongBreakBomb::Init(Vector3 fader_pos, Vector2 inner_size, float height, Color_by_Name color, float longxscale){

	this->time_ = this->REDUCINGTIME_;
	this->mycolor_ = color;
	this->alpha_ = 1.0f;
	this->useflag_ = true;

	float scalerate = 1.0f - longxscale;


	this->pos_ = Vector3_Zero;

	pos_.y += inner_size.y * height;
	pos_.y -= this->CELLSIZE_.y / 2.0f;

	pos_ += fader_pos;

	//54 ‚Í@ƒ_ƒCƒ„‚Ì‚³‚¢‚¸
	pos_.x += (inner_size.x - this->CELLSIZE_.x) / 2.0f;

	float diamondscale = this->DIAMONDSCALE_ * scalerate;

	this->time_ = (float)this->REDUCINGTIME_ * scalerate;
	this->xscale_ = 1.0f + diamondscale;
	this->state_ = LongBreakBomb::REDUCING;

	if (this->xscale_ <= 1.0f){
		this->xscale_ = 1.0f;
		this->time_ = this->FADEOUTTIME_;
		this->state_ = LongBreakBomb::FADEOUT;
	}

}

int LongBreakBomb::Update(int elapsedtime){

	this->time_ -= elapsedtime;

	//float diamondscale;
	float timerate;

	switch (this->state_){

	case LongBreakBomb::REDUCING:

		if (this->time_ < 0){

			this->xscale_ = 1.0f;
			this->time_ = this->FADEOUTTIME_ + this->time_;
			this->alpha_ = ((float)this->time_ / (float)this->FADEOUTTIME_) * 1.0f;
			this->state_ = LongBreakBomb::FADEOUT;
			break;

		}

		timerate = (float)this->time_ / (float)this->REDUCINGTIME_;
		this->xscale_ = 1.0f + (this->DIAMONDSCALE_ * timerate);

		break;

	case LongBreakBomb::FADEOUT:

		if (this->time_ < 0){

			this->time_ = 0;
			this->alpha_ = 0.0f;
			return 1;

		}

		this->alpha_ = (float)this->time_ / (float)this->FADEOUTTIME_ * 1.0f;

		break;

	default:
		return 1;
		break;

	}

	return 0;

}

void LongBreakBomb::Draw(){

	SPRITE sp = (*this->sprites_)[this->mycolor_];

	Color color = Color(0.7f, 0.7f, 0.7f, this->alpha_);

	SpriteBatch.Begin();
	SpriteBatch.Draw(*sp, this->pos_, color, Vector3_Zero, Vector3(this->CELLSIZE_.x / 2.0f, 0.0f, 0.0f), Vector2(this->xscale_,1.0f));
	SpriteBatch.End();

}
