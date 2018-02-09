#pragma once
#include "AbstructBomb.h"
#include "../../ESGLib.h"

class FlashBomb : public AbstructBomb{

public:

	FlashBomb();
	~FlashBomb();

	void Init(Vector3 faderpos,Vector2 faderinner,float height);
	virtual int Update(int elapsedtime);
	virtual void Draw();

private:

	static SPRITE sprite_;

	float movement_y_;
	float right_xpos_;

};