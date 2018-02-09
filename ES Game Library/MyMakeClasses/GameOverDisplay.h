#pragma once
#include "../ESGLib.h"

class GameOverDisplay{

public:

	GameOverDisplay();
	~GameOverDisplay();

	int Update(int elapsedtime);
	void Draw();

	void Start(){ this->state_ = GameOverDisplay::MOVEDOWN; }

private:

	enum STATE{

		WAIT,
		MOVEDOWN,
		SCALEUP

	}state_;

	const int STATETIME_;

	SPRITE sprite_;
	int time_;

};