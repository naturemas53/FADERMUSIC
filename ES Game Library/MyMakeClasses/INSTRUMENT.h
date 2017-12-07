#pragma once

#include "../ESGLib.h"

#include <vector>

class FADER;
class ABSTRUCT_NOTE;

class INSTRUMENT
{
public:
	INSTRUMENT(LONG max_mouse_y);
	~INSTRUMENT();

	void Update(unsigned nowtime, unsigned elapsedtime_);
	void Draw(unsigned nowtime,float animation_rate);

private:

	//Ç∆ÇËÇ†Ç¶Ç∏Å´
	void SetNote();
	void RightUp(unsigned nowtime);

	int range_hours_show;

	std::vector<FADER*> faders_;
	std::vector<ABSTRUCT_NOTE*> notes_;

	LONG mouse_y_;
	const LONG MAX_MOUSE_Y_;

	float button_height_;

};

