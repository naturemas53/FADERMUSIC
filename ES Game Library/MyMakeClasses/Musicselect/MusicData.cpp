#include "MusicData.h"
#include "../ImageFont.h"

SPRITE MusicData::backsprite_ = nullptr;
std::map<LEVEL, SPRITE>* MusicData::levelsprites_ = nullptr;

//1086 ‰æ‘œ‰¡@964 Žl•ÓŒ`‰¡

MusicData::MusicData(SongData data):
IMAGESIZE_(Vector2(1086.0f,200.0f)),
HORNSIZE_(Vector2(122.0f, 200.0f)),
INNER_X_(1086.0f - 122.0f){

	if (this->backsprite_ == nullptr){

		this->backsprite_ = GraphicsDevice.CreateSpriteFromFile(_T("musicselect/musictitle.png"));

	}

	if (this->levelsprites_ == nullptr){

		this->levelsprites_ = new map<LEVEL, SPRITE>;

		(*this->levelsprites_)[LO] = GraphicsDevice.CreateSpriteFromFile(_T("musicselect/LO.png"));
		(*this->levelsprites_)[MID] = GraphicsDevice.CreateSpriteFromFile(_T("musicselect/MID.png"));
		(*this->levelsprites_)[HIGH] = GraphicsDevice.CreateSpriteFromFile(_T("musicselect/HIGH.png"));

	}

	this->data_ = data;

}

MusicData::~MusicData(){

	if (this->backsprite_ != nullptr){

		GraphicsDevice.ReleaseSprite(this->backsprite_);

		this->backsprite_ = nullptr;

	}

	if (this->levelsprites_ == nullptr){

		for (auto sprite : (*this->levelsprites_) ){

			GraphicsDevice.ReleaseSprite(sprite.second);

		}

		delete this->levelsprites_;
		this->levelsprites_ = nullptr;

	}

}

void MusicData::Draw(Vector3 basepos, bool ismain){

	Color color = Color(255, 255, 255,255);

	if (!ismain) color.A(0.3f);

	Vector3 pos = basepos;
	SPRITE backsp = this->backsprite_;

	SpriteBatch.Begin();

	SpriteBatch.Draw(*backsp,pos,color);

	SpriteBatch.End();

	this->DataDraw(basepos,color);

}

void MusicData::DataDraw(Vector3 basepos, Color color){

	SPRITE sp;
	Color localcolor;

	Vector3 pos = basepos;

	Vector2 cellsize = IMAGEFONT.GetCellSize();
	Vector2 drawsize = IMAGEFONT.GetDrawSize(cellsize,this->data_.songname.c_str());

	float plusx = (this->INNER_X_ - drawsize.x) / 2.0f;

	pos.x += this->HORNSIZE_.x + plusx;
	pos.y -= 10.0f;

	IMAGEFONT.SetImageString(pos, cellsize, color, false,this->data_.songname.c_str());

	pos = basepos;
	pos.y += 100.0f;

	float halfhorn = this->HORNSIZE_.x / 2.0f - 10.0f;

	pos.x += halfhorn;
	sp = (*this->levelsprites_)[LO];

	SpriteBatch.Begin();

	SpriteBatch.Draw(*sp, pos, color);

	SpriteBatch.End();

	localcolor = color;
	localcolor.R(0.7f);
	localcolor.G(0.7f);
	localcolor.B(1.0f);

	IMAGEFONT.SetImageString(Vector3(pos.x + 200.0f,pos.y - 20.0f,pos.z),cellsize,localcolor,false,
		"%d",this->data_.level.lo);


	pos.x += this->INNER_X_ / 3.0f;
	sp = (*this->levelsprites_)[MID];

	SpriteBatch.Begin();

	SpriteBatch.Draw(*sp, pos, color);

	SpriteBatch.End();

	localcolor = color;
	localcolor.R(0.5f);
	localcolor.G(1.0f);
	localcolor.B(0.5f);

	IMAGEFONT.SetImageString(Vector3(pos.x + 200.0f, pos.y - 20.0f, pos.z), cellsize, localcolor, false,
		"%d", this->data_.level.mid);


	pos.x += this->INNER_X_ / 3.0f;
	sp = (*this->levelsprites_)[HIGH];

	SpriteBatch.Begin();

	SpriteBatch.Draw(*sp, pos, color);

	SpriteBatch.End();

	localcolor = color;
	localcolor.R(1.0f);
	localcolor.G(0.5f);
	localcolor.B(0.5f);

	IMAGEFONT.SetImageString(Vector3(pos.x + 200.0f, pos.y - 20.0f, pos.z), cellsize, localcolor,false,
		"%d", this->data_.level.high);

}