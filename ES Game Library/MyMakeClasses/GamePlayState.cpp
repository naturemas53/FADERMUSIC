#include "GamePlayState.h"
#include "INSTRUMENT.h"
#include "UI.h"
#include "ImageFont.h"
#include "CONTROLL.h"
#include "../GameScene/GameScene.hpp"
#include <string>


GamePlayState::GamePlayState(){

	IMAGEFONT; //‰æ‘œ‚Ì‰Šú‰»

	std::wstring buf;

	buf = SceneShared().GetWStringForKey("MOVIE");
	movie_ = MediaManager.CreateMediaFromFile(const_cast<wchar_t *>(buf.c_str()));
	SceneShared().RemoveWStringForKey("MOVIE");

	buf.clear();

	buf = SceneShared().GetWStringForKey("MUSIC");
	this->bgm_ = SoundDevice.CreateSoundFromFile(const_cast<wchar_t *>(buf.c_str()));
	SceneShared().RemoveWStringForKey("MUSIC");

	std::string str;
	str = SceneShared().GetStringForKey("MUSICSCORE");
	this->instrument_ = new INSTRUMENT(4500, this->bpmlist_, str.c_str());
	SceneShared().RemoveStringForKey("MUSICSCORE");
	this->ui_ = new UI();

	auto itr = this->bpmlist_.begin();
	this->bpm_ = itr->bpm;
	this->quater_rhythm_ = (int)(60.0f / (float)bpm_ * 1 * 1000.0f);
	this->instrument_->SetBPM(this->bpm_, this->quater_rhythm_);

	this->nowtime_ = -2000;
	this->animationrate_ = 0.0f;

	this->songlength_ = bgm_->GetLengthMSec();

	this->prevtime_ = 0;

	this->accuracy_ = 0;
	this->score_ = 0;
	this->life_ = 0.5f;
	this->maxcombo_ = 0;

	this->scorejudge_ = JUDGECOUNT();
	this->accuracyjudge_ = JUDGECOUNT();

	this->playstate_ = GamePlayState::READY;

}

GamePlayState::~GamePlayState(){

	MediaManager.ReleaseMedia(this->movie_);
	SoundDevice.ReleaseSound(this->bgm_);

	delete instrument_;
	delete ui_;

}

AbstructState* GamePlayState::Update(){

	CONTROLL::GetInstance().Update();
	IMAGEFONT.SrtingReset();

	this->TimeCalc();

	int isfinish = this->fade_.Update();


	if (!(this->playstate_ == GamePlayState::ENDGAME)){

	animationrate_ = (float)((quater_rhythm_ - 1) - nowtime_ % quater_rhythm_) / (float)quater_rhythm_;

	instrument_->Update(nowtime_, elapsedtime_, GetElapsedCount(elapsedtime_));

	this->ToUITellValue();

	}
	else{

		if (isfinish){

			this->nextscene_ = GAME_SCENE(new RESULT_SCENE());

		}

	}
	this->ui_->Update();

	if (this->movie_->IsComplete()){
		this->movie_->Replay();
	}

	return nullptr;

}

void GamePlayState::Draw(){

	SpriteBatch.Begin();

	if (this->bgm_->IsPlaying()){

		SpriteBatch.Draw(*this->movie_, Vector3_Zero, 1.0f, Vector3_Zero, Vector3_Zero, Vector2(1280.0f / 640.0f, 720.0f / 360.0f));

	}

	SpriteBatch.End();

	instrument_->Draw(nowtime_, animationrate_);

	ui_->Draw(animationrate_);

	IMAGEFONT.DrawString(animationrate_);

	this->fade_.Draw();

}

void GamePlayState::TimeCalc(){

	if (this->playstate_ == GamePlayState::SONGPLAY){

		prevtime_ = nowtime_;

		nowtime_ = (int)((float)songlength_ * ((float)bgm_->GetPosition() / (float)bgm_->GetSize()));
		elapsedtime_ = nowtime_ - prevtime_;

		if (!this->bgm_->IsPlaying()){

			this->SetSceneShared(true);

		}

	}
	else{

		this->elapsedtime_ = GameTimer.GetElapsedMilliSecond();
		this->nowtime_ += this->elapsedtime_;

		if (this->nowtime_ >= 0 && this->playstate_ == GamePlayState::READY){

			this->playstate_ = GamePlayState::SONGPLAY;
			this->bgm_->SetPositionMilliSec(this->nowtime_);
			this->bgm_->Play();

			LONGLONG setmoviepos = (LONGLONG)((double)UNITS * ((double)this->nowtime_ / 1000.0));

			this->movie_->SetPosition(setmoviepos);
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
	this->accuracyjudge_ += accuracyjudge;

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

	this->playstate_ = GamePlayState::ENDGAME;
	this->fade_.SetFadeState(FadeDisplay::FADEOUT);
	this->bgm_->Stop();

	SceneShared().SetBoolForKey("CLEARFLAG", clearflag);

	JUDGECOUNT* takescorejudge = new JUDGECOUNT();
	JUDGECOUNT* takeaccuracyjudge = new JUDGECOUNT();

	*takescorejudge = this->scorejudge_;
	*takeaccuracyjudge = this->accuracyjudge_;
	SceneShared().SetDataForKey("SCOREJUDGE", takescorejudge);
	SceneShared().SetDataForKey("COOLJUDGE", takeaccuracyjudge);

	float accuracyrate = (float)this->accuracy_/ (float)(instrument_->GetNotesCount() * 100);
	int trueaccuracy =(int) (accuracyrate * 100000.0f);

	SceneShared().SetIntegerForKey("SCORE", this->score_);
	SceneShared().SetIntegerForKey("ACCURACY", trueaccuracy);
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