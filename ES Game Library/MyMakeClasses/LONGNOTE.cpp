#include "LONGNOTE.h"
#include <math.h>

std::map<Color_by_Name, SPRITE>* LONGNOTE::longnote_sprites_ = nullptr;
std::map<Color_by_Name, SPRITE>* LONGNOTE::triangle_sprites_ = nullptr;
std::map<Color_by_Name, SPRITE>* LONGNOTE::diamond_sprites_ = nullptr;
SPRITE LONGNOTE::innner_box_ = nullptr;

LONGNOTE::LONGNOTE(int timing, float height_rate, Color_by_Name color, long range_count, int range_time, long firsthave_count) :
ABSTRUCT_NOTE(range_count, range_time,firsthave_count),
DIAMOND_SIZE_(Vector2(54.0f,93.0f)),
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

	if (this->diamond_sprites_ == nullptr){

		this->diamond_sprites_ = new std::map<Color_by_Name, SPRITE>;
		(*this->diamond_sprites_)[Color_Red] = GraphicsDevice.CreateSpriteFromFile(_T("notes/long/diamond_red.png"));
		(*this->diamond_sprites_)[Color_Green] = GraphicsDevice.CreateSpriteFromFile(_T("notes/long/diamond_green.png"));
		(*this->diamond_sprites_)[Color_Blue] = GraphicsDevice.CreateSpriteFromFile(_T("notes/long/diamond_blue.png"));

	}

	if (this->innner_box_ == nullptr){

		this->innner_box_ = GraphicsDevice.CreateSpriteFromFile(_T("fader/innerbox.png"));

	}

}


LONGNOTE::~LONGNOTE()
{

	if (this->longnote_sprites_ != nullptr) {

		for (auto sprite : (*this->longnote_sprites_)){

			GraphicsDevice.ReleaseSprite(sprite.second);

		}

		delete this->longnote_sprites_;
		this->longnote_sprites_ = nullptr;
	}

	if (this->triangle_sprites_ != nullptr) {

		for (auto sprite : (*this->triangle_sprites_)){

			GraphicsDevice.ReleaseSprite(sprite.second);

		}

		delete this->triangle_sprites_;
		this->triangle_sprites_ = nullptr;

	}

	if (this->diamond_sprites_ != nullptr) {

		for (auto sprite : (*this->diamond_sprites_)){

			GraphicsDevice.ReleaseSprite(sprite.second);

		}

		delete this->diamond_sprites_;
		this->diamond_sprites_ = nullptr;

	}

	if (this->innner_box_ != nullptr){

		GraphicsDevice.ReleaseSprite(this->innner_box_);
		this->innner_box_ = nullptr;

	}

}

void LONGNOTE::Update(int nowtime){

	auto p_itr = this->nowitr_;
	auto pe_itr = this->long_points_.end();

	pe_itr--;

	if (p_itr != pe_itr)
	if (this->timing_ < nowtime)NoteMove(nowtime);

	LongXScale(nowtime);

	this->trianglemap_.Update(this->long_points_);

}

