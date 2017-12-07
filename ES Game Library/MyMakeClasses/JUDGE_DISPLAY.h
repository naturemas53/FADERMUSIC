#pragma once
#include "../ESGLib.h"
#include <string>
#include <map>

enum JUDGELIST;

class JUDGE_DISPLAY
{
public:
	JUDGE_DISPLAY(Vector3 draw_pos, float fader_height);
	~JUDGE_DISPLAY();

	void Update();
	void Draw(float fader_width);

	void SetBomb(JUDGELIST judge,float height_rate);
	
private:

	enum SCALE_STATE{

		ZOOM_OUT,
		ZOOM_IN,
		STOP

	}scale_state_;

	const Vector3 DRAW_POS_;
	const float FADER_HEIGHT_;
	const float SIZE_;
	const int ZOOM_COUNT_;

	int now_count_;

	float transparency_;
	float scale_;
	float draw_height_;

	static std::map<JUDGELIST, SPRITE>* judge_sprites_;

	JUDGELIST draw_judge_;


};

