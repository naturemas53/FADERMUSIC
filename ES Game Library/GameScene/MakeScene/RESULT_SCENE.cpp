#include "../../StdAfx.h"
#include "RESULT_SCENE.hpp"
#include "../../MyMakeClasses/CONTROLL.h"
#include "../../MyMakeClasses/ImageFont.h"
#include <string>

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load any non-graphic
/// related content.  Calling base.Initialize will enumerate through any components
/// and initialize them as well.
/// </summary>
bool RESULT_SCENE::Initialize()
{
	// TODO: Add your initialization logic here

	this->clearflag_ = SceneShared().GetBoolForKey("CLEARFLAG");

	JUDGECOUNT* scorejudge = (JUDGECOUNT*)SceneShared().GetDataForKey("SCOREJUDGE");
	JUDGECOUNT* accuracyjudge = (JUDGECOUNT*)SceneShared().GetDataForKey("COOLJUDGE");
	this->scorejudge_ = *scorejudge;
	this->accuracyjudge_ = *accuracyjudge;

	this->score_ = SceneShared().GetIntegerForKey("SCORE");
	this->accuracy_ = SceneShared().GetIntegerForKey("ACCURACY");
	this->maxcombo_ = SceneShared().GetIntegerForKey("MAXCOMBO");

	SceneShared().RemoveBoolForKey("CLEARFLAG");
	SceneShared().RemoveDataForKey("SCOREJUDGE");
	SceneShared().RemoveDataForKey("COOLJUDGE");
	SceneShared().RemoveIntegerForKey("SCORE");
	SceneShared().RemoveIntegerForKey("ACCURACY");
	SceneShared().RemoveIntegerForKey("MAXCOMBO");
	delete scorejudge;
	delete accuracyjudge;

	this->state_ = RESULT_SCENE::FADEIN;

	this->scoremanager_ = new ScoresManager(this->clearflag_,this->score_,this->accuracy_,this->accuracyjudge_);

	this->movie_ = MediaManager.CreateMediaFromFile(_T("result/result_movie.wmv"));

	if (this->clearflag_){
		this->movie_->Play();
	}
	else{

		this->movie_->PlayMono();

	}

	this->bgm_ = SoundDevice.CreateSoundFromFile(_T("result/resultbgm.wav"));
	this->bgm_->PlayLooping();

	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void RESULT_SCENE::Finalize()
{
	// TODO: Add your finalization logic here
	MediaManager.ReleaseMedia(this->movie_);
	SoundDevice.ReleaseSound(this->bgm_);
	delete this->scoremanager_;
}

/// <summary>
/// Allows the game to run logic such as updating the world,
/// checking for collisions, gathering input, and playing audio.
/// </summary>
/// <returns>
/// Scene continued value.
/// </returns>
int RESULT_SCENE::Update()
{
    // TODO: Add your update logic here

	CONTROLL::GetInstance().Update();

	int scoremanager = this->scoremanager_->Update(GameTimer.GetElapsedMilliSecond());

	switch (this->state_){

	case RESULT_SCENE::FADEIN:

		if (fade_.Update()){

			this->state_ = RESULT_SCENE::DISPLAYNOW;
			this->scoremanager_->ShowStart();

		}
		else if(this->IsPush()){

			fade_.Skip();
			this->state_ = RESULT_SCENE::DISPLAYNOW;
			this->scoremanager_->ShowStart();
		}

		break;

	case RESULT_SCENE::DISPLAYNOW:

		if (this->IsPush()){

			this->scoremanager_->Skip();

		}

		if (scoremanager){
			this->state_ = RESULT_SCENE::PUSHWAIT;
		}

		break;

	case RESULT_SCENE::PUSHWAIT:
		

		if (this->IsPush()){

			fade_.SetFadeState(FadeDisplay::FADEOUT);
			this->state_ = RESULT_SCENE::FADEOUT;

		}
		
		break;

	case RESULT_SCENE::FADEOUT:

		if (fade_.Update()){

			this->bgm_->Stop();
			return GAME_SCENE(new THANK_SCENE());

		}
		else if (this->IsPush()){

			fade_.Skip();

		}

		break;

	default:
		break;
	}

	if (this->movie_->IsComplete()){

		this->movie_->Replay();

	}

	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void RESULT_SCENE::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_Black);

	GraphicsDevice.BeginScene();

	SpriteBatch.Begin();
	SpriteBatch.Draw(*movie_,Vector3_Zero,0.7f);
	SpriteBatch.End();

	Viewport viewport = GraphicsDevice.GetViewport();

	std::string str;
	Vector2 bigcellsize = IMAGEFONT.GetCellSize() * 1.3f;
	Vector2 biggestcellsize = IMAGEFONT.GetCellSize() * 1.8f;
	Color color = Color(1.0f, 1.0f, 1.0f);
	Vector2 drawsize;

	if (this->clearflag_){

		str = ("CLEARED");
		color = Color(1.0f,1.0f,0.0f);

	}
	else{

		str = ("FAILED");
		color = Color(1.0f, 0.0, 0.0f);

	}

	drawsize = IMAGEFONT.GetDrawSize(biggestcellsize, str.c_str());

	float resultstr_x = drawsize.x;

	drawsize = IMAGEFONT.GetDrawSize(bigcellsize, "STAGE");
	resultstr_x += drawsize.x;
	
	Vector3 pos = Vector3_Zero;
	pos.x = (viewport.Width - resultstr_x) / 2.0f;
	IMAGEFONT.DirectDrawImageString(pos, bigcellsize, Color(255, 255, 255), "STAGE");
	pos.x += drawsize.x;
	IMAGEFONT.DirectDrawImageString(pos, biggestcellsize, color, str.c_str());

	Vector2 smollcellsize = IMAGEFONT.GetCellSize() / 2.5f;

	drawsize = IMAGEFONT.GetDrawSize(smollcellsize, "PUSH BUTTON TO NEXT");
	pos = Vector3_Zero;
	pos.x = (viewport.Width - drawsize.x) / 2.0f;
	pos.y = (viewport.Height - drawsize.y);

	IMAGEFONT.DirectDrawImageString(pos, smollcellsize, Color(255, 255, 255),"PUSH BUTTON TO NEXT");

	this->scoremanager_->Draw();

	fade_.Draw();

	GraphicsDevice.EndScene();
}

bool RESULT_SCENE::IsPush(){

	if (CONTROLL::GetInstance().BufferIsPress(LEFT)||
		CONTROLL::GetInstance().BufferIsPress(CENTER) || 
		CONTROLL::GetInstance().BufferIsPress(RIGHT) ){

		return true;

	}

	return false;

}