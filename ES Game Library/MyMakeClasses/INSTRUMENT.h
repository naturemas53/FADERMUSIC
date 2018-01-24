#pragma once

#include "../ESGLib.h"

#include <vector>
#include <fstream>

class FADER;
class ABSTRUCT_NOTE;
struct JUDGECOUNT;
struct BPM_DATA;

class INSTRUMENT
{
public:
	INSTRUMENT(LONG max_mouse_y, std::vector<BPM_DATA>& bpmlist, const char* filename);
	~INSTRUMENT();

	void Update(int nowtime, int elapsedtime_, long elapsedcount);
	void Draw(int nowtime, float animation_rate);

	void SetBPM(int bpm, int quater_rhythm);

	JUDGECOUNT GetScoreJudge();
	JUDGECOUNT GetAccuracyJudge();

	int GetNotesCount(){ return notes_.size(); }
	int GetCombo(){ return havecombo_; }

private:

	void Setting(const char* filename, std::vector<BPM_DATA>& bpmlist);
	void ReadBpm(FILE* file, std::vector<BPM_DATA>& bpmlist);
	void ReadNote(FILE* file, std::vector<BPM_DATA>& bpmlist);
	void RangeCalculation(int timing, int* range_time, long* range_count, long* firsthave_count, std::vector<BPM_DATA>& bpmlist);

	void HighSpeedUpdate(LONG ScrollWheelValue);
	//とりあえず↓
	void RightUp(int nowtime);

	FONT font_;
	//とりあえず↑

	void ComboCheck();

	int range_hours_show;

	std::vector<FADER*> faders_;
	std::vector<ABSTRUCT_NOTE*> notes_;

	LONG mouse_y_;
	const LONG MAX_MOUSE_Y_;

	float button_height_;

	int songbpm_;
	int quater_rhythm_;
	int havecombo_;

	float high_speed;

};

