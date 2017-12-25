#include "LONGNOTE.h"
#include <math.h>

std::map<Color_by_Name, SPRITE>* LONGNOTE::longnote_sprites_ = nullptr;
std::map<Color_by_Name, SPRITE>* LONGNOTE::triangle_sprites_ = nullptr;

LONGNOTE::LONGNOTE(unsigned timing, float height_rate, Color_by_Name color, long range_count, int range_time, long firsthave_count) :
ABSTRUCT_NOTE(range_count, range_time,firsthave_count),
RIGHT_POWER_MAX_(2000.0f)
{

	this->longnotes_flag_ = true;

	this->timing_ = timing;
	this->height_rate_ = height_rate;
	this->mycolor_ = color;

	this->ispush_ = false;

	this->long_xscale_ = 1.0f;

	this->right_power_ = this->RIGHT_POWER_MAX_;

	this->AddPoint(timing,height_rate);
	
	if (this->triangle_sprites_ == nullptr){

		this->triangle_sprites_ = new std::map<Color_by_Name, SPRITE>;

		(*this->triangle_sprites_)[Color_Red] = GraphicsDevice.CreateSpriteFromFile(_T("triangle/red.png"));
		(*this->triangle_sprites_)[Color_Green] = GraphicsDevice.CreateSpriteFromFile(_T("triangle/green.png"));
		(*this->triangle_sprites_)[Color_Blue] = GraphicsDevice.CreateSpriteFromFile(_T("triangle/blue.png"));

	}

	if (this->longnote_sprites_ == nullptr){

		this->longnote_sprites_ = new std::map<Color_by_Name, SPRITE>;

		(*this->longnote_sprites_)[Color_Red] = GraphicsDevice.CreateSpriteFromFile(_T("notes/long/longnote_red.png"));
		(*this->longnote_sprites_)[Color_Green] = GraphicsDevice.CreateSpriteFromFile(_T("notes/long/longnote_green.png"));
		(*this->longnote_sprites_)[Color_Blue] = GraphicsDevice.CreateSpriteFromFile(_T("notes/long/longnote_blue.png"));

	}

}


LONGNOTE::~LONGNOTE()
{

	if (this->longnote_sprites_ != nullptr) {
		delete this->longnote_sprites_;
		this->longnote_sprites_ = nullptr;
	}

	if (this->triangle_sprites_ != nullptr) {

		delete this->triangle_sprites_;
		this->triangle_sprites_ = nullptr;

	}

}

void LONGNOTE::Update(unsigned nowtime){

	auto p_itr = this->long_points_.begin();
	auto pe_itr = this->long_points_.end();

	pe_itr--;

	if (p_itr != pe_itr)
	if (this->timing_ < nowtime)NoteMove(nowtime);

	LongXScale(nowtime);

}

bool LONGNOTE::Draw(Vector3 fader_top_pos, float fader_height, float animation_rate, unsigned nowtime){

	float x_scale_rate = this->GetXScale();

	if (x_scale_rate <= 0.0f)return false;

	float triangle_x_scale = x_scale_rate;
	if (triangle_x_scale > 1.0f) triangle_x_scale = 1.0f;

	auto p_itr = this->long_points_.begin();
	auto pe_itr = this->long_points_.end();
	pe_itr--;

	unsigned longtime = (*pe_itr).timing - this->timing_;

	DrawTriangle(fader_top_pos, fader_height, nowtime, longtime, triangle_x_scale);

	DrawNote(fader_top_pos, fader_height, nowtime, animation_rate, x_scale_rate);

	return true;

}

