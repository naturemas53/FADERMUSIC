#pragma once
#include "AbstructRankDisplay.h"

class RankFDisplay : public AbstructRankDisplay{

public:

	RankFDisplay();
	~RankFDisplay();

	virtual int Update(int elapsedtime);
	virtual void Draw();
	virtual void Skip();

private:

	const Vector3 STARTPOS_;
	const int MOVETIME_;

	int time_;
};