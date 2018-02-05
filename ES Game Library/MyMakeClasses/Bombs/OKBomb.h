#pragma once
#include "JudgeBomb.h"

class OKBomb : public JudgeBomb{

public:

	OKBomb();
	~OKBomb();

	virtual void Init(Vector3 faderpos, Vector2 fader_inner, float height);
	virtual int Update(int elapsedtime);
	virtual void Draw();

private:

	static SPRITE sprite_;


};