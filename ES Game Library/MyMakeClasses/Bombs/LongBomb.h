#pragma once
#include "AbstructBomb.h"

class LongBomb : public AbstructBomb{

public:

	LongBomb();
	~LongBomb();

	void Init(Vector3 fader_pos, Vector2 inner_size, float height, Color_by_Name color);
	virtual int Update(int elapsedtime);
	virtual void Draw();

private:

	static std::map<Color_by_Name, SPRITE>* sprites_;

	Color_by_Name mycolor_;

};