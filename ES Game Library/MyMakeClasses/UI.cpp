#include "UI.h"
#include "JUDGELIST_ENUM.h"
#include "ImageFont.h"

UI::UI() :
FRAME_SIZE_(Vector2(600.0f, 52.0f)),
INNER_SIZE_(Vector2(582.0f, 37.0f)),
ANIMECOUNT_(30),
CELLCOUNT_(2)
{

	this->uiline_ = GraphicsDevice.CreateSpriteFromFile(_T("sideui/score_back.png"));

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

	GraphicsDevice.ReleaseSprite(this->uiline_);
	GraphicsDevice.ReleaseSprite(this->framesp_);
	GraphicsDevice.ReleaseSprite(this->innersp_);

}

void UI::Update(){

	this->nowcount_++;

	int maxcount = this->ANIMECOUNT_ * this->CELLCOUNT_;

	if (this->nowcount_ >= maxcount ){

		this->nowcount_ = 0;

	}

}

void UI::Draw(float animationrate){

	SpriteBatch.Begin();
	SPRITE sp = this->uiline_;

	SpriteBatch.Draw(*sp,Vector3_Zero,1.0f);

	//sp = this->rightuiline_;

	Vector3 pos = Vector3_Zero;
	pos.x = 1280.0f - 293.0f;

	SpriteBatch.Draw(*sp, pos, Color(255,255,255),Vector3_Zero,Vector3(293.0f / 2.0f,0.0f,0.0f),Vector2(-1.0f,1.0f));
	SpriteBatch.End();

	int animenum = (int)(90.0f * animationrate);

	Vector2 middlecellsize = IMAGEFONT.GetCellSize() / 2.0f;
	Vector2 smollcellsize = IMAGEFONT.GetCellSize() / 4.0f;
	Vector2 drawsize = Vector2_Zero;

	drawsize = IMAGEFONT.GetDrawSize(smollcellsize,"SCORE");
	IMAGEFONT.SetImageString(Vector3(5.0f, 5.0f, 0.0f), smollcellsize, Color(255, 255, 255), true, "SCORE");
	IMAGEFONT.SetImageString(Vector3(15.0f, 5.0f + drawsize.y + -20.0f, 0.0f), middlecellsize,
		Color(255, 255, 128), true, "%08d", this->draw_score_);

	drawsize = IMAGEFONT.GetDrawSize(smollcellsize, "ACCURACY");
	IMAGEFONT.SetImageString(Vector3(1280.0f - 280.0f + 10.0f, 5.0f, 0.0f), smollcellsize, Color(255, 255, 255), true, "ACCURACY");
	float smollacuracy_y = drawsize.y;
	drawsize = IMAGEFONT.GetDrawSize(middlecellsize, "%06d", this->draw_accuracy_);
	IMAGEFONT.SetImageString(Vector3(1280.0f - drawsize.x - 5.0f, 5.0f + smollacuracy_y + -20.0f, 0.0f),
		middlecellsize,Color(128, 255, 255), true, "%06d", this->draw_accuracy_);

	drawsize = IMAGEFONT.GetDrawSize(smollcellsize, "MAXCOMBO %4d", this->draw_maxcombo_);
	IMAGEFONT.SetImageString(Vector3(274.0f - drawsize.x, 72.0f, 0.0f), smollcellsize, Color(255, 255, 255), false, "MAXCOMBO %4d", this->draw_maxcombo_);

	this->LifeGaugeDraw(animationrate);

}

void UI::LifeGaugeDraw(float animationrate){

	this->FrameDraw(animationrate);
	this->GaugeDraw(animationrate);

}

void UI::FrameDraw(float animationrate){

	Vector2 framesize = this->FRAME_SIZE_;
	SPRITE sp = this->framesp_;
	float pos_x = (1280.0f - framesize.x) / 2.0f;
	RectWH userect = RectWH(0, 0, this->FRAME_SIZE_.x, this->FRAME_SIZE_.y);

	SpriteBatch.Begin();
	SpriteBatch.Draw(*sp, Vector3(pos_x, 20.0f, 0.0f),userect, 1.0f);
	SpriteBatch.End();

	if (this->draw_lifepersent_ >= 1.0f){

		GraphicsDevice.SetBlendMode(DXGBLEND_ADD);
		SpriteBatch.Begin();

		userect.top += this->FRAME_SIZE_.y;
		userect.bottom += this->FRAME_SIZE_.y;

		Color color = Color(1.0f, 1.0f, 1.0f, 0.7f * animationrate);

		SpriteBatch.Draw(*sp, Vector3(pos_x, 20.0f, 0.0f), userect, color);

		SpriteBatch.End();
		GraphicsDevice.SetBlendMode(DXGBLEND_NORMAL);

	}

}

void UI::GaugeDraw(float animationrate){

	Vector2 framesize = this->FRAME_SIZE_;
	Vector2 innersize = this->INNER_SIZE_;

	int rect_right = (int)(innersize.x * this->draw_lifepersent_);

	float pos_x = (1280.0f - framesize.x) / 2.0f;
	SPRITE sp = this->innersp_;

	SpriteBatch.Begin();

	int animecount = this->nowcount_ / this->CELLCOUNT_;

	RectWH userect = RectWH(0, innersize.y * animecount, rect_right, (int)innersize.y);
	float plus_x = (framesize.x - innersize.x) / 2.0f;
	float plus_y = (framesize.y - innersize.y) / 2.0f;
	sp = this->innersp_;

	SpriteBatch.Draw(*sp, Vector3(pos_x + plus_x, 20.0f + plus_y, 0.0f), userect, 1.0f);
	SpriteBatch.End();

	GraphicsDevice.SetBlendMode(DXGBLEND_ADD);
	SpriteBatch.Begin();

	float pal = (this->draw_lifepersent_ >= 1.0f) ? 0.2f + (0.3f * animationrate) : 0.3f * animationrate;
	userect = RectWH(innersize.x, innersize.y * animecount, rect_right, (int)innersize.y);

	Color color = Color(0.5f, 1.0f, 1.0f, pal);

	SpriteBatch.Draw(*sp, Vector3(pos_x + plus_x, 20.0f + plus_y, 0.0f), userect, color);

	SpriteBatch.End();
	GraphicsDevice.SetBlendMode(DXGBLEND_NORMAL);

}

void UI::SetDisplayData(int score, float life, int accuracy, int allnotes, int maxcombo){

	this->draw_lifepersent_ = life;
	this->draw_score_ = score;

	this->draw_accuracy_ = (int)(100000.0f * ((float)accuracy / (float)(allnotes * 100)) );
	this->draw_maxcombo_ = maxcombo;

}
