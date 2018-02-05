#pragma once
#include "AbstructBomb.h"
#include "../JUDGELIST_ENUM.h"

class JudgeBomb : public AbstructBomb{

public:

	virtual ~JudgeBomb();

	virtual void Init(Vector3 fader_pos, Vector2 fader_inner, float height) = 0;

	virtual int Update(int elapsedtime) = 0;
	virtual void Draw() = 0;

	JUDGELIST GetType(){ return this->judge_; }

protected:
	JudgeBomb(int animetime, int holizoncell, int maxcell, Vector2 cellsize,JUDGELIST myjudge);

	static SPRITE addsprite_;

	JUDGELIST judge_;

};