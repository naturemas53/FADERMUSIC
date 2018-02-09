#include "FlashBomb.h"

SPRITE FlashBomb::sprite_ = nullptr;

FlashBomb::FlashBomb(): AbstructBomb(350,1,1,Vector2(16.0f,50.0f))
{

	if (this->sprite_ == nullptr){

		this->sprite_ = GraphicsDevice.CreateSpriteFromFile(_T("bomb/justline.png"));

	}

	this->pos_ = Vector3_Zero;
	this->useflag_ = true;
	this->time_ = 0;
	this->movement_y_ = 0.0f;

}

FlashBomb::~FlashBomb(){

	if (this->sprite_ != nullptr){

		GraphicsDevice.ReleaseSprite(this->sprite_);
		this->sprite_ = nullptr;
	}

}

void FlashBomb::Init(Vector3 faderpos, Vector2 faderinner, float height){

	this->pos_ = Vector3_Zero;
	this->useflag_ = true;
	this->time_ = 0;

	faderinner.y -= this->CELLSIZE_.y;

	this->pos_.y = faderinner.y * height;
	this->pos_ += faderpos;

	this->right_xpos_ = this->pos_.x + faderinner.x;
	this->movement_y_ = 0.0f;
}

int FlashBomb::Update(int elapsedtime){

	this->time_ += elapsedtime;

	float timerate;

	if (this->time_ > this->ANIMETIME_){

		this->movement_y_ = 720.0f;

		return 1;

	}

	timerate = (float)this->time_ / (float)this->ANIMETIME_;

	this->movement_y_ = timerate * 720.0f;

	return 0;

}

void FlashBomb::Draw(){

	GraphicsDevice.SetBlendMode(DXGBLEND_ADD);
	SpriteBatch.Begin();

	Vector3 basepos = this->pos_;
	SPRITE sp = this->sprite_;
	Color color = Color(1.0f,1.0f,1.0f);

	Vector3 pos = basepos;
	pos.x -= this->CELLSIZE_.x;
	pos.x += 3.0f;
	pos.y += this->movement_y_;

	SpriteBatch.Draw(*sp, pos, color);

	pos.y += this->movement_y_ * -2.0f;
	SpriteBatch.Draw(*sp, pos, color);

	pos = basepos;
	pos.x = this->right_xpos_;
	pos.x -= 5.0f;
	pos.y += this->movement_y_;
	SpriteBatch.Draw(*sp, pos, color);

	pos.y += this->movement_y_ * -2.0f;
	SpriteBatch.Draw(*sp, pos, color);

	SpriteBatch.End();
	GraphicsDevice.SetBlendMode(DXGBLEND_NORMAL);

}