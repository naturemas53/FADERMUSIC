#include "../../StdAfx.h"
#include "RESULT_SCENE.hpp"
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


	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void RESULT_SCENE::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();

	SpriteBatch.Begin();

	std::wstring str;

	if (this->clearflag_){

		str = _T("STAGECLEAR!");

	}
	else{

		str = _T("STAGE FAILED");

	}

	SpriteBatch.DrawString(this->font_,Vector2_One * 30.0f,Color(0,0,0),str.c_str());

	SpriteBatch.End();

	GraphicsDevice.EndScene();
}
