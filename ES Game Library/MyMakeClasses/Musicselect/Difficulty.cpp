#include "Difficulty.h"
#include "../ImageFont.h"

Difficulty::Difficulty(){

	this->level_ = LO;

	this->sprite_[LO] = GraphicsDevice.CreateSpriteFromFile(_T("musicselect/LO.png"));
	this->sprite_[MID] = GraphicsDevice.CreateSpriteFromFile(_T("musicselect/MID.png"));
	this->sprite_[HIGH] = GraphicsDevice.CreateSpriteFromFile(_T("musicselect/HIGH.png"));

	this->sound_ = SoundDevice.CreateSoundFromFile(_T("musicselect/sound/difficult.wav"));

}

Difficulty::~Difficulty(){

	for (auto sprite: this->sprite_){

		GraphicsDevice.ReleaseSprite(sprite.second);

	}

	SoundDevice.ReleaseSound(this->sound_);

}

void Difficulty::Draw(){

	Vector2 cellsize = IMAGEFONT.GetCellSize() / 4.0f;

	Vector3 pos = Vector3_Zero;
	pos.y = 100.0f;
	pos.x += 5.0f;

	IMAGEFONT.SetImageString(pos,cellsize,Color(255,255,255),false,"NOW SELECT");

	pos.y += cellsize.y;
	SPRITE sp = this->sprite_[this->level_];

	SpriteBatch.Begin();
	SpriteBatch.Draw(*sp,pos);
	SpriteBatch.End();

}