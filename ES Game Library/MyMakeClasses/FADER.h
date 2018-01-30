#pragma once
#include "../ESGLib.h"
#include "JUDGELIST_ENUM.h"
#include "EffectBomb.h"
#include <list>
#include <map>

class ABSTRUCT_NOTE;

struct JUDGENOTICE{

	JUDGELIST judge;
	float height;

	JUDGENOTICE(){

		judge = NONE;
		height = 0.0f;

	}

};

class FADER
{
public:

	FADER(Vector3 draw_pos, Keys asign_key);
	~FADER();

	void Update(int nowtime, int elapsedtime, float button_height_rate, long elapsedcount);
	void Draw(float button_height_rate,float animetion_rate, int nowtime, float highspeed);

	void InNote(ABSTRUCT_NOTE* innote);

	JUDGENOTICE GetScoreJudge(){ return this->score_judge_; }
	JUDGELIST GetAccuracyJudge(){ return this->accuracy_judge_; }
	Vector2 GetSize(){ return this->SIZE_; }
	Vector2 GetInnerSize(){ return this->INNER_SIZE_; }
	Vector3 GetInnerPos(){

		Vector3 innerpos = this->DRAW_POS_;
		innerpos.x += this->INNER_LEFT_POS_;
		innerpos.y += this->INNER_TOP_POS_;

		return innerpos;

	}

	Vector3 GetDrawPos(){ return this->DRAW_POS_; }

	void SetBPM(int bpm, int quater_rhythm){

		this->songbpm_ = bpm;
		this->quater_rhythm_ = quater_rhythm;

	}

private:

	void FaderDraw(int animecount,float animationrate);
	void NoteDraw(float animationrate,int nowtime,float highspeed);
	void ButtonDraw(float button_height_rate);

	void SingleNoteCheck(std::list<ABSTRUCT_NOTE*>::iterator top_itr, int nowtime, float button_height_rate);
	void LongNoteCheck(std::list<ABSTRUCT_NOTE*>::iterator top_itr, int nowtime, int elapsedtime, float button_height_rate);
	void ScaleUpdate(int nowtime, long elapsedcount);

	bool IsInForButton(std::list<ABSTRUCT_NOTE*>::iterator top_itr, float button_height_rate);

	void NoteErase(std::list<ABSTRUCT_NOTE*>::iterator erase_itr,JUDGELIST judge,float height);

	JUDGELIST Judge(int pushtime);

	static SPRITE normal_sprite_;
	static SPRITE button_sprite_;
	static std::map<Color_by_Name, SPRITE>* color_playareas_;
	static SOUND pushsound_;

	const Vector2 SIZE_;
	const Vector2 INNER_SIZE_;
	const float INNER_TOP_POS_;
	const float INNER_LEFT_POS_;
	const float BUTTON_SIZE_;
	const float ACCEPTABLE_RANGE_;
	const Keys ASIGN_KEY_;
	const Vector3 DRAW_POS_;
	
	std::list<ABSTRUCT_NOTE*> notelist_;

	JUDGELIST longjudge_;
	JUDGENOTICE score_judge_;
	JUDGELIST accuracy_judge_;

	EffectBomb* effectbomb_;

	int total_elapsed_;
	int songbpm_;
	int quater_rhythm_;

};

