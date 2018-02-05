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
	JUDGECOUNT* accuracyjudge = (JUDGECOUNT*)SceneShared().GetDataForKey("ACCURACYJUDGE");
	this->scorejudge_ = *scorejudge;
	this->accuracyjudge_ = *accuracyjudge;

	this->score_ = SceneShared().GetIntegerForKey("SCORE");
	this->accuracy_ = SceneShared().GetIntegerForKey("ACCURACY");
	this->maxcombo_ = SceneShared().GetIntegerForKey("MAXCOMBO");

	SceneShared().RemoveBoolForKey("CLEARFLAG");
	SceneShared().RemoveDataForKey("SCOREJUDGE");
	SceneShared().RemoveDataForKey("ACCURACYJUDGE");
	SceneShared().RemoveIntegerForKey("SCORE");
	SceneShared().RemoveIntegerForKey("ACCURACY");
	SceneShared().RemoveIntegerForKey("MAXCOMBO");
	delete scorejudge;
	delete accuracyjudge;

	this->state_ = RESULT_SCENE::FADEIN;

	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void RESULT_SCENE::Finalize()
{
	// TODO: Add your finalization logic here

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

	switch (this->state_){

	case RESULT_SCENE::FADEIN:

		if (fade_.Update()){

			this->state_ = RESULT_SCENE::DISPLAYNOW;

		}
		else if(this->IsPush()){

			fade_.Skip();
			this->state_ = RESULT_SCENE::DISPLAYNOW;

		}

		break;

	case RESULT_SCENE::DISPLAYNOW:

		if (this->IsPush()){

			fade_.SetFadeState(FadeDisplay::FADEOUT);
			this->state_ = RESULT_SCENE::FADEOUT;

		}

		break;

	case RESULT_SCENE::FADEOUT:

		if (fade_.Update()){

			return GAME_SCENE(new CALIBRATION_SCENE());

		}
		else if (this->IsPush()){

			fade_.Skip();
			return GAME_SCENE(new CALIBRATION_SCENE());

		}

		break;

	default:
		break;
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

	std::string str;

	if (this->clearflag_){

		str = ("STAGE CLEARED");

	}
	else{

		str = ("STAGE FAILED");

	}

	Vector2 bigcellsize = IMAGEFONT.GetCellSize();
	Vector2 smollcellsize = IMAGEFONT.GetCellSize() / 2.0f;
	Vector2 drawsize;

	drawsize = IMAGEFONT.GetDrawSize(bigcellsize,str.c_str());
	Vector3 pos = Vector3_Zero;
	Viewport viewport = GraphicsDevice.GetViewport();
	pos.x = (viewport.Width - drawsize.x) / 2.0f;
	pos.y = (viewport.Height - drawsize.y) / 2.0f - 100.0f;

	IMAGEFONT.DirectDrawImageString(pos,bigcellsize,Color(255,255,255),str.c_str());

	drawsize = IMAGEFONT.GetDrawSize(smollcellsize, "RETRY TO PUSH SorDorF");
	pos = Vector3_Zero;
	pos.x = (viewport.Width - drawsize.x) / 2.0f;
	pos.y = (viewport.Height - drawsize.y) - 100.0f;

	IMAGEFONT.DirectDrawImageString(pos, smollcellsize, Color(255, 255, 255),"RETRY TO PUSH SorDorF");

	fade_.Draw();

	GraphicsDevice.EndScene();
}

bool RESULT_SCENE::IsPush(){

	if (CONTROLL::GetInstance().BufferIsPress(Keys_S)||
		CONTROLL::GetInstance().BufferIsPress(Keys_D) || 
		CONTROLL::GetInstance().BufferIsPress(Keys_F) ){

		return true;

	}

	return false;

}