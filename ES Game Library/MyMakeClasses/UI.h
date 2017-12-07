#pragma once
#include "../ESGLib.h"

class UI
{
public:
	UI();
	~UI();

	void Update();
	void Draw(float animation_rate);

	void SetDisplayData(float lifepersent){ this->draw_lifepersent_ = lifepersent; }

private:

	SPRITE lifegauge_sprite_;
	SPRITE uiline_sprite_;

	const float GAUGE_HEIGHT_;
	const float GAUGE_WIDTH_;

	float draw_lifepersent_;
	//float draw_score_;
	//float draw_stage_;
	//float draw_difficulty_;
	//float draw__;



};

