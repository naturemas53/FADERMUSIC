#pragma once
#include "../ESGLib.h"
#include <list>
#include <map>

class ABSTRUCT_NOTE;
class JUDGE_DISPLAY;
enum JUDGELIST;

class FADER
{
public:

	FADER(Vector3 draw_pos,Keys asign_key);
	~FADER();

	void Update(unsigned nowtime, unsigned elapsedtime, float button_height_rate);
	void Draw(float button_height_rate, float animetion_rate, unsigned nowtime, int range_hours_show);

	void InNote(ABSTRUCT_NOTE* innote);
	JUDGELIST GetJudge(){ return this->have_judge_; }

private:

	void SingleNoteCheck(std::list<ABSTRUCT_NOTE*>::iterator top_itr,unsigned nowtime,float button_height_rate);
	void LongNoteCheck(std::list<ABSTRUCT_NOTE*>::iterator top_itr, unsigned nowtime, unsigned elapsedtime,float button_height_rate);

	void NoteErase(std::list<ABSTRUCT_NOTE*>::iterator erase_itr,JUDGELIST judge);

	JUDGELIST Judge(int pushtime);

	static SPRITE normal_sprite_;
	static SPRITE button_sprite_;
	static std::map<Color_by_Name, SPRITE>* color_playareas_;


	const float HEIGHT_;
	const float WIDTH_;
	const float INNER_HEIGHT_;
	const float INNER_TOP_POS_;
	const float INNER_LEFT_POS_;
	const float BUTTON_SIZE_;
	const float ACCEPTABLE_RANGE_;
	const Keys ASIGN_KEY_;

	Vector3 draw_pos_;
	
	std::list<ABSTRUCT_NOTE*> notelist_;

	JUDGE_DISPLAY* judge_display_;

	JUDGELIST longjudge_;
	JUDGELIST have_judge_;

};

