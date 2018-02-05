#pragma once
#include "ABSTRUCT_NOTE.h"
#include <vector>
#include <map>

class LONGNOTE : public ABSTRUCT_NOTE
{
public:
	LONGNOTE(int timing, float height_rate, Color_by_Name color, long range_count, int range_time, long firsthave_count);
	~LONGNOTE();

	virtual void Update(int nowtime);
	virtual bool Draw(Vector3 fader_top_pos, Vector2 fader_inner, float animation_rate, int nowtime, float highspeed, bool addblend);

	struct LONG_POINT{

		int timing;
		float height_rate;

		LONG_POINT(int timing, float height_rate){
		
			this->timing = timing;
			this->height_rate = height_rate;
		
		}

	};

	void AddPoint(int timing, float height_rate);

	int GetTimingSlowMostPoint(){
	
		auto itr = long_points_.end();

		itr--;
		return itr->timing;
	
	}

	float GetLongXScale(){ return this->long_xscale_; }

	bool IsPush(){ return ispush_; }
	void Push(){ ispush_ = true; }

	void DownRight(int downvalue){ this->right_power_ -= (float)downvalue; }
	bool IsHaveRightPower(){ return (this->right_power_ / this->RIGHT_POWER_MAX_ >= 0.5f); }

private:

	const Vector2 DIAMOND_SIZE_;

	void NoteMove(int nowtime);
	void LongXScale(int nowtime);

	void DrawTriangle(Vector3 fader_top_pos, float fader_height, int nowtime, int longtime, float animation_rate, float long_x_scale, bool addblend);
	void DrawNote(Vector3 fader_top_pos, float fader_height, int nowtime, float animation_rate, float x_scale_rate, bool addblend);
	void DrawDiamond(Vector3 fader_top_pos, Vector2 fader_inner, int nowtime, int longtime, float animation_rate, float x_scale_rate, bool addblend);

	bool ispush_;
	float long_xscale_;

	float right_power_;
	const float RIGHT_POWER_MAX_;

	std::vector<LONG_POINT> long_points_;

	static std::map<Color_by_Name, SPRITE>* longnote_sprites_;
	static std::map<Color_by_Name, SPRITE>* triangle_sprites_;
	static std::map<Color_by_Name, SPRITE>* diamond_sprites_;
	static SPRITE innner_box_;

};

