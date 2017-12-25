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

	void Update(unsigned nowtime, unsigned elapsedtime_,long elapsedcount);
	void Draw(unsigned nowtime,float animation_rate);

	void SetBPM(unsigned bpm, unsigned quater_rhythm);

	JUDGECOUNT GetScoreJudge();
	JUDGECOUNT GetAccuracyJudge();

	unsigned GetNotesCount(){ return notes_.size(); }
	unsigned GetCombo(){ return havecombo_; }

private:

	void Setting(const char* filename, std::vector<BPM_DATA>& bpmlist);
	void ReadBpm(FILE* file, std::vector<BPM_DATA>& bpmlist);
	void ReadNote(FILE* file, std::vector<BPM_DATA>& bpmlist);
	void RangeCalculation(unsigned timing, int* range_time, long* range_count, long* firsthave_count, std::vector<BPM_DATA>& bpmlist);

	void HighSpeedUpdate(LONG ScrollWheelValue);
	//Ç∆ÇËÇ†Ç¶Ç∏Å´
	void RightUp(unsigned nowtime);

	FONT font_;
	//Ç∆ÇËÇ†Ç¶Ç∏Å™

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

	float high_speed;

};

