#include "ScoresManager.h"
#include "JudgeDisplay.h"
#include "ScoreDisplay.h"
#include "RankSDisplay.h"
#include "RankADisplay.h"
#include "RankBDisplay.h"
#include "RankCDisplay.h"
#include "RankDDisplay.h"
#include "RankFDisplay.h"

ScoresManager::ScoresManager(bool clearflag, int score, int accuracy, JUDGECOUNT scorejudge) :
SCORESHOWTIME_(200),
RANDOMUPDATETIME_(30)
{

	this->ScoreDisplaySet(score,accuracy,scorejudge);
	this->RankSet(clearflag,accuracy);

	this->showsound_ = SoundDevice.CreateSoundFromFile(_T("result/showscore.wav"));

	this->count_ = 0;
	this->randomtime_ = 0;

	this->startdisplay_ = false;
	this->state_ = ScoresManager::WAIT;

}

void ScoresManager::ScoreDisplaySet(int score, int accuracy, JUDGECOUNT scorejudge){

	float left = 50.0f;

	this->scores_.push_back(new ScoreDisplay(Vector3(left, 210.0f, 0.0f), "SCORE", score));
	this->scores_.push_back(new ScoreDisplay(Vector3(700.0f, 210.0f, 0.0f), "ACCURACY", accuracy));

	this->scores_.push_back(new JudgeDisPlay(Vector3(left, 390.0f, 0.0f), _T("result/judgestring/UNBELIEVABLE_result.png"),
		Vector3(left + 500.0f, 360.0f, 0.0f), scorejudge.unbelievable));
	this->scores_.push_back(new JudgeDisPlay(Vector3(left, 450.0f, 0.0f), _T("result/judgestring/GREAT_result.png"),
		Vector3(left + 500.0f, 420.0f, 0.0f), scorejudge.great));
	this->scores_.push_back(new JudgeDisPlay(Vector3(left, 510.0f, 0.0f), _T("result/judgestring/OK_result.png"),
		Vector3(left + 500.0f, 480.0f, 0.0f), scorejudge.ok));
	this->scores_.push_back(new JudgeDisPlay(Vector3(left, 570.0f, 0.0f), _T("result/judgestring/MISS_result.png"),
		Vector3(left + 500.0f, 540.0f, 0.0f), scorejudge.misstime));

}

void ScoresManager::RankSet(bool clearflag,int accuracy){

	if (!clearflag){

		this->rank_ = new RankFDisplay();
		return;

	}

	if (accuracy >= 98000){

		this->rank_ = new RankSDisPlay();

	}
	else if (accuracy >= 90000){

		this->rank_ = new RankADisplay();

	}
	else if (accuracy >= 80000){

		this->rank_ = new RankBDisplay();

	}
	else if (accuracy >= 70000){

		this->rank_ = new RankCDisplay();

	}
	else {

		this->rank_ = new RankDDisplay();

	}

}

ScoresManager::~ScoresManager(){

	for (auto score : this->scores_){

		delete score;

	}

	delete this->rank_;

	SoundDevice.ReleaseSound(this->showsound_);

}

int ScoresManager::Update(int elapsedtime){

	switch (this->state_){

	case ScoresManager::WAIT:
		this->RandomUpdate();
		break;

	case ScoresManager::SCOREDISPLAY:

		if (this->RandomUpdate()){

			this->state_ = ScoresManager::RANKDISPLAY;
			this->rank_->Start();
			break;

		}

		this->count_ += elapsedtime;
		if (this->count_ > this->SCORESHOWTIME_){

			this->showsound_->Play();
			this->ShowScore();

		}

		break;

	case ScoresManager::RANKDISPLAY:

		if (this->rank_->Update(elapsedtime)){

			return 1;

		}

		break;

	default:
		break;

	}

	return 0;

}

void ScoresManager::Draw(){

	for (auto score : this->scores_){

		score->Draw();

	}

	this->rank_->Draw();

}

int ScoresManager::RandomUpdate(){

	this->randomtime_ -= this->RANDOMUPDATETIME_;

	auto itr = this->scores_.begin();
	auto e_itr = this->scores_.end();
	auto ef_itr = e_itr - 1;

	while (itr != e_itr){

		if (!(*itr)->GetScoreShowFlag()){

			(*itr)->Update();

		}
		else if (itr == ef_itr){

			return 1;

		}

		itr++;

	}

	return 0;

}

void ScoresManager::ShowScore(){

	this->count_ -= this->SCORESHOWTIME_;

	for (auto score : this->scores_){

		if (!score->GetScoreShowFlag()){

			score->SetScoreShowFlag(true);
			break;

		}

	}

}