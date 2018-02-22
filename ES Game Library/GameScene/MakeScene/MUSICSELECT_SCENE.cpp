#include "MUSICSELECT_SCENE.hpp"
#include "../../StdAfx.h"
#include "../SceneShared.hpp"
#include "../../MyMakeClasses/ImageFont.h"
#include "../../MyMakeClasses/CONTROLL.h"
#include <string>
#include <locale> 
#include <codecvt> 
#include <cstdio>

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load any non-graphic
/// related content.  Calling base.Initialize will enumerate through any components
/// and initialize them as well.
/// </summary>
bool MUSICSELECT_SCENE::Initialize()
{
	// TODO: Add your initialization logic here

	//if (!this->FileRead()) return false;

	this->datamanager_ = new MusicDataManager();
	this->highspeed_ = new SelectHighSpeed();
	this->difficulty_ = new Difficulty();
	this->context_ = new Context(this->datamanager_,this->highspeed_,this->difficulty_);

	this->titlebar_ = GraphicsDevice.CreateSpriteFromFile(_T("musicselect/music_select.png"));
	this->stick_ = GraphicsDevice.CreateSpriteFromFile(_T("musicselect/stick.png"));

	this->mouse_y_ = 4500 / 2;
	this->state_ = MUSICSELECT_SCENE::SELECTNOW;
	this->time_ = 0;

	this->screen_ = GraphicsDevice.CreateRenderTarget(1280,720,PixelFormat_RGBA8888,DepthFormat_Unknown);

	this->movie_ = MediaManager.CreateMediaFromFile(_T("title_movie.wmv"));
	this->movie_->Play();

	this->bgm_ = SoundDevice.CreateSoundFromFile(_T("musicselect/musicselect_bgm.wav"));
	this->bgm_->PlayLooping();

	this->desidese_ = SoundDevice.CreateSoundFromFile(_T("musicselect/sound/deside.wav"));

	return this->datamanager_->Initialize();
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void MUSICSELECT_SCENE::Finalize()
{
	// TODO: Add your finalization logic here
	delete this->datamanager_;
	delete this->highspeed_;
	delete this->context_;
	delete this->difficulty_;

	GraphicsDevice.ReleaseSprite(this->titlebar_);
	GraphicsDevice.ReleaseSprite(this->stick_);
	MediaManager.ReleaseMedia(this->movie_);
	GraphicsDevice.ReleaseRenderTarget(this->screen_);
	SoundDevice.ReleaseSound(this->bgm_);
	SoundDevice.ReleaseSound(this->desidese_);
}

/// <summary>
/// Allows the game to run logic such as updating the world,
/// checking for collisions, gathering input, and playing audio.
/// </summary>
/// <returns>
/// Scene continued value.
/// </returns>
int MUSICSELECT_SCENE::Update()
{
    // TODO: Add your update logic here

	CONTROLL::GetInstance().Update();

	IMAGEFONT.SrtingReset();

	MouseState mouse = Mouse->GetState();

	this->mouse_y_ += mouse.Y;
	if (this->mouse_y_ == 0)this->mouse_y_ = 1;

	float mouseheight = (float)this->mouse_y_ / 4500.0f;
	if (mouseheight < 0.0f) {
		mouseheight = 0.0f;
		this->mouse_y_ = 1;
	}
	if (mouseheight > 1.0f){
		mouseheight = 1.0f;
		this->mouse_y_  = 4500;
	}
	if (this->state_ != MUSICSELECT_SCENE::DESIDE){
		this->context_->Update(mouseheight, GameTimer.GetElapsedMilliSecond());
		if (context_->IsDeside()){

			this->SongDeside();
			this->bgm_->Stop();
			this->desidese_->Play();

		}
	}
	else{

		this->time_ += GameTimer.GetElapsedMilliSecond();

	}

	this->datamanager_->Update(GameTimer.GetElapsedMilliSecond());

	int isfinish = this->fade_.Update();

	if (this->state_ == MUSICSELECT_SCENE::DESIDE && isfinish){

		return GAME_SCENE(new SONGPLAY_SCENE());

	}

	if (this->movie_->IsComplete()){

		this->movie_->Replay();

	}

	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void MUSICSELECT_SCENE::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_Black);

	GraphicsDevice.BeginScene();

	if (this->state_ == MUSICSELECT_SCENE::DESIDE){

		GraphicsDevice.SetRenderTarget(this->screen_);
		GraphicsDevice.Clear(Color_Black);
	}

	SpriteBatch.Begin();
	SpriteBatch.Draw(*this->movie_, Vector3_Zero,0.5f);
	SpriteBatch.End();

	this->datamanager_->Draw(); 
	this->difficulty_->Draw();
	this->context_->Draw();

	float mouseheight = (float)this->mouse_y_ / 4500.0f;
	if (mouseheight < 0.0f) mouseheight = 0.0f;
	if (mouseheight > 1.0f) mouseheight = 1.0f;

	float height = 520.0f - 20.0f; //560　は長方形のやつのたて　20は棒の縦

	Vector3 pos = Vector3_Zero;
	pos.x = 1280.0f - 100.0f; // 100　は長方形の横
	pos.y = 100.0f + (height * mouseheight);
	SpriteBatch.Begin();
	SpriteBatch.Draw(*this->stick_, pos);
	SpriteBatch.End();

	IMAGEFONT.DrawString(1.0f);

	this->highspeed_->Draw();
	SpriteBatch.Begin();
	SpriteBatch.Draw(*this->titlebar_,Vector3_Zero);
	SpriteBatch.End();

	if (this->state_ == MUSICSELECT_SCENE::DESIDE){

		GraphicsDevice.SetDefaultRenderTarget();

		float timerate = (float)this->time_ / 100.0f;

		float scale = 1.0f + timerate;

		SpriteBatch.Begin();
		SpriteBatch.Draw(*this->screen_, Vector3_Zero,Color(255,255,255),Vector3_Zero,
			Vector3(1280.0f / 2.0f,720.0f / 2.0f,0.0f),scale);
		SpriteBatch.End();


	}

	fade_.Draw();

	GraphicsDevice.EndScene();
}

void MUSICSELECT_SCENE::SongDeside(){

	SongData data = this->datamanager_->GetSelectData();
	int highspeedcount = this->highspeed_->GetSpeedCount();
	SceneShared().SetIntegerForKey("SPEEDCOUNT",highspeedcount);
	LEVEL level = this->difficulty_->GetLevel();

	//char* filename = new char[512];

	std::string buf;
	std::wstring sendname;
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;

	std::string songname = data.songname;
	std::string difficulty;

	switch (level){
	case LO: difficulty = "lo"; break;
	case MID: difficulty = "mid"; break;
	case HIGH: difficulty = "high"; break;
	}

	char cbuf[512] = {};

	sprintf(cbuf, "musics/%s/%s.txt", songname.c_str(), difficulty.c_str());
	SceneShared().SetStringForKey("MUSICSCORE", cbuf);

	sprintf(cbuf, "musics/%s/music.wav", songname.c_str());
	buf = cbuf;
	sendname = cv.from_bytes(buf);
	SceneShared().SetWStringForKey("MUSIC", sendname);

	sprintf(cbuf, "musics/%s/movie.wmv", songname.c_str());
	buf = cbuf;
	sendname = cv.from_bytes(buf);
	SceneShared().SetWStringForKey("MOVIE", sendname);

	this->fade_.SetFadeState(FadeDisplay::FADEOUT);

	this->state_ = MUSICSELECT_SCENE::DESIDE;

	//delete filename;

}