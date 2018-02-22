#include "../../StdAfx.h"
#include "TITLE_SCENE.hpp"
#include "../../MyMakeClasses/ImageFont.h"
#include "../../MyMakeClasses/CONTROLL.h"

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load any non-graphic
/// related content.  Calling base.Initialize will enumerate through any components
/// and initialize them as well.
/// </summary>
bool TITLE_SCENE::Initialize()
{
	// TODO: Add your initialization logic here

	this->titlelogo_ = GraphicsDevice.CreateSpriteFromFile(_T("title_logo.png"));
	this->movie_ = MediaManager.CreateMediaFromFile(_T("title_movie.wmv"));
	this->movie_->Play();

	this->state_ = TITLE_SCENE::WAIT;

	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void TITLE_SCENE::Finalize()
{
	// TODO: Add your finalization logic here
	GraphicsDevice.ReleaseSprite(this->titlelogo_);
	MediaManager.ReleaseMedia(this->movie_);


}

/// <summary>
/// Allows the game to run logic such as updating the world,
/// checking for collisions, gathering input, and playing audio.
/// </summary>
/// <returns>
/// Scene continued value.
/// </returns>
int TITLE_SCENE::Update()
{
    // TODO: Add your update logic here

	CONTROLL::GetInstance().Update();

	int isfinish = this->fade_.Update();

	if (this->state_ == TITLE_SCENE::START && isfinish){

		return GAME_SCENE(new MUSICSELECT_SCENE());

	} else if(this->state_ != TITLE_SCENE::START){

	if (CONTROLL::GetInstance().BufferIsPress(LEFT)||
		CONTROLL::GetInstance().BufferIsPress(CENTER) || 
		CONTROLL::GetInstance().BufferIsPress(RIGHT)){

		this->state_ = TITLE_SCENE::START;
		this->fade_.SetFadeState(FadeDisplay::FADEOUT);

		}
		
	}

	if (this->movie_->IsComplete()){

		this->movie_->Replay();

	}

	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void TITLE_SCENE::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_Black);

	GraphicsDevice.BeginScene();

	SpriteBatch.Begin();

	SpriteBatch.Draw(*this->movie_, Vector3_Zero, 0.5f);
	SpriteBatch.Draw(*this->titlelogo_, Vector3_Zero);

	SpriteBatch.End();

	Vector2 cellsize = IMAGEFONT.GetCellSize() / 2.0f;
	Vector2 drawsize = IMAGEFONT.GetDrawSize(cellsize,"PUSH BUTTON TO START");

	Vector3 pos = Vector3_Zero;
	pos.x = (1280.0f - drawsize.x) / 2.0f;
	pos.y = 480.0f + (240.0f - drawsize.y) / 2.0f;

	IMAGEFONT.DirectDrawImageString(pos,cellsize,Color(255,255,255),"PUSH BUTTON TO START");

	this->fade_.Draw();

	GraphicsDevice.EndScene();
}
