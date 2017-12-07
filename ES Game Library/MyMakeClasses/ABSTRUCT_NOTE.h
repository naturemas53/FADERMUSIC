#pragma once
#include "../ESGLib.h"
#include <map>


class ABSTRUCT_NOTE
{
public:
	ABSTRUCT_NOTE():
		WIDTH_(74.0f),
		HEIGHT_(30.0f),
		LINE_HEIGHT_(10.0f)
	{
		use_flag_ = true;
		rightup_flag_ = false;

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

	virtual void Update(unsigned nowtime) = 0;
	virtual void Draw(Vector3 fader_top_pos, float fader_height, float animation_rate, unsigned nowtime, int timeup_to_timing) = 0;
	
	virtual unsigned GetTiming(){ return this->timing_; }
	float GetHeightRate(){ return this->height_rate_; }
	Color_by_Name GetColor(){ return mycolor_; }

	bool isLong(){ return this->longnotes_flag_; }
	bool isUsing(){ return this->use_flag_; }
	bool isRightUp(){ return this->rightup_flag_; }

	void RightUp(){ this->rightup_flag_ = true; }
	void Used(){ this->use_flag_ = false; }

protected:

	const float WIDTH_;
	const float HEIGHT_;
	const float LINE_HEIGHT_;

	bool use_flag_;
	bool longnotes_flag_;
	bool rightup_flag_;

	float height_rate_;
	unsigned timing_;

	Color_by_Name mycolor_;

	static SPRITE normal_sprite_;
	static std::map<Color_by_Name, SPRITE>* colornote_sprites_;


};

