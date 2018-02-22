#pragma once
#include "../ESGLib.h"
#include "AbstructState.h"
#include "BPM_DATA_STRUCT.h"
#include "JUDGELIST_ENUM.h"
#include "FadeDisplay.h"
#include "GameOverDisplay.h"
#include <vector>

class INSTRUMENT;
class UI;

class GamePlayState : public AbstructState{

public:

	GamePlayState();
	virtual ~GamePlayState();

	AbstructState* Update();
	void Draw();

private:

	enum PLAYSTATE{

		READY,
		SONGPLAY,
		ENDGAME

	}playstate_;

	// ä÷êîêÈåæ
	void TimeCalc();
	long GetElapsedCount(int elapsedtime);
	void ToUITellValue();

	void SetSceneShared(bool clearflag);

	// ïœêîêÈåæ



	INSTRUMENT* instrument_;
	UI* ui_;

	MEDIA movie_;

	int songlength_;

	int score_;
	float life_;
	int accuracy_;
	int maxcombo_;

	int nowtime_;
	int prevtime_;
	int elapsedtime_;
	float animationrate_;

	int bpm_;
	int quater_rhythm_;
	int quaver_rhythm_;

	std::vector<BPM_DATA> bpmlist_;

	JUDGECOUNT scorejudge_;
	JUDGECOUNT accuracyjudge_;

	GameOverDisplay gameover_;
	FadeDisplay fade_;

	SOUND bgm_;

};