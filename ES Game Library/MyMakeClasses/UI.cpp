#include "UI.h"
#include "JUDGELIST_ENUM.h"
#include "ImageFont.h"

UI::UI():
FRAME_HEIGHT_(52.0f),
FRAME_WIDTH_(600.0f),
INNER_HEIGHT_(37.0f),
INNER_WIDTH_(582.0f),
score_font_(GraphicsDevice.CreateSpriteFont(_T("Voyager Grotesque Bold"), 50)),
accuracy_font_(GraphicsDevice.CreateSpriteFont(_T("Voyager Grotesque Light"), 20))
{

	this->framesp_ = GraphicsDevice.CreateSpriteFromFile(_T("lifegauge/life_frame.png"));
	this->innersp_ = GraphicsDevice.CreateSpriteFromFile(_T("lifegauge/life_gage.png"));

	this->draw_lifepersent_ = 1.0f;
	this->draw_score_ = 0;
	this->draw_accuracy_ = 0;
	this->draw_maxcombo_ = 0;

}


UI::~UI()
{
}

void UI::Update(){


}

void UI::Draw(float animation_rate){

	int animenum = (int)(90.0f * animation_rate);

	//SpriteBatch.DrawString(this->score_font_, Vector2(10.0f, 10.0f), Color(0, 255, 0), _T("SCORE : %08d"),this->draw_score_);
	//SpriteBatch.DrawString(this->accuracy_font_, Vector2(10.0f, 70.0f), Color(0, 255, 0), _T("ACCURACY : %06d"), this->draw_accuracy_);
	//SpriteBatch.DrawString(this->accuracy_font_, Vector2(210.0f, 70.0f), Color(0, 255, 0), _T("MAXCOMBO : %04d"), this->draw_maxcombo_);

	Vector2 cellsize = IMAGEFONT.GetCellSize();

	cellsize *= 0.5f;
	IMAGEFONT.SetImageString(Vector3(10.0f, 10.0f, 0.0f), cellsize, true,"SCORE:\n%08d", this->draw_score_);
	IMAGEFONT.SetImageString(Vector3(10.0f, 10.0f + 150.0f, 0.0f), cellsize,true, "ACCURACY:\n   %06d", this->draw_accuracy_);

	cellsize *= 0.5f;
	IMAGEFONT.SetImageString(Vector3(10.0f, 10.0f + 320.0f, 0.0f), cellsize, false,"MAXCOMBO: %4d", this->draw_maxcombo_);

	Vector3 pos = Vector3_Zero;
	pos.x += 1280.0f / 2.0f;
	pos.y = 10.0f;


	int rect_right = (int)(this->INNER_WIDTH_ * this->draw_lifepersent_);

	SPRITE sp = this->framesp_;
	float pos_x = 330.0f + (960.0f - this->FRAME_WIDTH_) / 2.0f;

	SpriteBatch.Draw(*sp,Vector3(pos_x,20.0f,0.0f),1.0f);

	RectWH userect = RectWH(0, 0, rect_right, (int)this->INNER_HEIGHT_);
	float plus_x = (this->FRAME_WIDTH_ - this->INNER_WIDTH_) / 2.0f;
	float plus_y = (this->FRAME_HEIGHT_ - this->INNER_HEIGHT_) / 2.0f;
	sp = this->innersp_;

	SpriteBatch.Draw(*sp, Vector3(pos_x + plus_x, 20.0f + plus_y, 0.0f),userect, 1.0f);

}

void UI::InnerAddDraw(float animation_rate){

	Vector3 pos = Vector3_Zero;
	pos.x += 1280.0f / 2.0f;
	pos.y = 10.0f;

	int rect_right = (int)(this->INNER_WIDTH_ * this->draw_lifepersent_);

	float pos_x = 330.0f + (960.0f - this->FRAME_WIDTH_) / 2.0f;

	RectWH userect = RectWH(0, 0, rect_right, (int)this->INNER_HEIGHT_);
	float plus_x = (this->FRAME_WIDTH_ - this->INNER_WIDTH_) / 2.0f;
	float plus_y = (this->FRAME_HEIGHT_ - this->INNER_HEIGHT_) / 2.0f;
	SPRITE sp = this->innersp_;

	float pal = (this->draw_lifepersent_ >= 1.0f) ? 0.3f + (0.7f * animation_rate) : 0.5f * animation_rate;

	SpriteBatch.Draw(*sp, Vector3(pos_x + plus_x, 20.0f + plus_y, 0.0f), userect, pal);

}

void UI::SetDisplayData(int score, float life, int accuracy, int allnotes, int maxcombo){

	this->draw_lifepersent_ = life;
	this->draw_score_ = score;

	this->draw_accuracy_ = (int)(100000.0f * ((float)accuracy / (float)(allnotes * 100)) );
	this->draw_maxcombo_ = maxcombo;

}
