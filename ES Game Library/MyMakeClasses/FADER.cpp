#include "FADER.h"
#include "SINGLENOTE.h"
#include "LONGNOTE.h"
#include <cstdlib>
#include "JUDGELIST_ENUM.h"
#include "JUDGE_DISPLAY.h"
#include "CONTROLL.h"

SPRITE FADER::button_sprite_ = nullptr;
SPRITE FADER::normal_sprite_ = nullptr;
std::map<Color_by_Name, SPRITE>* FADER::color_playareas_ = nullptr;

FADER::FADER(Vector3 draw_pos, Keys asign_key) :
HEIGHT_(580.0f),
WIDTH_(114.0f),
INNER_HEIGHT_(540.0f),
INNER_TOP_POS_(20.0f),
INNER_LEFT_POS_(20.0f),
BUTTON_SIZE_(84.0f),
ACCEPTABLE_RANGE_(0.009f),
ASIGN_KEY_(asign_key),
DRAW_POS_(draw_pos)
{

	if (this->normal_sprite_ == nullptr) this->normal_sprite_ = GraphicsDevice.CreateSpriteFromFile(_T("fader/fader_normal.png"));
	if (this->button_sprite_ == nullptr) this->button_sprite_ = GraphicsDevice.CreateSpriteFromFile(_T("button/newbutton_normal.png"));

	if (this->color_playareas_ == nullptr){

		this->color_playareas_ = new std::map<Color_by_Name, SPRITE>;

		(*this->color_playareas_)[Color_Red] = GraphicsDevice.CreateSpriteFromFile(_T("fader/fader_long_red.png"));
		(*this->color_playareas_)[Color_Green] = GraphicsDevice.CreateSpriteFromFile(_T("fader/fader_long_green.png"));
		(*this->color_playareas_)[Color_Blue] = GraphicsDevice.CreateSpriteFromFile(_T("fader/fader_long_blue.png"));

	}

	Vector3 pos = draw_pos;
	pos.y += INNER_TOP_POS_;

	this->judge_display_ = new JUDGE_DISPLAY(pos,this->INNER_HEIGHT_,this->WIDTH_);

	this->longjudge_ = NONE;
	this->score_judge_ = NONE;
	this->accuracy_judge_ = NONE;

	this->total_elapsed_ = 0;
}


FADER::~FADER()
{

	if (this->color_playareas_ != nullptr){

		delete this->color_playareas_;
		this->color_playareas_ = nullptr;

	}

	delete judge_display_;

}

void FADER::Update(unsigned nowtime, unsigned elapsedtime_, float button_height_rate){

	KeyboardState key_state = Keyboard->GetState();

	this->score_judge_ = NONE;
	this->accuracy_judge_ = NONE;

	this->total_elapsed_ += elapsedtime_;


	auto s_itr = this->notelist_.begin();
	
	if (s_itr != this->notelist_.end())
		((*s_itr)->isLong()) ? LongNoteCheck(s_itr, nowtime,elapsedtime_, button_height_rate) : SingleNoteCheck(s_itr, nowtime, button_height_rate);

	this->judge_display_->Update();
	

}

void FADER::SingleNoteCheck(std::list<ABSTRUCT_NOTE*>::iterator top_itr, unsigned nowtime, float button_height_rate){

	int betweentime = (int)nowtime - (int)(*top_itr)->GetTiming();

	if (betweentime > OK){

		NoteErase(top_itr, MISSTIME);

		return;

	}
	else if (betweentime > -OK  && CONTROLL::GetInstance().BufferIsPress(ASIGN_KEY_)){

		if (this->IsInForButton(top_itr, button_height_rate)){

			JUDGELIST judge = Judge(abs(betweentime));

			NoteErase(top_itr, judge);
			return;

		}
		else{

			NoteErase(top_itr, OUCH);
			return;

		}

	}

}

void FADER::LongNoteCheck(std::list<ABSTRUCT_NOTE*>::iterator top_itr, unsigned nowtime, unsigned elapsedtime_, float button_height_rate){

	LONGNOTE* top_long = (LONGNOTE*)(*top_itr);

	(*top_itr)->Update(nowtime);

	int betweentime = (int)nowtime - (int)(*top_long).GetTiming();

	if (top_long->IsPush()){

		if (CONTROLL::GetInstance().StateIsDown(ASIGN_KEY_)){

			if (this->IsInForButton(top_itr, button_height_rate)){

				if (this->total_elapsed_ > this->quater_rhythm_ / 4){

					this->judge_display_->SetBomb(this->longjudge_, (*top_itr)->GetHeightRate());
					this->score_judge_ = this->longjudge_;

					this->total_elapsed_ -= this->quater_rhythm_ / 4;
				
				}

			}
			else{

				top_long->DownRight(elapsedtime_);

				if (!top_long->IsHaveRightPower()){

					NoteErase(top_itr, MISSTIME);
					return;
				}
				
			}

			if (top_long->GetTimingSlowMostPoint() < nowtime){


				NoteErase(top_itr, this->longjudge_);
				return;

			}

		}
		else{


			NoteErase(top_itr, MISSTIME);
			return;

		}

	}
	else if (betweentime > -OK && CONTROLL::GetInstance().BufferIsPress(ASIGN_KEY_)){

		if (this->IsInForButton(top_itr, button_height_rate)){

			this->longjudge_ = Judge(abs(betweentime));

			this->judge_display_->SetBomb(this->longjudge_, (*top_itr)->GetHeightRate());
			top_long->Push();
			this->total_elapsed_ = 0;

		}
		else{

			NoteErase(top_itr, OUCH);
			return;

		}


	}else if (betweentime > OK){
	
		NoteErase(top_itr,MISSTIME);
		return;

	}


}

