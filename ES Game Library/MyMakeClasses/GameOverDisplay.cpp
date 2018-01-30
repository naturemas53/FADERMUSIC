#include "GameOverDisplay.h"

GameOverDisplay::GameOverDisplay(){

	//this->alpha_ = 0.0f;
	this->blackscreen_ = GraphicsDevice.CreateRenderTarget(1280,720,PixelFormat_RGBA8888,DepthFormat_Unknown);
	GraphicsDevice.SetRenderTarget(this->blackscreen_);
	GraphicsDevice.Clear(Color_Black);
	GraphicsDevice.SetDefaultRenderTarget();
	
	this->count_ = 0;
}

GameOverDisplay::~GameOverDisplay(){



}

int GameOverDisplay::Update(){

	this->count_++;

	if (this->count_ >= 100){

		return 1;

	}

	return 0;

}

void GameOverDisplay::Draw(){

	RENDERTARGET screen = this->blackscreen_;

	float alpha = (float)this->count_ / 100.0f;
	if (alpha >= 1.0f) alpha = 1.0f;

	SpriteBatch.Begin();
	SpriteBatch.Draw(*screen, Vector3_Zero, alpha);
	SpriteBatch.End();

}