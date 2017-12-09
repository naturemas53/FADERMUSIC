#pragma once
#include "../ESGLib.h"

struct JUDGECOUNT;

class UI
{
public:
	UI();
	~UI();

	void Update();
	void Draw(float animation_rate);

	void SetDisplayData(int score,float life,int accuracy,int allnotes);

private:

	SPRITE lifegauge_sprite_;
	SPRITE uiline_sprite_;

	const float GAUGE_HEIGHT_;
	const float GAUGE_WIDTH_;

	float draw_lifepersent_;
	int draw_score_;
	int draw_accuracy_;


	//Ç∆ÇËÇ†Ç¶Ç∏Å´
	FONT score_font_;
	FONT accuracy_font_;


};

