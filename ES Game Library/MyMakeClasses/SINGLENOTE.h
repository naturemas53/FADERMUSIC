#pragma once
#include "ABSTRUCT_NOTE.h"

class SINGLENOTE:public ABSTRUCT_NOTE
{
public:
	SINGLENOTE(int timing, float height_rate, Color_by_Name color, long range_count, int range_time, long firsthave_count);
	virtual ~SINGLENOTE() = default;

	void Init(int timing, float height_rate);
	virtual void Update(int nowtime){/*���̂Ƃ��뉽���Ȃ��ł�*/ }
	virtual bool Draw(Vector3 fader_top_pos, Vector2 fader_inner, float animation_rate, int nowtime, float highspeed, bool addblend);


};

