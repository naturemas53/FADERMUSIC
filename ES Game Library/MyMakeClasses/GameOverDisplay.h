#pragma once
#include "../ESGLib.h"

class GameOverDisplay{

public:

	GameOverDisplay();
	~GameOverDisplay();

	int Update();
	void Draw();

private:

	RENDERTARGET blackscreen_;
	//float alpha_;

	int count_;
};