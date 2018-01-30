#pragma once
#include "../ESGLib.h"
#include "AbstructState.h"
#include "BPM_DATA_STRUCT.h"
#include "JUDGELIST_ENUM.h"
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

	// ä÷êîêÈåæ
	void TimeCalc();
	long GetElapsedCount(int elapsedtime);
	void ToUITellValue();

	void SetSceneShared(bool clearflag);

	// ïœêîêÈåæ
	FONT font_;

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

	GameOverDisplay gameoverdisplay;

	//Ç∆ÇËÇ†Ç¶Ç∏Ç≈Å´
	bool start_;

	bool endgameflag_;

	SOUND bgm_;

};