#pragma once
#include "../../ESGLib.h"
#include "../JUDGELIST_ENUM.h"
#include "AbstructScoreDisplay.h"
#include "AbstructRankDisplay.h"
#include <string>
#include <vector>
#include <map>

class ScoresManager{

public:

	ScoresManager(bool clearflag,int score, int accuracy, JUDGECOUNT scorejudge);
	~ScoresManager();

	int Update(int elapsedtime);
	void Draw();

	void ShowStart(){
		
		this->state_ = ScoresManager::SCOREDISPLAY;
	
	}

	void Skip(){

		for (auto score : this->scores_){

			score->SetScoreShowFlag(true);

		}

		this->rank_->Skip();

	}

private:

	void ScoreDisplaySet(int score, int accuracy, JUDGECOUNT scorejudge);
	void RankSet(bool clearflag = false, int accuracy = 0);

	int RandomUpdate();
	void ShowScore();

	const int SCORESHOWTIME_;
	const int RANDOMUPDATETIME_;

	enum STATE{

		WAIT,
		SCOREDISPLAY,
		RANKDISPLAY

	}state_;

	std::vector<AbstructScoreDisplay*> scores_;
	AbstructRankDisplay* rank_;

	int count_;
	int randomtime_;

	//Ç∆ÇËÇ†Ç¶Ç∏Å´
	bool startdisplay_;

};