#include "GamePlayState.h"
#include "INSTRUMENT.h"
#include "UI.h"
#include "ImageFont.h"
#include "CONTROLL.h"
#include "../GameScene/GameScene.hpp"


GamePlayState::GamePlayState(){

	IMAGEFONT; //‰æ‘œ‚Ì‰Šú‰»

	MediaManager.Attach(GraphicsDevice);

	movie_ = MediaManager.CreateMediaFromFile(_T("backmovie.wmv"));

	this->bgm_ = SoundDevice.CreateSoundFromFile(_T("transtep.wav"));

	this->instrument_ = new INSTRUMENT(SceneShared().GetLongIntegerForKey("MOUSE_MAX_Y"), this->bpmlist_, "test.txt");
	SceneShared().RemoveLongIntegerForKey("MOUSE_MAX_Y");
	this->ui_ = new UI();

	auto itr = this->bpmlist_.begin();
	this->bpm_ = itr->bpm;
	this->quater_rhythm_ = (int)(60.0f / (float)bpm_ * 1 * 1000.0f);
	this->instrument_->SetBPM(this->bpm_, this->quater_rhythm_);

	this->nowtime_ = 0;
	this->animationrate_ = 0.0f;

	this->start_ = false;
	this->endgameflag_ = false;

	this->songlength_ = bgm_->GetLengthMSec();

	this->prevtime_ = 0;

	this->accuracy_ = 0;
	this->score_ = 0;
	this->life_ = 0.5f;
	this->maxcombo_ = 0;

	font_ = GraphicsDevice.CreateDefaultFont();

}

GamePlayState::~GamePlayState(){

	delete instrument_;
	delete ui_;

}

AbstructState* GamePlayState::Update(){

	CONTROLL::GetInstance().Update();
	IMAGEFONT.SrtingReset();

	this->TimeCalc();

	animationrate_ = (float)((quater_rhythm_ - 1) - nowtime_ % quater_rhythm_) / (float)quater_rhythm_;

	instrument_->Update(nowtime_, elapsedtime_, GetElapsedCount(elapsedtime_));

	if (!this->endgameflag_){
		this->ToUITellValue();
	}
	else{

		int isfinish = this->gameoverdisplay.Update();

		if (isfinish){

			this->nextscene_ = GAME_SCENE(new RESULT_SCENE());

		}

	}
	this->ui_->Update();

	return nullptr;

}

void GamePlayState::Draw(){

	SpriteBatch.Begin();

	if (this->start_){

		SpriteBatch.Draw(*this->movie_, Vector3_Zero, 1.0f, Vector3_Zero, Vector3_Zero, Vector2(1280.0f / 640.0f, 720.0f / 360.0f));

	}
	SpriteBatch.DrawString(this->font_, Vector2(0.0f, 100.0f), Color(0, 255, 255), _T("time : %u"), nowtime_);
	SpriteBatch.DrawString(this->font_, Vector2(0.0f, 130), Color(0, 255, 255), _T("elapsedtime : %u"), elapsedtime_);

	SpriteBatch.End();

	instrument_->Draw(nowtime_, animationrate_);

	ui_->Draw(animationrate_);

	IMAGEFONT.DrawString(animationrate_);


	if (this->endgameflag_){

		this->gameoverdisplay.Draw();

	}

}

void GamePlayState::TimeCalc(){


	if (this->start_){

		prevtime_ = nowtime_;

		nowtime_ = (int)((float)songlength_ * ((float)bgm_->GetPosition() / (float)bgm_->GetSize()));
		elapsedtime_ = nowtime_ - prevtime_;

		if (!this->bgm_->IsPlaying() && !this->endgameflag_){

			this->SetSceneShared(true);

		}

	}
	else{

		elapsedtime_ = 0;
		if (CONTROLL::GetInstance().BufferIsPress(Keys_Space)){

			start_ = true;

			this->bgm_->Play();
			this->movie_->Play();
		}

	}

}

void GamePlayState::ToUITellValue(){

	JUDGECOUNT scorejudge;
	JUDGECOUNT accuracyjudge;

	scorejudge = instrument_->GetScoreJudge();
	this->scorejudge_ += scorejudge;

	int framescore = scorejudge.GetScore();
	float multiplayer_ = 1.0f + (float)instrument_->GetCombo() / 100.0f;
	this->score_ += (int)((float)framescore * multiplayer_);

	accuracyjudge = instrument_->GetAccuracyJudge();
	this->accuracy_ += accuracyjudge.GetAccuracy();
	this->accuracyjudge_ += accuracyjudge_;

	if (this->maxcombo_ < instrument_->GetCombo())this->maxcombo_ = instrument_->GetCombo();

	this->life_ += scorejudge.GetLifePersent();
	if (this->life_ > 1.0f) this->life_ = 1.0f;
	if (this->life_ <= 0.0f){

		this->life_ = 0.0f;
		this->SetSceneShared(false);

	}

	ui_->SetDisplayData(this->score_, this->life_, this->accuracy_, instrument_->GetNotesCount(), this->maxcombo_);

}

void GamePlayState::SetSceneShared(bool clearflag){

	this->endgameflag_ = true; 
	this->bgm_->Stop();

	SceneShared().SetBoolForKey("CLEARFLAG", clearflag);

	JUDGECOUNT* takescorejudge = new JUDGECOUNT();
	JUDGECOUNT* takeraccuracyjudge = new JUDGECOUNT();

	*takescorejudge = this->scorejudge_;
	*takeraccuracyjudge = this->accuracyjudge_;
	SceneShared().SetDataForKey("SCOREJUDGE", takescorejudge);
	SceneShared().SetDataForKey("ACCURACYJUDGE", takeraccuracyjudge);

	SceneShared().SetIntegerForKey("SCORE", this->score_);
	SceneShared().SetIntegerForKey("ACCURACY", this->accuracy_);
	SceneShared().SetIntegerForKey("MAXCOMBO", this->maxcombo_);

}

long GamePlayState::GetElapsedCount(int elapsedtime){

	auto bpm_itr = bpmlist_.begin();

	long count = 0;

	if (bpmlist_.size() > 1){

		if ((bpm_itr + 1)->timing < this->nowtime_){

			int overtime = this->nowtime_ - (bpm_itr + 1)->timing;
			count += (bpm_itr + 1)->bpm * overtime;
			count += (elapsedtime - overtime) * bpm_itr->bpm;

			bpm_itr = bpmlist_.erase(bpm_itr);
			this->bpm_ = (bpm_itr)->bpm;
			this->quater_rhythm_ = (int)(60.0f / (float)bpm_ * 1 * 1000.0f);

			instrument_->SetBPM(this->bpm_, this->quater_rhythm_);

			return count;

		}

	}

	return count += elapsedtime * bpm_itr->bpm;

}