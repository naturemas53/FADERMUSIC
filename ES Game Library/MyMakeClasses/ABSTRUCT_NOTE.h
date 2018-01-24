#pragma once
#include "../ESGLib.h"
#include <map>


class ABSTRUCT_NOTE
{
public:
	ABSTRUCT_NOTE(long range_count, int range_time, long firsthave_count) :
		WIDTH_(74.0f),
		HEIGHT_(30.0f),
		LINE_HEIGHT_(10.0f),
		RANGE_COUNT_(range_count),
		RANGE_TIME_(range_time)
	{

		rightup_flag_ = false;
		this->have_count_ = firsthave_count;

		if (this->normal_sprite_ == nullptr) this->normal_sprite_ = GraphicsDevice.CreateSpriteFromFile(_T("notes/rhythm/note_normal.png"));
		if (this->colornote_sprites_ == nullptr){

			this->colornote_sprites_ = new std::map<Color_by_Name, SPRITE>;

			(*this->colornote_sprites_)[Color_Red] = GraphicsDevice.CreateSpriteFromFile(_T("notes/rhythm/note_red.png"));
			(*this->colornote_sprites_)[Color_Green] = GraphicsDevice.CreateSpriteFromFile(_T("notes/rhythm/note_green.png"));
			(*this->colornote_sprites_)[Color_Blue] = GraphicsDevice.CreateSpriteFromFile(_T("notes/rhythm/note_blue.png"));

		}

	};
	virtual ~ABSTRUCT_NOTE(){
	
		if (this->colornote_sprites_ != nullptr) {

			delete this->colornote_sprites_;
			this->colornote_sprites_ = nullptr;

		}
	
	};

	virtual void Update(int nowtime) = 0;
	virtual bool Draw(Vector3 fader_top_pos, float fader_height, float animation_rate, int nowtime, float highspeed) = 0;
	
	virtual int GetTiming(){ return this->timing_; }

	bool CountUpdate(int nowtime, long elapsedcount){

		int betweentime = (this->timing_ - nowtime);

		if (betweentime > this->RANGE_TIME_) return false;

		this->have_count_ += elapsedcount;
		return true;

	}

	float GetHeightRate(){ return this->height_rate_; }
	Color_by_Name GetColor(){ return mycolor_; }
	
	bool isLong(){ return this->longnotes_flag_; }
	bool isRightUp(){ return this->rightup_flag_; }


	void RightUp(){ this->rightup_flag_ = true; }

protected:

	float GetXScale(float highspeed = 0.5f){

		float x_scale = (float)this->have_count_ / (float)this->RANGE_COUNT_;

		x_scale -= (1.0f - highspeed);

		if ( x_scale > 0.0f){

			x_scale /= highspeed;

		}
		else{

			x_scale = 0.0f;

		}

		return x_scale;

	}

	const float WIDTH_;
	const float HEIGHT_;
	const float LINE_HEIGHT_;
	const long RANGE_COUNT_;
	const int RANGE_TIME_;

	bool longnotes_flag_;
	bool rightup_flag_;

	float height_rate_;
	int timing_;
	long have_count_;

	Color_by_Name mycolor_;

	static SPRITE normal_sprite_;
	static std::map<Color_by_Name, SPRITE>* colornote_sprites_;


};

