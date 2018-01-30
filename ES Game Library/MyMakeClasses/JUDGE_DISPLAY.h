#pragma once
#include "JUDGELIST_ENUM.h"
#include "ImageFont.h"
#include "../ESGLib.h"
#include <string>
#include <map>

class JUDGE_DISPLAY
{
public:
	JUDGE_DISPLAY(float fader_height,float fader_width);
	~JUDGE_DISPLAY();

	void Update();
	void Draw();

	void SetBomb(JUDGELIST judge, Vector3 drawpos , float height_rate,int combo);

	void AddDraw(){

		if (this->draw_judge_ == MISSTIME || this->draw_judge_ == OUCH) return;

		float move_x = (this->FADER_WIDTH_ - this->SIZE_) / 2.0f;
		Vector3 pos = this->drawpos_;
		pos.x += move_x;
		pos.y += this->FADER_HEIGHT_ * this->draw_height_ - this->SIZE_ / 2.0f;

		JUDGELIST judge = (this->draw_judge_ == OUCH) ? MISSTIME : this->draw_judge_;

		SPRITE draw_sprite = this->judge_sprites_[judge];

		if (this->addalpha_ > 0.0f){

			GraphicsDevice.SetBlendMode(DXGBLEND_ADD);
			SpriteBatch.Begin();
			SpriteBatch.Draw(*draw_sprite, pos, this->addalpha_, Vector3_Zero, Vector3(SIZE_ / 2.0f, SIZE_ / 2.0f, 0.0f), this->scale_);
			SpriteBatch.End();
			GraphicsDevice.SetBlendMode(DXGBLEND_NORMAL);

		}


	}
	
private:

	void CalcTransparency(float rate,bool fadein){

		this->transparency_ = 0.0f;

		if (this->now_count_ % 2 == 1) this->transparency_ += 0.2f;

		if (fadein){

			this->transparency_ += 0.8f * rate;

		}
		else{

			this->transparency_ += 0.8f * (1.0f - rate);

		};
	}

	enum SCALE_STATE{

		FIRST,
		SECOND,
		THIRD

	}scale_state_;

	void AnimeUpdate();
	void ViewParameterReset();

	const float FADER_HEIGHT_;
	const float FADER_WIDTH_;
	const float SIZE_;
	const int FIRST_COUNT_;
	const int SECOND_COUNT_;
	const int THIRD_COUNT_;
	const float FIRST_SCALE_;
	const float SECOND_SCALE_;
	const float THIRD_SCALE_;

	int now_count_;
	Vector3 drawpos_;


	float addalpha_;
	float transparency_;
	float scale_;
	float draw_height_;

	int drawcombo_;

	std::map<JUDGELIST, SPRITE> judge_sprites_;

	JUDGELIST draw_judge_;


};

