#include "UI.h"


UI::UI():
GAUGE_HEIGHT_(100.0f),
GAUGE_WIDTH_(630.0f)
{

	this->lifegauge_sprite_ = GraphicsDevice.CreateSpriteFromFile(_T("lifegauge/ui_lifegauge.png"));
	this->uiline_sprite_ = GraphicsDevice.CreateSpriteFromFile(_T("background/ui.png"));

	draw_lifepersent_ = 1.0f;

}


UI::~UI()
{
}

void UI::Update(){


}

void UI::Draw(float animation_rate){

	SpriteBatch.Draw(*this->uiline_sprite_,Vector3_Zero);

	int animenum = (int)(90.0f * animation_rate);

	Vector3 pos = Vector3_Zero;
	pos.x += 1280.0f / 2.0f;
	pos.y = 10.0f;


	int rect_right = (int)((float)this->GAUGE_HEIGHT_ * this->draw_lifepersent_);

	SpriteBatch.Draw(*this->lifegauge_sprite_,pos,
		RectWH((animenum % 3) * this->GAUGE_WIDTH_, (animenum / 3) * this->GAUGE_HEIGHT_, this->GAUGE_WIDTH_, rect_right)
		,1.0f);

}