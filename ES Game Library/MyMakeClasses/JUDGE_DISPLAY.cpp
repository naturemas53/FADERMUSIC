#include "JUDGE_DISPLAY.h"
#include "JUDGELIST_ENUM.h"

std::map<JUDGELIST, SPRITE>* JUDGE_DISPLAY::judge_sprites_ = nullptr;

JUDGE_DISPLAY::JUDGE_DISPLAY(Vector3 draw_pos, float fader_height) :
DRAW_POS_(draw_pos),
FADER_HEIGHT_(fader_height),
SIZE_(200.0f),
ZOOM_COUNT_(15)
{

	this->transparency_ = 0.0f;
	this->draw_height_ = 0.0f;
	this->scale_ = 0.2f;

	if (this->judge_sprites_ == nullptr){

		this->judge_sprites_ = new std::map<JUDGELIST, SPRITE>;

		(*this->judge_sprites_)[MISSTIME] = GraphicsDevice.CreateSpriteFromFile(_T("judge/MISS.png"));
		(*this->judge_sprites_)[OK] = GraphicsDevice.CreateSpriteFromFile(_T("judge/OK.png"));
		(*this->judge_sprites_)[GREAT] = GraphicsDevice.CreateSpriteFromFile(_T("judge/GREAT.png"));
		(*this->judge_sprites_)[UNBELIEVABLE] = GraphicsDevice.CreateSpriteFromFile(_T("judge/unbelievable.png"));

	}

	this->draw_judge_ = MISSTIME;
	this->now_count_ = ZOOM_COUNT_ + 10;
	this->scale_state_ = STOP;
}


JUDGE_DISPLAY::~JUDGE_DISPLAY()
{

	if (this->judge_sprites_ != nullptr){

		delete this->judge_sprites_;
		this->judge_sprites_ = nullptr;

	}

}

void JUDGE_DISPLAY::Update(){

	switch (this->scale_state_){

	case ZOOM_OUT:
		this->now_count_++;

		this->scale_ = (1.0f - (float)this->now_count_ / (float)(this->ZOOM_COUNT_ - 5)) * (1.0f - 0.1f) + 0.1f;

		this->transparency_ = (float)this->now_count_ / (float)this->ZOOM_COUNT_;

		if (this->now_count_ >= this->ZOOM_COUNT_ - 5){

			this->scale_state_ = ZOOM_IN;

		}

		break;

	case ZOOM_IN:

		this->now_count_++;

		this->scale_ = ((float)this->now_count_ - (float)(this->ZOOM_COUNT_ - 5)) / ((float)this->ZOOM_COUNT_ - (float)(this->ZOOM_COUNT_ - 5)) * (0.2f - 0.1f) + 0.1f;

		if (this->now_count_ >= this->ZOOM_COUNT_ ){

			this->scale_state_ = STOP;
			this->scale_ = 0.2f;
			this->transparency_ = 1.0f;

		}

		break;

	case STOP:

		if (this->now_count_ < this->ZOOM_COUNT_ + 10){

			this->now_count_++;

			if (this->now_count_ >= this->ZOOM_COUNT_ + 5){
			
				this->transparency_ = 1.0f - ((float)(this->now_count_ - (this->ZOOM_COUNT_ + 5)) / 5.0f);

			}

		}


		break;

	}

}

void JUDGE_DISPLAY::Draw(float fader_width){

	float move_x = (fader_width - this->SIZE_) / 2.0f;
	Vector3 pos = this->DRAW_POS_;
	pos.x += move_x;
	pos.y += FADER_HEIGHT_ * this->draw_height_ - this->SIZE_ / 2.0f;

	JUDGELIST judge = (this->draw_judge_ == OUCH) ? MISSTIME : this->draw_judge_;

	SPRITE draw_sprite = (*this->judge_sprites_)[judge];

	Color mask = (this->draw_judge_ == OUCH) ? Color(255, 255, 0) : Color(255, 255, 255);
	mask.A(this->transparency_);

	SpriteBatch.Draw(*draw_sprite,pos,mask,Vector3_Zero,Vector3(SIZE_ / 2.0f,SIZE_ / 2.0f,0.0f),this->scale_);

}

void JUDGE_DISPLAY::SetBomb(JUDGELIST judge, float height_rate){

	this->draw_height_ = height_rate;

	if (this->now_count_ > 5){

		this->transparency_ = 0.0f;
		this->now_count_ = 0;
		this->scale_ = 0.135f;
		this->scale_state_ = ZOOM_OUT;
	}

	this->draw_judge_ = judge;

}