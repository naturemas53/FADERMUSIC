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

	FADER(Vector3 draw_pos, Keys asign_key);
	~FADER();

	void Update(int nowtime, int elapsedtime, float button_height_rate, long elapsedcount);
	void Draw(float button_height_rate, float animetion_rate, int nowtime, float highspeed);

	void InNote(ABSTRUCT_NOTE* innote);
	JUDGELIST GetScoreJudge(){ return this->score_judge_; }
	JUDGELIST GetAccuracyJudge(){ return this->accuracy_judge_; }

	void SetBPM(int bpm, int quater_rhythm){

		this->songbpm_ = bpm;
		this->quater_rhythm_ = quater_rhythm;

	}

private:

	void SingleNoteCheck(std::list<ABSTRUCT_NOTE*>::iterator top_itr, int nowtime, float button_height_rate);
	void LongNoteCheck(std::list<ABSTRUCT_NOTE*>::iterator top_itr, int nowtime, int elapsedtime, float button_height_rate);
	void ScaleUpdate(int nowtime, long elapsedcount);

	bool IsInForButton(std::list<ABSTRUCT_NOTE*>::iterator top_itr, float button_height_rate);

	void NoteErase(std::list<ABSTRUCT_NOTE*>::iterator erase_itr,JUDGELIST judge);

	JUDGELIST Judge(int pushtime);



	static SPRITE normal_sprite_;
	static SPRITE button_sprite_;
	static std::map<Color_by_Name, SPRITE>* color_playareas_;


	const float HEIGHT_;
	const float WIDTH_;
	const float INNER_HEIGHT_;
	const float INNER_WIDTH_;
	const float INNER_TOP_POS_;
	const float INNER_LEFT_POS_;
	const float BUTTON_SIZE_;
	const float ACCEPTABLE_RANGE_;
	const Keys ASIGN_KEY_;
	const Vector3 DRAW_POS_;
	
	std::list<ABSTRUCT_NOTE*> notelist_;

	JUDGE_DISPLAY* judge_display_;

	JUDGELIST longjudge_;
	JUDGELIST score_judge_;
	JUDGELIST accuracy_judge_;

	int total_elapsed_;
	int songbpm_;
	int quater_rhythm_;

};

