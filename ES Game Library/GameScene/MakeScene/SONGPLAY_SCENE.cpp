// #include "Extension\DirectX11\DXGraphics11.hpp"
#include "SONGPLAY_SCENE.h"
#include "../../StdAfx.h"
#include "../../MyMakeClasses/INSTRUMENT.h"
#include "../../MyMakeClasses/UI.h"
#include "../../MyMakeClasses/CONTROLL.h"
#include "../SceneShared.hpp"
#include <time.h>


/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load all of your content.
/// Initialize will enumerate through any components and initialize them as well.
/// </summary>
bool SONGPLAY_SCENE::Initialize()
{
	// TODO: Add your initialization logic here

	background_ = GraphicsDevice.CreateSpriteFromFile(_T("background/backwall.png"));
	bgm_ = SoundDevice.CreateSoundFromFile(_T("transtep.wav"));

	bpm_ = 136;
	quater_rhythm_ = (UINT)(60.0f / (float)bpm_ * 1 * 1000.0f);
	quaver_rhythm_ = quater_rhythm_ / 2;

	instrument_ = new INSTRUMENT(SceneShared().GetLongIntegerForKey("MOUSE_MAX_Y"));
	SceneShared().RemoveLongIntegerForKey("MOUSE_MAX_Y");
	ui_ = new UI();

	instrument_->SetBPM(136, quater_rhythm_);

	nowtime_ = 0;
	animation_rate_ = 0.0f;
	start_ = false;

	songlength_ = bgm_->GetLengthMSec();

	prevtime_ = clock();

	accuracy_ = 0;
	score_ = 0;
	life_ = 0.5f;
	maxcombo_ = 0;

	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void SONGPLAY_SCENE::Finalize()
{
	// TODO: Add your finalization logic here

	delete instrument_;
	delete ui_;

}

/// <summary>
/// Allows the game to run logic such as updating the world,
/// checking for collisions, gathering input, and playing audio.
/// </summary>
/// <returns>
/// Scene continued value.
/// </returns>
int SONGPLAY_SCENE::Update()
{
	// TODO: Add your update logic here

	CONTROLL::GetInstance().Update();

	if (start_){

		prevtime_ = nowtime_;

 		nowtime_ = (UINT)( (double)songlength_ * ((double)bgm_->GetPosition() / (double)bgm_->GetSize()) );
		elapsedtime = nowtime_ - prevtime_;

	}
	else{
	
		elapsedtime = 0;
		if (CONTROLL::GetInstance().BufferIsPress(Keys_Space)){

			start_ = true;

			bgm_->Play();
		}


	}


	animation_rate_ = (float)((quater_rhythm_ - 1) - nowtime_ % quater_rhythm_) / (float)quater_rhythm_;

	instrument_->Update(nowtime_, elapsedtime);

	unsigned framescore = instrument_->GetScoreJudge().GetScore();
	float multiplayer_ = 1.0f + (float)instrument_->GetCombo() / 100.0f;
	score_ += (UINT)((float)framescore * multiplayer_);
	life_ += instrument_->GetScoreJudge().GetLifePersent();
	if (life_ > 1.0f) life_ = 1.0f;
	if (life_ < 0.0f) life_ = 0.0f;

	if (maxcombo_ < instrument_->GetCombo()) maxcombo_ = instrument_->GetCombo();

	accuracy_ += instrument_->GetAccuracyJudge().GetAccuracy();

	ui_->SetDisplayData(score_,life_, accuracy_, instrument_->GetNotesCount(),maxcombo_);

	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void SONGPLAY_SCENE::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_Black);

	GraphicsDevice.BeginScene();


	SpriteBatch.Begin();


	SpriteBatch.Draw(*background_,Vector3_Zero,0.3f);

	instrument_->Draw(nowtime_,animation_rate_);

	ui_->Draw(animation_rate_);

	SpriteBatch.DrawString(DefaultFont, Vector2(0.0f, 100.0f), Color(0, 255, 255), _T("time : %u"), nowtime_);
	SpriteBatch.DrawString(DefaultFont, Vector2(0.0f, 130), Color(0, 255, 255), _T("elapsedtime : %u"), elapsedtime);


	SpriteBatch.End();

	GraphicsDevice.EndScene();
}
