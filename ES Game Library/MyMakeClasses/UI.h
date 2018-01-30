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

	void SetDisplayData(int score,float life,int accuracy,int allnotes,int maxcombo);

private:

	SPRITE framesp_;
	SPRITE innersp_;

	const Vector2 FRAME_SIZE_;
	const Vector2 INNER_SIZE_;
	const int ANIMECOUNT_;
	const int CELLCOUNT_;

	float draw_lifepersent_;
	int draw_score_;
	int draw_accuracy_;
	int draw_maxcombo_;

	int nowcount_;


};

