#pragma once
#include "JudgeBomb.h"

class UnbelievableBomb : public JudgeBomb{

public:

	UnbelievableBomb();
	~UnbelievableBomb();

	virtual void Init(Vector3 faderpos, Vector2 fader_inner, float height);
	virtual int Update(int elapsedtime);
	virtual void Draw();

private:

	static SPRITE sprite_;

};