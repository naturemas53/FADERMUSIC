#include "../../StdAfx.h"
#include "THANK_SCENE.hpp"
#include "../../MyMakeClasses/CONTROLL.h"

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load any non-graphic
/// related content.  Calling base.Initialize will enumerate through any components
/// and initialize them as well.
/// </summary>
bool THANK_SCENE::Initialize()
{
	// TODO: Add your initialization logic here

	this->thankyousprite_ = GraphicsDevice.CreateSpriteFromFile(_T("THANKS.png"));
	this->bgm_ = SoundDevice.CreateSoundFromFile(_T("thankyou_bgm.wav"));
	this->bgm_->PlayLooping();

	this->time_ = 0;
	this->nextflag_ = false;

	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void THANK_SCENE::Finalize()
{
	// TODO: Add your finalization logic here
	GraphicsDevice.ReleaseSprite(this->thankyousprite_);
	SoundDevice.ReleaseSound(this->bgm_);
}

/// <summary>
/// Allows the game to run logic such as updating the world,
/// checking for collisions, gathering input, and playing audio.
/// </summary>
/// <returns>
/// Scene continued value.
/// </returns>
int THANK_SCENE::Update()
{
    // TODO: Add your update logic here
	CONTROLL::GetInstance().Update();

	int isfinish = this->fade_.Update();

	this->time_ += GameTimer.GetElapsedMilliSecond();

	if (isfinish && this->nextflag_){

		this->bgm_->Stop();
		return GAME_SCENE(new TITLE_SCENE());

	}

	if ((this->time_ > 10000 || this->IsPush()) && !this->nextflag_){

		this->nextflag_ = true;
		this->fade_.SetFadeState(FadeDisplay::FADEOUT);

	}

	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void THANK_SCENE::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();

	SpriteBatch.Begin();

	SpriteBatch.Draw(*this->thankyousprite_,Vector3_Zero);

	SpriteBatch.End();

	this->fade_.Draw();

	GraphicsDevice.EndScene();
}

bool THANK_SCENE::IsPush(){

	if (CONTROLL::GetInstance().BufferIsPress(LEFT) ||
		CONTROLL::GetInstance().BufferIsPress(CENTER) ||
		CONTROLL::GetInstance().BufferIsPress(RIGHT)){

		return true;

	}

	return false;
}