#pragma once

#include "../ESGLib.h"

#include <vector>

class FADER;
class ABSTRUCT_NOTE;
struct JUDGECOUNT;

class INSTRUMENT
{
public:
	INSTRUMENT(LONG max_mouse_y);
	~INSTRUMENT();

	void Update(unsigned nowtime, unsigned elapsedtime_);
	void Draw(unsigned nowtime,float animation_rate);

	void SetBPM(unsigned bpm, unsigned quater_rhythm);

	JUDGECOUNT GetScoreJudge();
	JUDGECOUNT GetAccuracyJudge();

	unsigned GetNotesCount(){ return notes_.size(); }
	unsigned GetCombo(){ return havecombo_; }

private:

	//とりあえず↓
	void SetNote();
	void RightUp(unsigned nowtime);

	FONT font_;
	//とりあえず↑

	void ComboCheck();

	int range_hours_show;

	std::vector<FADER*> faders_;
	std::vector<ABSTRUCT_NOTE*> notes_;

	LONG mouse_y_;
	const LONG MAX_MOUSE_Y_;

	float button_height_;

	unsigned songbpm_;
	unsigned quater_rhythm_;
	unsigned havecombo_;

};

