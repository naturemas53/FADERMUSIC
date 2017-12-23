#include "SINGLENOTE.h"


SINGLENOTE::SINGLENOTE(unsigned timing, float height_rate, Color_by_Name color, long range_count, int range_time) :
ABSTRUCT_NOTE(range_count,range_time)
{

	this->longnotes_flag_ = false;
	
	this->timing_ = timing;

	if (height_rate > 1.0f) height_rate = 1.0f;
	if (height_rate < 0.0f) height_rate = 0.0f;

	this->height_rate_ = height_rate;
	this->mycolor_ = color;
}

void SINGLENOTE::Init(unsigned timing, float height_rate){

	this->timing_ = timing;
	this->height_rate_ = height_rate;

}

bool SINGLENOTE::Draw(Vector3 fader_top_pos, float fader_height, float animation_rate, unsigned nowtime){

	//数字は全部エフェクトのそれ

	Vector3 note_displaypos = fader_top_pos;
	note_displaypos.y += (fader_height - this->LINE_HEIGHT_) * this->height_rate_ - (this->HEIGHT_ - this->LINE_HEIGHT_) / 2.0f; 
	int animenum = (int)(animation_rate * 90.0f);

	float x_scale_rate = this->GetXScale();

	SPRITE draw_sprite;

	if (this->rightup_flag_){
	
		draw_sprite = (*this->colornote_sprites_)[this->mycolor_];

	}
	else{

		draw_sprite = this->normal_sprite_;
	
	}

	SpriteBatch.Draw(*draw_sprite, note_displaypos,
		RectWH((animenum % 10) * this->WIDTH_, (animenum / 10) * this->HEIGHT_, this->WIDTH_, this->HEIGHT_), 1.0f,
		Vector3_Zero, Vector3(this->WIDTH_ / 2.0f, 0.0f, 0.0f), Vector2(x_scale_rate, 1.0f));

	return true;
}