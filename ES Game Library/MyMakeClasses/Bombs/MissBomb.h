#pragma once
#include "JudgeBomb.h"

class MissBomb : public JudgeBomb{

public:

	MissBomb() : JudgeBomb(350, 5, 5, Vector2(120.0f, 120.0f), MISSTIME){}
	~MissBomb() = default;

	virtual void Init(Vector3 faderpos, Vector2 fader_inner, float height);
	virtual int Update(int elapsedtime);
	virtual void Draw();

private:

};