void FADER::Draw(float button_height_rate, float animetion_rate, unsigned nowtime, int range_hours_show){

	int animenum = (int)(animetion_rate * 90.0f);

	auto s_itr = this->notelist_.begin();

	LONGNOTE* longnote_;

	if (s_itr != this->notelist_.end()){

		if ((*s_itr)->isLong()){


			longnote_ = (LONGNOTE*)(*s_itr);
			if (longnote_->IsPush()){

				SpriteBatch.Draw(*(*this->color_playareas_)[longnote_->GetColor()], this->DRAW_POS_,
					RectWH((animenum % 30) * WIDTH_, (animenum / 30) * HEIGHT_, WIDTH_, HEIGHT_), 1.0f);

			}
			else{

				SpriteBatch.Draw(*this->normal_sprite_, this->DRAW_POS_,
					RectWH((animenum % 30) * WIDTH_, (animenum / 30) * HEIGHT_, WIDTH_, HEIGHT_), 1.0f);

			}


		}
		else{

			SpriteBatch.Draw(*this->normal_sprite_, this->DRAW_POS_,
				RectWH((animenum % 30) * WIDTH_, (animenum / 30) * HEIGHT_, WIDTH_, HEIGHT_), 1.0f);

		}

	}
	else{

		SpriteBatch.Draw(*this->normal_sprite_, this->DRAW_POS_,
			RectWH((animenum % 30) * WIDTH_, (animenum / 30) * HEIGHT_, WIDTH_, HEIGHT_), 1.0f);

	}


	Vector3 top_pos = this->DRAW_POS_;
	top_pos.y += INNER_TOP_POS_;
	top_pos.x += INNER_LEFT_POS_;
	
	//ノーツの描画　ロング→シングル
	s_itr = this->notelist_.begin();

	while (s_itr != this->notelist_.end()){

		if ((*s_itr)->isLong()){

			longnote_ = (LONGNOTE*)(*s_itr);

			int betweentime = (int)(*s_itr)->GetTiming() - (int)nowtime;

			if (betweentime > range_hours_show){

				break;

			}

			(*s_itr)->Draw(top_pos, INNER_HEIGHT_, animetion_rate, nowtime, range_hours_show);

		}

		s_itr++;

	}

	s_itr = this->notelist_.begin();

	while (s_itr != this->notelist_.end()){
	
		int betweentime = (int)(*s_itr)->GetTiming() - (int)nowtime;

		if (betweentime > range_hours_show){
		
			break;
		
		}
		else if ((*s_itr)->isLong()){

			s_itr++;
			continue;

		}

		(*s_itr)->Draw(top_pos, INNER_HEIGHT_, animetion_rate, nowtime, range_hours_show);
	
		s_itr++;

	}

	Vector3 button_pos_ = top_pos;

	button_pos_.y -= 5.0f; //線の太さ
	button_pos_.x -= 5.0f; //線の太さ
	button_pos_.y += (INNER_HEIGHT_ - BUTTON_SIZE_ + 10.0f) * button_height_rate;//5.0fは線の太さ * 2

	SpriteBatch.Draw(*this->button_sprite_, button_pos_, 1.0f);

	this->judge_display_->Draw();

}

void FADER::InNote(ABSTRUCT_NOTE* innote){
	
		this->notelist_.push_back(innote);

}

bool FADER::IsInForButton(std::list<ABSTRUCT_NOTE*>::iterator top_itr, float button_height_rate){

	float button_top_rate = button_height_rate * ((this->INNER_HEIGHT_ - this->BUTTON_SIZE_) / this->INNER_HEIGHT_);
	float button_down_rate = button_top_rate + (1.0f - (this->INNER_HEIGHT_ - this->BUTTON_SIZE_) / this->INNER_HEIGHT_);

	if ((*top_itr)->GetHeightRate() > button_top_rate - ACCEPTABLE_RANGE_ &&
		(*top_itr)->GetHeightRate() < button_down_rate + ACCEPTABLE_RANGE_){

		return true;

	}

	return false;


}

void FADER::NoteErase(std::list<ABSTRUCT_NOTE*>::iterator erase_itr, JUDGELIST judge){

	(*erase_itr)->Used();

	this->judge_display_->SetBomb(judge, (*erase_itr)->GetHeightRate());

	this->notelist_.erase(erase_itr);

	this->score_judge_ = judge;
	this->accuracy_judge_ = judge;

	return;
}

JUDGELIST FADER::Judge(int pushtime){

	JUDGELIST judge;

	if (UNBELIEVABLE > pushtime){
		judge = UNBELIEVABLE;
	}
	else if (GREAT > pushtime){
		judge = GREAT;
	}
	else if (OK > pushtime){
		judge = OK;
	}
	else{
		judge = MISSTIME;
	}

	return judge;

}