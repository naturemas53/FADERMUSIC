#include "LongBomb.h"

std::map<Color_by_Name, SPRITE>* LongBomb::sprites_ = nullptr;

LongBomb::LongBomb() : AbstructBomb(200,5,10,Vector2(100.0f,100.0f)){

	if (this->sprites_ == nullptr){

		this->sprites_ = new std::map<Color_by_Name, SPRITE>;

		(*this->sprites_)[Color_Red] = GraphicsDevice.CreateSpriteFromFile(_T("bomb/LongNoteBomb/longnote_efect_R.png"));
		(*this->sprites_)[Color_Green] = GraphicsDevice.CreateSpriteFromFile(_T("bomb/LongNoteBomb/longnote_efect_G.png"));
		(*this->sprites_)[Color_Blue] = GraphicsDevice.CreateSpriteFromFile(_T("bomb/LongNoteBomb/longnote_efect_B.png"));

	}

	this->time_ = 0;
	this->mycolor_ = Color_Red;
	this->useflag_ = true;

}

LongBomb::~LongBomb(){

	if (this->sprites_ != nullptr){

		for (auto sprite : (*this->sprites_)){

			GraphicsDevice.ReleaseSprite(sprite.second);

		}


		delete this->sprites_;
		this->sprites_ = nullptr;

	}

}

void LongBomb::Init(Vector3 fader_pos, Vector2 inner_size, float height, Color_by_Name color){

	this->pos_ = fader_pos;
	this->pos_.y += inner_size.y * height;
	this->pos_.y -= this->CELLSIZE_.y / 2.0f;
	this->pos_.x += (inner_size.x - this->CELLSIZE_.x) / 2.0f;

	this->time_ = 0;
	this->mycolor_ = color;
	this->useflag_ = true;

}
int LongBomb::Update(int elapsedtime){

	this->time_ += elapsedtime;

	if (this->time_ > this->ANIMETIME_){

		return 1;

	}

	return 0;

}

void LongBomb::Draw(){

	float timerate = (float)this->time_ / (float)this->ANIMETIME_;
	int cellcount = (int)((float)this->MAXCELL_ * timerate);

	int rectleft = cellcount % this->HOLIZONCELL_ *  (int)this->CELLSIZE_.x;
	int recttop = cellcount / this->HOLIZONCELL_ *  (int)this->CELLSIZE_.y;

	RectWH userect = RectWH(rectleft, recttop, (int)this->CELLSIZE_.x, (int)this->CELLSIZE_.y);

	SPRITE sp = (*this->sprites_)[this->mycolor_];
	Color color = Color(1.0f, 1.0f, 1.0f);
	Vector2 cellsize = this->CELLSIZE_;

	SpriteBatch.Begin();
	SpriteBatch.Draw(*sp, this->pos_, userect, color, Vector3_Zero, Vector3(cellsize.x / 2.0f, cellsize.y / 2.0f, 0.0f), Vector2_One * 3.0f);
	SpriteBatch.End();

	GraphicsDevice.SetBlendMode(DXGBLEND_ADD);
	SpriteBatch.Begin();

	color.A(0.5f);
	SpriteBatch.Draw(*sp, this->pos_, userect, color, Vector3_Zero, Vector3(cellsize.x / 2.0f, cellsize.y / 2.0f, 0.0f), Vector2_One *  3.0f);

	SpriteBatch.End();
	GraphicsDevice.SetBlendMode(DXGBLEND_NORMAL);

}