void LONGNOTE::DrawNote(Vector3 fader_top_pos, float fader_height, unsigned nowtime, float animation_rate, float x_scale_rate){

	Vector3 note_displaypos = fader_top_pos;
	note_displaypos.y += (fader_height - this->LINE_HEIGHT_) * this->height_rate_ - (this->HEIGHT_ - this->LINE_HEIGHT_) / 2.0f;
	int animenum = (int)(animation_rate * 90.0f);

	float pal;
	SPRITE draw_sprite_;

	if (ispush_){

		if (long_xscale_ > 1.0f) long_xscale_ = 1.0f;
		x_scale_rate = long_xscale_;

		draw_sprite_ = (*this->longnote_sprites_)[mycolor_];


	}
	else{

		if (this->rightup_flag_){
			
			draw_sprite_ = (*this->colornote_sprites_)[mycolor_];

		}
		else{

			draw_sprite_ = this->normal_sprite_;

		}
		
		
	}

	pal = this->right_power_ / this->RIGHT_POWER_MAX_;

	SpriteBatch.Draw(*draw_sprite_, note_displaypos,
		RectWH((animenum % 10) * this->WIDTH_, (animenum / 10) * this->HEIGHT_, this->WIDTH_, this->HEIGHT_), pal,
		Vector3_Zero, Vector3(this->WIDTH_ / 2.0f, 0.0f, 0.0f), Vector2(x_scale_rate, 1.0f));  

}

void LONGNOTE::DrawTriangle(Vector3 fadet_top_pos, float fader_height, unsigned nowtime, unsigned longtime, float long_x_scale){

	auto p_itr = this->long_points_.begin();
	auto pe_itr = this->long_points_.end();
	pe_itr--;

	Vector3 pos;

	//画像の使用描画の計算
	float start_use_rate;
	float end_use_rate;

	//フェーダーでの描画の高さの計算
	float start_height_rate;
	float end_height_rate;
	float draw_height_rate;

	//画像の使用位置上下の指定
	int rect_top;
	int rect_bottom;

	//横広げ
	float scale_y;

	//透明度
	float pal;

	while (p_itr != pe_itr){

		pos = fadet_top_pos;

		if ((*p_itr).timing > nowtime){

			start_use_rate = (float)((*p_itr).timing - this->timing_) / (float)longtime;
			pos.y += fader_height * (*p_itr).height_rate;

		}
		else{

			start_use_rate = (float)(nowtime - this->timing_) / (float)longtime;
			pos.y += fader_height * this->height_rate_;

		}


		end_use_rate = (float)((*(p_itr + 1)).timing - this->timing_) / (float)longtime;


		start_height_rate = ((*p_itr).timing > nowtime) ? (*p_itr).height_rate : this->height_rate_;
		end_height_rate = (*(p_itr + 1)).height_rate;

		draw_height_rate = end_height_rate - start_height_rate;
		
		rect_top = (int)(fader_height * start_use_rate);
		rect_bottom = (int)(fader_height * end_use_rate);

		scale_y = draw_height_rate / (end_use_rate - start_use_rate);

		pal = this->right_power_ / this->RIGHT_POWER_MAX_;

		SpriteBatch.Draw(*( (*this->triangle_sprites_)[mycolor_] ),pos,Rect(0,rect_top,this->WIDTH_,rect_bottom),pal,
			Vector3_Zero, Vector3(this->WIDTH_ / 2.0f,0.0f, 0.0f), Vector2(long_x_scale, scale_y));


		p_itr++;

	}

}

void LONGNOTE::NoteMove(unsigned nowtime){

	auto p_itr = this->long_points_.begin();
	auto pe_itr = this->long_points_.end();

	pe_itr--;

	int pointbetweentime = (p_itr + 1)->timing - p_itr->timing;
	int pointnowtime = (int)nowtime - p_itr->timing;

	float start_height_rate = p_itr->height_rate;
	float between_height_rate = (p_itr + 1)->height_rate - p_itr->height_rate;
	float move_height_rate = between_height_rate * ( (float)pointnowtime / (float)pointbetweentime );

	this->height_rate_ = start_height_rate + move_height_rate;

	if (nowtime > (p_itr + 1)->timing){

		if (p_itr != pe_itr) p_itr = this->long_points_.erase(p_itr);

	}

}

void LONGNOTE::LongXScale(unsigned nowtime){

	unsigned starttime = this->timing_;
	unsigned endtime = (long_points_.end() - 1)->timing;

	unsigned betweentime = endtime - starttime;
	int pointnowtime = (int)nowtime - (int)starttime;

	this->long_xscale_ = 1.0f - ((float)pointnowtime / (float)betweentime);

}

void LONGNOTE::AddPoint(unsigned timing,float height_rate){

	this->long_points_.push_back(LONG_POINT(timing,height_rate));

}