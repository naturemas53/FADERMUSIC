#pragma once
#include "AbstructScoreDisplay.h"
#include <string>

class ScoreDisplay : public AbstructScoreDisplay{

public:

	ScoreDisplay(Vector3 pos, std::string name, int score);
	~ScoreDisplay();

	virtual void Draw();

private:

	std::string name_;
	int score_;

};