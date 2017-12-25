#pragma once
#include "ABSTRUCT_NOTE.h"

class SINGLENOTE:public ABSTRUCT_NOTE
{
public:
	SINGLENOTE(unsigned timing, float height_rate, Color_by_Name color, long range_count, int range_time, long firsthave_count);
	virtual ~SINGLENOTE() = default;

	void Init(unsigned timing, float height_rate);
	virtual void Update(unsigned nowtime){/*ç°ÇÃÇ∆Ç±ÇÎâΩÇ‡Ç»Ç¢Ç≈Ç∑*/}
	virtual bool Draw(Vector3 fader_top_pos, float fader_height, float animation_rate, unsigned nowtime);


};

