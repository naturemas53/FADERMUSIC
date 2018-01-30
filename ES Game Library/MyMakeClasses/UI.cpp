#include "UI.h"
#include "JUDGELIST_ENUM.h"
#include "ImageFont.h"

UI::UI() :
FRAME_SIZE_(Vector2(600.0f, 52.0f)),
INNER_SIZE_(Vector2(582.0f, 37.0f)),
ANIMECOUNT_(30),
CELLCOUNT_(2)
{

	this->framesp_ = GraphicsDevice.CreateSpriteFromFile(_T("lifegauge/life_frame.png"));
	this->innersp_ = GraphicsDevice.CreateSpriteFromFile(_T("lifegauge/life_gage.png"));

	this->draw_lifepersent_ = 1.0f;
	this->draw_score_ = 0;
	this->draw_accuracy_ = 0;
	this->draw_maxcombo_ = 0;

	this->nowcount_ = 0;
}


UI::~UI()
{
}

void UI::Update(){

	this->nowcount_++;

	int maxcount = this->ANIMECOUNT_ * this->CELLCOUNT_;

	if (this->nowcount_ >= maxcount ){

		this->nowcount_ = 0;

	}

}

void UI::Draw(float animation_rate){

	int animenum = (int)(90.0f * animation_rate);

	Vector2 cellsize = IMAGEFONT.GetCellSize();

	cellsize /= 2.0f;
	IMAGEFONT.SetImageString(Vector3(5.0f, 5.0f, 0.0f), cellsize, true,"SCORE:\n%08d", this->draw_score_);

	Vector2 drawsize = IMAGEFONT.GetDrawSize(cellsize, "ACCURACY:\n   %06d", this->draw_accuracy_);
	float mostright = 1280.0f - drawsize.x;
	IMAGEFONT.SetImageString(Vector3(mostright - 5.0f, 5.0f, 0.0f), cellsize,true, "ACCURACY:\n   %06d", this->draw_accuracy_);

	cellsize *= 0.5f;
	IMAGEFONT.SetImageString(Vector3(5.0f, 155.0f , 0.0f), cellsize, false, "MAXCOMBO: %4d", this->draw_maxcombo_);

	Vector3 pos = Vector3_Zero;
	pos.y = 10.0f;

	Vector2 framesize = this->FRAME_SIZE_;
	Vector2 innersize = this->INNER_SIZE_;

	int rect_right = (int)(innersize.x * this->draw_lifepersent_);

	SPRITE sp = this->framesp_;
	float pos_x = (1280.0f - framesize.x) / 2.0f;

	SpriteBatch.Begin();
	SpriteBatch.Draw(*sp,Vector3(pos_x,20.0f,0.0f),1.0f);

	int animecount = this->nowcount_ / this->CELLCOUNT_;

	RectWH userect = RectWH(0, innersize.y * animecount, rect_right, (int)innersize.y);
	float plus_x = (framesize.x - innersize.x) / 2.0f;
	float plus_y = (framesize.y - innersize.y) / 2.0f;
	sp = this->innersp_;

	SpriteBatch.Draw(*sp, Vector3(pos_x + plus_x, 20.0f + plus_y, 0.0f),userect, 1.0f);
	SpriteBatch.End();

	GraphicsDevice.SetBlendMode(DXGBLEND_ADD);
	SpriteBatch.Begin();

	float pal = (this->draw_lifepersent_ >= 1.0f) ? 0.3f + (0.7f * animation_rate) : 0.5f * animation_rate;

	SpriteBatch.Draw(*sp, Vector3(pos_x + plus_x, 20.0f + plus_y, 0.0f), userect, pal);

	SpriteBatch.End();
	GraphicsDevice.SetBlendMode(DXGBLEND_NORMAL);

}

void UI::SetDisplayData(int score, float life, int accuracy, int allnotes, int maxcombo){

	this->draw_lifepersent_ = life;
	this->draw_score_ = score;

	this->draw_accuracy_ = (int)(100000.0f * ((float)accuracy / (float)(allnotes * 100)) );
	this->draw_maxcombo_ = maxcombo;

}
