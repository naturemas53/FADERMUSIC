#pragma once
#include "ABSTRUCT_NOTE.h"
#include <vector>
#include <map>

class LONGNOTE : public ABSTRUCT_NOTE
{
public:
	LONGNOTE(unsigned timing, float height_rate, Color_by_Name color);
	~LONGNOTE();

	virtual void Update(unsigned nowtime);
	virtual void Draw(Vector3 fader_top_pos, float fader_height, float animation_rate, unsigned nowtime, int timeup_to_timing);

	struct LONG_POINT{

		unsigned timing;
		float height_rate;

		LONG_POINT(unsigned timing,float height_rate){
		
			this->timing = timing;
			this->height_rate = height_rate;
		
		}

	};

	void AddPoint(unsigned timing,float height_rate);

	unsigned GetTimingSlowMostPoint(){
	
		auto itr = long_points_.end();

		itr--;
		return itr->timing;
	
	}

	bool IsPush(){ return ispush_; }
	void Push(){ ispush_ = true; }

	void DownRight(unsigned downvalue){ this->right_power_ -= (float)downvalue; }
	bool IsHaveRightPower(){ return (this->right_power_ / this->RIGHT_POWER_MAX_ >= 0.5f); }

private:

	void NoteMove(unsigned nowtime);
	void LongXScale(unsigned nowtime);

	void DrawTriangle(Vector3 fader_top_pos,float fader_height,unsigned nowtime,unsigned longtime,float long_x_scale);
	void DrawNote(Vector3 fader_top_pos, float fader_height, unsigned nowtime,float animation_rate,int timeup_to_timing,unsigned longtime);

	bool ispush_;
	float long_xscale_;

	float right_power_;
	const float RIGHT_POWER_MAX_;

	std::vector<LONG_POINT> long_points_;

	static std::map<Color_by_Name, SPRITE>* longnote_sprites_;
	static std::map<Color_by_Name, SPRITE>* triangle_sprites_;

};

