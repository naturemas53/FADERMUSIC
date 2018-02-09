#pragma once
#include "AbstructBomb.h"
#include "../../ESGLib.h"
#include <map>

class LongBreakBomb : public AbstructBomb{

public:

	LongBreakBomb();
	~LongBreakBomb();

	void Init(Vector3 fader_pos,Vector2 inner_size,float height,Color_by_Name color,float longxscale);
	virtual int Update(int elapsedtime);
	virtual void Draw();

private:

	enum STATE{

		REDUCING,
		FADEOUT

	}state_;

	static std::map<Color_by_Name, SPRITE>* sprites_;

	const int REDUCINGTIME_;
	const int FADEOUTTIME_;
	const float DIAMONDSCALE_;

	float xscale_;
	float alpha_;
	Color_by_Name mycolor_;

};