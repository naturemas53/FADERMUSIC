#pragma once
#include "ABSTRUCT_NOTE.h"

class SINGLENOTE:public ABSTRUCT_NOTE
{
public:
	SINGLENOTE(unsigned timing, float height_rate,Color_by_Name color);
	virtual ~SINGLENOTE() = default;

	void Init(unsigned timing, float height_rate);
	virtual void Update(unsigned nowtime){/*今のところ何もないです*/}
	virtual void Draw(Vector3 fader_top_pos, float fader_height, float animation_rate, unsigned nowtime, int timeup_to_timing);


};

