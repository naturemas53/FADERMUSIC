#include "JUDGE_DISPLAY.h"
#include "ImageFont.h"

JUDGE_DISPLAY::JUDGE_DISPLAY(float fader_height,float fader_width) :
FADER_HEIGHT_(fader_height),
FADER_WIDTH_(fader_width),
SIZE_(200.0f),
FIRST_COUNT_(5),
SECOND_COUNT_(10),
THIRD_COUNT_(10),
FIRST_SCALE_(0.1f),
SECOND_SCALE_(0.5f),
THIRD_SCALE_(0.45f)
{

	this->transparency_ = 0.0f;
	this->draw_height_ = 0.0f;
	this->scale_ = this->THIRD_SCALE_;

	this->judge_sprites_[MISSTIME] = GraphicsDevice.CreateSpriteFromFile(_T("judge/MISS.png"));
	this->judge_sprites_[OK] = GraphicsDevice.CreateSpriteFromFile(_T("judge/OK.png"));
	this->judge_sprites_[GREAT] = GraphicsDevice.CreateSpriteFromFile(_T("judge/GREAT.png"));
	this->judge_sprites_[UNBELIEVABLE] = GraphicsDevice.CreateSpriteFromFile(_T("judge/unbelievable.png"));

	this->draw_judge_ = MISSTIME;
	this->now_count_ = this->THIRD_COUNT_;
	this->scale_state_ = THIRD;
	this->addalpha_ = 0.0f;
	this->drawcombo_ = 0;
	this->drawpos_ = Vector3_Zero;
}


JUDGE_DISPLAY::~JUDGE_DISPLAY()
{

	for (auto sprite : this->judge_sprites_){

		GraphicsDevice.ReleaseSprite(sprite.second);

	}

}

void JUDGE_DISPLAY::Update(){

	this->AnimeUpdate();

}

void JUDGE_DISPLAY::Draw(){

	float move_x = (this->FADER_WIDTH_ - this->SIZE_) / 2.0f;
	Vector3 pos = this->drawpos_;
	pos.x += move_x;
	pos.y += this->FADER_HEIGHT_ * this->draw_height_ - this->SIZE_ / 2.0f;

	JUDGELIST judge = (this->draw_judge_ == OUCH) ? MISSTIME : this->draw_judge_;

	SPRITE draw_sprite = this->judge_sprites_[judge];

	Color mask = (this->draw_judge_ == OUCH) ? Color(255, 255, 0) : Color(255, 255, 255);
	mask.A(this->transparency_);

	SpriteBatch.Begin();
	SpriteBatch.Draw(*draw_sprite,pos,mask,Vector3_Zero,Vector3(SIZE_ / 2.0f,SIZE_ / 2.0f,0.0f),this->scale_);
	SpriteBatch.End();

	this->AddDraw();

	if (this->drawcombo_ <= 0 || (this->scale_state_ == THIRD && this->now_count_ >= this->THIRD_COUNT_) ) return;

	Vector2 cellsize = IMAGEFONT.GetCellSize();
	cellsize /= 3.0f;
	Vector2 drawsize = IMAGEFONT.GetDrawSize(cellsize,"COMBO%3d",this->drawcombo_);
	float plus_x = (this->FADER_WIDTH_ - drawsize.x) / 2.0f;
	pos.x = this->drawpos_.x + plus_x;
	pos.y += 40.0f; //‚³‚¶‰ÁŒ¸
	if (this->draw_judge_ == UNBELIEVABLE)pos.y -= (cellsize.y * 0.7f);

	IMAGEFONT.SetImageString(pos, cellsize,Color(255,255,255),true,"COMBO%3d", this->drawcombo_);

}

void JUDGE_DISPLAY::SetBomb(JUDGELIST judge,Vector3 drawpos,float height_rate,int combo){

	this->draw_height_ = height_rate;
	this->drawpos_ = drawpos;

	this->ViewParameterReset();

	this->draw_judge_ = judge;
	this->drawcombo_ = combo;

}

void JUDGE_DISPLAY::AnimeUpdate(){

	float rate;
	float dirscale;
	switch (this->scale_state_){

	case FIRST:

		this->now_count_++;

		dirscale = this->SECOND_SCALE_ - this->FIRST_SCALE_;
		rate = (float)this->now_count_ / (float)this->FIRST_COUNT_;

		this->scale_ = this->FIRST_SCALE_ + (dirscale * rate);

		this->CalcTransparency(rate, true);

		if (this->now_count_ >= this->FIRST_COUNT_){

			this->scale_state_ = SECOND;
			this->now_count_ = 0;
			this->addalpha_ = 1.0f;

		}

		break;

	case SECOND:

		this->now_count_++;

		dirscale = this->THIRD_SCALE_ - this->SECOND_SCALE_;
		rate = (float)this->now_count_ / (float)this->SECOND_COUNT_;

		this->scale_ = this->SECOND_SCALE_ + (dirscale * rate);
		this->CalcTransparency(1.0f, true);
		this->addalpha_ = (1.0f - rate) * 1.0f;


		if (this->now_count_ >= this->SECOND_COUNT_){

			this->scale_state_ = THIRD;
			this->scale_ = this->THIRD_SCALE_;
			this->transparency_ = 1.0f;
			this->now_count_ = 0;
			this->addalpha_ = 0.0f;

		}

		break;

	case THIRD:

		if (this->now_count_ < this->THIRD_COUNT_){

			this->now_count_++;

			rate = (float)this->now_count_ / (float)this->THIRD_COUNT_;

			this->CalcTransparency(rate, false);

			if (this->now_count_ == this->THIRD_COUNT_) this->transparency_ = 0.0f;

		}


		break;

	}

}

void JUDGE_DISPLAY::ViewParameterReset(){

	//‰Šú‰»•”•ª
	this->transparency_ = 0.0f;
	this->now_count_ = 0;
	this->scale_ = this->FIRST_SCALE_;
	this->scale_state_ = FIRST;
	this->addalpha_ = 0.0f;

}