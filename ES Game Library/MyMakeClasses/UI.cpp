#include "UI.h"
#include "JUDGELIST_ENUM.h"

UI::UI():
GAUGE_HEIGHT_(100.0f),
GAUGE_WIDTH_(630.0f),
score_font_(GraphicsDevice.CreateSpriteFont(_T("Voyager Grotesque Bold"), 50)),
accuracy_font_(GraphicsDevice.CreateSpriteFont(_T("Voyager Grotesque Light"), 20))
{

	this->lifegauge_sprite_ = GraphicsDevice.CreateSpriteFromFile(_T("lifegauge/ui_lifegauge.png"));
	this->uiline_sprite_ = GraphicsDevice.CreateSpriteFromFile(_T("background/ui.png"));

	this->draw_lifepersent_ = 0.5f;
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

	SpriteBatch.Draw(*this->uiline_sprite_,Vector3_Zero);

	int animenum = (int)(90.0f * animation_rate);

	SpriteBatch.DrawString(this->score_font_, Vector2(10.0f, 10.0f), Color(0, 255, 0), _T("SCORE : %08d"),this->draw_score_);
	SpriteBatch.DrawString(this->accuracy_font_, Vector2(10.0f, 70.0f), Color(0, 255, 0), _T("ACCURACY : %06d"), this->draw_accuracy_);
	SpriteBatch.DrawString(this->accuracy_font_, Vector2(210.0f, 70.0f), Color(0, 255, 0), _T("MAXCOMBO : %04d"), this->draw_maxcombo_);

	Vector3 pos = Vector3_Zero;
	pos.x += 1280.0f / 2.0f;
	pos.y = 10.0f;


	int rect_right = (int)((float)this->GAUGE_WIDTH_ * this->draw_lifepersent_);

	SpriteBatch.Draw(*this->lifegauge_sprite_,pos,
		RectWH((animenum % 3) * this->GAUGE_WIDTH_, (animenum / 3) * this->GAUGE_HEIGHT_, rect_right,this->GAUGE_HEIGHT_ )
		,1.0f);

}

void UI::SetDisplayData(int score, float life, int accuracy, int allnotes, int maxcombo){

	this->draw_lifepersent_ = life;
	this->draw_score_ = score;

	this->draw_accuracy_ = (int)(100000.0f * ((float)accuracy / (float)(allnotes * 100)) );
	this->draw_maxcombo_ = maxcombo;

}
