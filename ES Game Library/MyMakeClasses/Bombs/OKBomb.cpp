#include "OKBomb.h"

SPRITE OKBomb::sprite_ = nullptr;

OKBomb::OKBomb() : JudgeBomb(250, 5, 5, Vector2(120.0f, 120.0f), OK){

	if (this->sprite_ == nullptr){

		this->sprite_ = GraphicsDevice.CreateSpriteFromFile(_T("bomb/blue_bomb.png"));

	}

}

OKBomb::~OKBomb(){

	if (this->sprite_ != nullptr){

		GraphicsDevice.ReleaseSprite(this->sprite_);
		this->sprite_ = nullptr;

	}

}

void OKBomb::Init(Vector3 faderpos, Vector2 fader_inner, float height){

	this->pos_ = faderpos;
	this->pos_.y += fader_inner.y * height;
	this->pos_.y -= this->CELLSIZE_.y / 2.0f;
	this->pos_.x += (fader_inner.x - this->CELLSIZE_.x) / 2.0f;

	this->time_ = 0;
	this->useflag_ = true;

}

int OKBomb::Update(int elapsedtime){

	this->time_ += elapsedtime;

	if (this->time_ > this->ANIMETIME_){

		return 1;

	}

	return 0;

}

void OKBomb::Draw(){

	float timerate = (float)this->time_ / (float)this->ANIMETIME_;
	int cellcount = (int)((float)this->MAXCELL_ * timerate);

	int rectleft = cellcount % this->HOLIZONCELL_ *  (int)this->CELLSIZE_.x;
	int recttop = cellcount / this->HOLIZONCELL_ *  (int)this->CELLSIZE_.y;

	RectWH userect = RectWH(rectleft, recttop, (int)this->CELLSIZE_.x, (int)this->CELLSIZE_.y);

	SPRITE sp = this->sprite_;
	Color color = Color(1.0f, 1.0f, 1.0f);
	Vector2 cellsize = this->CELLSIZE_;

	SpriteBatch.Begin();
	SpriteBatch.Draw(*sp, this->pos_, userect, color, Vector3_Zero, Vector3(cellsize.x / 2.0f, cellsize.y / 2.0f, 0.0f), Vector2_One * 1.5f);
	SpriteBatch.End();

	GraphicsDevice.SetBlendMode(DXGBLEND_ADD);
	SpriteBatch.Begin();

	color.A(0.5f);
	sp = this->addsprite_;
	SpriteBatch.Draw(*sp, this->pos_, userect, color, Vector3_Zero, Vector3(cellsize.x / 2.0f, cellsize.y / 2.0f, 0.0f), Vector2_One * 1.5f);

	SpriteBatch.End();
	GraphicsDevice.SetBlendMode(DXGBLEND_NORMAL);

}