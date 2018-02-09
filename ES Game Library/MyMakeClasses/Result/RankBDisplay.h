#pragma once
#include "AbstructRankDisplay.h"

class RankBDisplay : public AbstructRankDisplay{

public:

	RankBDisplay();
	~RankBDisplay();

	virtual int Update(int elapsedtime);
	virtual void Draw();
	virtual void Skip();

private:

	const Vector3 STARTPOS_;
	const int MOVETIME_;

	int time_;


};