bool LONGNOTE::Draw(Vector3 fader_top_pos, Vector2 fader_inner, float animation_rate, int nowtime, float highspeed, bool addblend)
{

	float x_scale_rate = this->GetXScale(highspeed);

	if (x_scale_rate <= 0.0f)return false;

	SPRITE sp = this->innner_box_;
	Vector3 pos = fader_top_pos;

	float triangle_x_scale = x_scale_rate;
	if (triangle_x_scale > 1.0f) triangle_x_scale = 1.0f;

	auto p_itr = this->long_points_.begin();
	auto pe_itr = this->long_points_.end();
	pe_itr--;

	int longtime = (*pe_itr).timing - this->timing_;

	Color color = Color(1.0f,1.0f,1.0f);

	if (this->ispush_){
		switch (this->mycolor_){

		case Color_Red: color = Color(1.0f, 0.3f, 0.3f); break;
		case Color_Green: color = Color(0.3f, 1.0f, 0.3f); break;
		case Color_Blue: color = Color(0.3f, 0.3f, 1.0f); break;
		default:break;

		}
	}

	color.A(0.3f);

	float scale = (this->ispush_) ? this->long_xscale_ : triangle_x_scale;
	SpriteBatch.Begin();
	SpriteBatch.Draw(*sp, pos, color, Vector3_Zero, Vector3(this->WIDTH_ / 2.0f, 0.0f, 0.0f), Vector2(scale, 1.0f));
	SpriteBatch.End();

	DrawTriangle(fader_top_pos, fader_inner.y, nowtime, longtime,animation_rate, triangle_x_scale,addblend);

	if(addblend)GraphicsDevice.SetBlendMode(DXGBLEND_ADD);

	SpriteBatch.Begin();

	DrawNote(fader_top_pos, fader_inner.y, nowtime, animation_rate, x_scale_rate, addblend);

	//this->DrawDiamond(fader_top_pos, fader_inner,nowtime,longtime, animation_rate, x_scale_rate, addblend);
	SpriteBatch.End();

	GraphicsDevice.SetBlendMode(DXGBLEND_NORMAL);

	return true;

}

void LONGNOTE::DrawNote(Vector3 fader_top_pos, float fader_height, int nowtime, float animation_rate, float x_scale_rate, bool addblend){

	Vector3 note_displaypos = fader_top_pos;
	note_displaypos.y += (fader_height - this->LINE_HEIGHT_) * this->height_rate_ - (this->HEIGHT_ - this->LINE_HEIGHT_) / 2.0f;
	int animenum = (int)(animation_rate * 90.0f);

	float pal;
	SPRITE draw_sprite_;

	if (this->rightup_flag_){

		draw_sprite_ = (*this->colornote_sprites_)[mycolor_];

	}
	else{

		draw_sprite_ = this->normal_sprite_;

	}

	if (this->ispush_){

		//x_scale_rate = (x_scale_rate > 1.0f) ? 1.0f : x_scale_rate;
		x_scale_rate = this->long_xscale_;

	}

	pal = (addblend) ? animation_rate : this->right_power_ / this->RIGHT_POWER_MAX_;

	SpriteBatch.Draw(*draw_sprite_, note_displaypos, pal,Vector3_Zero, Vector3(this->WIDTH_ / 2.0f, 0.0f, 0.0f), Vector2(x_scale_rate, 1.0f));

}

void LONGNOTE::DrawDiamond(Vector3 fader_top_pos, Vector2 fader_inner, int nowtime, int longtime, float animation_rate, float x_scale_rate, bool addblend){

	Vector3 note_displaypos = fader_top_pos;
	note_displaypos.x += (fader_inner.x - this->DIAMOND_SIZE_.x) / 2.0f;

	//緊急で付け焼刃　(92.0f - 54.0f) / 2.0f;
	note_displaypos.x -= (92.0f - 54.0f) / 2.0f;

	note_displaypos.y += (fader_inner.y) * this->height_rate_;
	note_displaypos.y -= this->DIAMOND_SIZE_.y / 2.0f;
	int animenum = (int)(animation_rate * 90.0f);

	float diamond_scale = fader_inner.x / this->DIAMOND_SIZE_.x;
	diamond_scale -= 1.0f;
		
	float pal;
	SPRITE draw_sprite = (*this->diamond_sprites_)[this->mycolor_];

	if (this->ispush_){

		nowtime = nowtime - this->timing_;
		//float timerate = (float)nowtime / (float)longtime;
		float timerate = 1.0f - this->long_xscale_;

		x_scale_rate = 1.0f + (timerate * diamond_scale);

	}
	else{

		x_scale_rate = (x_scale_rate > 1.0f) ? 1.0f : x_scale_rate;

	}

	pal = (addblend) ? animation_rate : this->right_power_ / this->RIGHT_POWER_MAX_;

	SpriteBatch.Draw(*draw_sprite, note_displaypos, pal, Vector3_Zero, Vector3(92.0f / 2.0f, 0.0f, 0.0f), Vector2(x_scale_rate, 1.0f));

}

