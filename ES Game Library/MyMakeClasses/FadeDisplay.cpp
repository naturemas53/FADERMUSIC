#include "FadeDisplay.h"

FadeDisplay::FadeDisplay(FADESTATE startstate) :
MAXCOUNT_(50){

	this->blackscreen_ = GraphicsDevice.CreateRenderTarget(1280,720,PixelFormat_RGBA8888,DepthFormat_Unknown);
	GraphicsDevice.SetRenderTarget(this->blackscreen_);
	GraphicsDevice.Clear(Color_Black);
	GraphicsDevice.SetDefaultRenderTarget();
	
	this->fadestate_ = startstate;

	switch (this->fadestate_){

	case FADEIN:

		this->count_ = this->MAXCOUNT_;

		break;

	case FADEOUT:

		this->count_ = 0;

		break;

	default:
		break;


	}

}

FadeDisplay::~FadeDisplay(){

	GraphicsDevice.ReleaseRenderTarget(this->blackscreen_);

}

int FadeDisplay::Update(){

	switch (this->fadestate_){

	case FADEIN:

		this->count_--;
		if (this->count_ < 0){

			this->count_ = 0;
			return 1;
		}

		break;

	case FADEOUT:

		this->count_++;
		if (this->count_ >= this->MAXCOUNT_){

			this->count_ = this->MAXCOUNT_;
			return 1;
		}

		break;

	default:
		break;


	}

	return 0;

}

void FadeDisplay::Draw(){

	RENDERTARGET screen = this->blackscreen_;

	float alpha = (float)this->count_ / (float)(this->MAXCOUNT_ - 20);
	if (alpha >= 1.0f) alpha = 1.0f;

	Color color = Color(1.0f, 1.0f, 1.0f, alpha);

	SpriteBatch.Begin();
	SpriteBatch.Draw(*screen, Vector3_Zero, color);
	SpriteBatch.End();

}