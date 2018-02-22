#include "SelectHighSpeed.h"
#include "../ImageFont.h"

SelectHighSpeed::SelectHighSpeed(){

	this->sprite_ = GraphicsDevice.CreateSpriteFromFile(_T("musicselect/high_speed.png"));
	this->plussound_ = SoundDevice.CreateSoundFromFile(_T("musicselect/sound/highspeed.wav"));
	this->minussound_ = SoundDevice.CreateSoundFromFile(_T("musicselect/sound/lospeed.wav"));
	this->speedcount_ = 0;

}

SelectHighSpeed::~SelectHighSpeed(){

	GraphicsDevice.ReleaseSprite(this->sprite_);

	SoundDevice.ReleaseSound(this->plussound_);
	SoundDevice.ReleaseSound(this->minussound_);

}

void SelectHighSpeed::PlusCount(){

	this->speedcount_++;

	if (this->speedcount_ > 8){

		this->speedcount_ = 8;

	}

	this->plussound_->Play();

}

void SelectHighSpeed::MinusCount(){

	this->speedcount_--;

	if (this->speedcount_ < -8){

		this->speedcount_ = -8;

	}

	this->minussound_->Play();

}

void SelectHighSpeed::Draw(){

	SPRITE sp = this->sprite_;

	Vector3 pos = Vector3_Zero;
	pos.y = 720.0f - 100.0f; //100ÇÕâÊëúÇÃècïù

	SpriteBatch.Begin();

	SpriteBatch.Draw(*sp,pos);

	SpriteBatch.End();

	pos.x += 5.0f;
	pos.y -= 15.0f;

	Vector2 cellsize = IMAGEFONT.GetCellSize();
	Color color = Color(255, 255, 255);

	for (int i = -8; i <= 8;i++){

		if (i == this->speedcount_){

			pos.x += (cellsize.x * 0.7f);
			continue;

		}
		if (i > 0){

			color = Color(1.0f, 0.5f, 0.5f,0.3f);

		}
		if (i < 0){

			color = Color(0.5f, 0.5f, 1.0f,0.3f);

		}
		if (i == 0){

			color = Color(1.0f, 1.0f, 1.0f,0.3f);

		}

		IMAGEFONT.DirectDrawImageString(pos, cellsize, color, "%d", i);

		pos.x += (cellsize.x * 0.7f);

	}

	pos = Vector3_Zero;
	pos.y = 720.0f - 100.0f; //100ÇÕâÊëúÇÃècïù
	pos.x += 5.0f;
	pos.y -= 15.0f;

	int num = 8 + this->speedcount_;

	pos.x += (cellsize.x * 0.7f) * num;


	if (this->speedcount_ > 0){

		color = Color(1.0f, 0.7f, 0.7f);

	}
	if (this->speedcount_ < 0){

		color = Color(0.7f, 0.7f, 1.0f);

	}
	if (this->speedcount_ == 0){

		color = Color(1.0f, 1.0f, 1.0f);

	}

	IMAGEFONT.DirectDrawImageString(pos, cellsize, color, "%d", this->speedcount_);


}