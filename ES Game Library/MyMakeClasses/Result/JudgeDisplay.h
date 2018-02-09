#pragma once
#include "AbstructScoreDisplay.h"
#include <string>

class JudgeDisPlay : public AbstructScoreDisplay{

public:

	JudgeDisPlay(Vector3 pos, std::wstring filename, Vector3 countpos, int count);
	~JudgeDisPlay();

	virtual void Draw();

private:

	const int COUNT_;
	const Vector3 COUNTPOS_;

	SPRITE sprite_;

};