void LONGNOTE::DrawTriangle(
	Vector3 fadet_top_pos,
	float fader_height, 
	int nowtime, 
	int longtime,
	float animation_rate, 
	float long_x_scale,
	bool addblend){

	auto p_itr = this->nowitr_;
	auto pe_itr = this->long_points_.end();
	pe_itr--;

	Vector3 pos;

	//画像の使用範囲の計算
	float start_use_rate = 0.0f;
	float end_use_rate = 0.0f;
	float total_use_rate = 0.0f;

	//フェーダーでの描画位置の計算
	float start_height_rate;
	float end_height_rate;
	float draw_height_rate;

	//間の　こう　高さ
	float dir_height_rate;

	//透明度
	float pal;
	Color color = Color(255,255,255);

	//画像の生成
	RENDERTARGET screen = this->trianglemap_.GetSprite((*this->triangle_sprites_)[mycolor_],nowtime,this->long_points_);


	//画像の使用位置上下の指定
	int rect_top;
	int rect_bottom;

	//上下反転のそれ
	float scale_y;

	SpriteBatch.Begin();

	while (p_itr != pe_itr){

		pos = fadet_top_pos;
		//210 枠までの横サイズ
		pos.x -= (210.0f - this->WIDTH_) / 2.0f;


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

		rect_top = (int)((536.0f)* start_use_rate);
		rect_bottom = (int)((536.0f) * end_use_rate);

		scale_y = draw_height_rate / (end_use_rate - start_use_rate);

		pal = (addblend) ? animation_rate : this->right_power_ / this->RIGHT_POWER_MAX_;
		color.A(pal);

		//210 FADERの枠までの横
		SpriteBatch.Draw(*screen, pos, Rect(0, rect_top, 210.0f, rect_bottom), color,
			Vector3_Zero, Vector3(210.0f/ 2.0f,0.0f, 0.0f), Vector2(long_x_scale, scale_y));

		p_itr++;

	}

	SpriteBatch.End();

}

void LONGNOTE::NoteMove(int nowtime){

	auto p_itr = this->nowitr_;
	auto pe_itr = this->long_points_.end();

	pe_itr--;

	int pointbetweentime = (p_itr + 1)->timing - p_itr->timing;
	int pointnowtime = nowtime - p_itr->timing;

	float start_height_rate = p_itr->height_rate;
	float between_height_rate = (p_itr + 1)->height_rate - p_itr->height_rate;
	float move_height_rate = between_height_rate * ( (float)pointnowtime / (float)pointbetweentime );

	this->height_rate_ = start_height_rate + move_height_rate;

	if (nowtime > (p_itr + 1)->timing){

		if (this->nowitr_ != pe_itr) this->nowitr_++;

	}

}

void LONGNOTE::LongXScale(int nowtime){

	int starttime = this->timing_;
	int endtime = (long_points_.end() - 1)->timing;

	int betweentime = endtime - starttime;
	int pointnowtime = nowtime - starttime;

	this->long_xscale_ = 1.0f - ((float)pointnowtime / (float)betweentime);

}

void LONGNOTE::AddPoint(int timing,float height_rate){

	int size = this->long_points_.size();

	auto itr = this->long_points_.begin();
	auto e_itr = this->long_points_.end();

	int inserttiming = timing;
	int checktiming;

	while (itr != e_itr){

		checktiming = itr->timing;

		if (inserttiming < checktiming){

			this->long_points_.insert(itr,LONG_POINT(timing,height_rate));
			this->nowitr_ = this->long_points_.begin();
			return;
		}

		itr++;

	}

	this->long_points_.push_back(LONG_POINT(timing, height_rate));
	this->nowitr_ = this->long_points_.begin();

}