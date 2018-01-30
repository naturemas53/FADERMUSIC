#include "FADER.h"
#include "SINGLENOTE.h"
#include "LONGNOTE.h"
#include <cstdlib>
#include "CONTROLL.h"

SPRITE FADER::button_sprite_ = nullptr;
SPRITE FADER::normal_sprite_ = nullptr;
std::map<Color_by_Name, SPRITE>* FADER::color_playareas_ = nullptr;
SOUND FADER::pushsound_ = nullptr;

FADER::FADER(Vector3 draw_pos, Keys asign_key) :
SIZE_(Vector2(236.0f,596.0f)),
INNER_SIZE_(Vector2(180.0f,540.0f)),
INNER_TOP_POS_((this->SIZE_.x - this->INNER_SIZE_.x) / 2.0f),
INNER_LEFT_POS_((this->SIZE_.y - this->INNER_SIZE_.y) / 2.0f),
BUTTON_SIZE_(195.0f),
ACCEPTABLE_RANGE_(0.009f),
ASIGN_KEY_(asign_key),
DRAW_POS_(draw_pos)
{

	if (this->normal_sprite_ == nullptr) this->normal_sprite_ = GraphicsDevice.CreateSpriteFromFile(_T("fader/fader_normal.png"));
	if (this->button_sprite_ == nullptr) this->button_sprite_ = GraphicsDevice.CreateSpriteFromFile(_T("button/newbutton_normal.png"));
	if (this->pushsound_ == nullptr) this->pushsound_ = SoundDevice.CreateSoundFromFile(_T("pushsound.wav"));

	if (this->color_playareas_ == nullptr){

		this->color_playareas_ = new std::map<Color_by_Name, SPRITE>;

		(*this->color_playareas_)[Color_Red] = GraphicsDevice.CreateSpriteFromFile(_T("fader/fader_long_red.png"));
		(*this->color_playareas_)[Color_Green] = GraphicsDevice.CreateSpriteFromFile(_T("fader/fader_long_green.png"));
		(*this->color_playareas_)[Color_Blue] = GraphicsDevice.CreateSpriteFromFile(_T("fader/fader_long_blue.png"));

	}

	Vector3 pos = draw_pos;
	pos.y += INNER_TOP_POS_;

	this->longjudge_ = NONE;
	this->score_judge_ = JUDGENOTICE();
	this->accuracy_judge_ = NONE;

	this->total_elapsed_ = 0;

	effectbomb_ = new EffectBomb();
}


FADER::~FADER()
{

	if (this->color_playareas_ != nullptr){

		delete this->color_playareas_;
		this->color_playareas_ = nullptr;

	}

	delete this->effectbomb_;

}

void FADER::Update(int nowtime, int elapsedtime_, float button_height_rate, long elapsedcount){

	KeyboardState key_state = Keyboard->GetState();

	this->score_judge_.judge= NONE;
	this->accuracy_judge_ = NONE;

	this->total_elapsed_ += elapsedtime_;

	this->effectbomb_->Update();

	auto s_itr = this->notelist_.begin();
	
	if (s_itr != this->notelist_.end())
		((*s_itr)->isLong()) ? LongNoteCheck(s_itr, nowtime,elapsedtime_, button_height_rate) : SingleNoteCheck(s_itr, nowtime, button_height_rate);
	
	this->ScaleUpdate(nowtime,elapsedcount);

}

void FADER::SingleNoteCheck(std::list<ABSTRUCT_NOTE*>::iterator top_itr, int nowtime, float button_height_rate){

	int betweentime = (int)nowtime - (int)(*top_itr)->GetTiming();

	if (betweentime > OK){

		NoteErase(top_itr, MISSTIME,(*top_itr)->GetHeightRate());

		return;

	}
	else if (betweentime > -OK  && CONTROLL::GetInstance().BufferIsPress(ASIGN_KEY_)){

		if (this->IsInForButton(top_itr, button_height_rate)){

			JUDGELIST judge = Judge(abs(betweentime));
			this->pushsound_->Play();
			NoteErase(top_itr, judge, (*top_itr)->GetHeightRate());
			return;

		}
		else{

			NoteErase(top_itr, OUCH, (*top_itr)->GetHeightRate());
			return;

		}

	}

}

void FADER::LongNoteCheck(std::list<ABSTRUCT_NOTE*>::iterator top_itr, int nowtime, int elapsedtime_, float button_height_rate){

	LONGNOTE* top_long = (LONGNOTE*)(*top_itr);

	(*top_itr)->Update(nowtime);

	int betweentime = (int)nowtime - (int)(*top_long).GetTiming();

	if (top_long->IsPush()){

		if (CONTROLL::GetInstance().StateIsDown(ASIGN_KEY_)){

			if (this->IsInForButton(top_itr, button_height_rate)){

				if (this->total_elapsed_ > this->quater_rhythm_ / 4){

					this->score_judge_.judge = this->longjudge_;
					this->score_judge_.height = (*top_itr)->GetHeightRate();

					this->effectbomb_->SetBomb((*top_itr), this->longjudge_, (*top_itr)->GetHeightRate());

					this->total_elapsed_ -= this->quater_rhythm_ / 4;
				
				}

			}
			else{

				top_long->DownRight(elapsedtime_);

				if (!top_long->IsHaveRightPower()){

					NoteErase(top_itr, MISSTIME,(*top_itr)->GetHeightRate());
					return;
				}
				
			}

			if (top_long->GetTimingSlowMostPoint() < nowtime){

				this->pushsound_->Play();
				NoteErase(top_itr, this->longjudge_, (*top_itr)->GetHeightRate());
				return;

			}

		}
		else{

			this->pushsound_->Play();
			JUDGELIST releasejudge;
			releasejudge = Judge(top_long->GetTimingSlowMostPoint() - nowtime);
			NoteErase(top_itr, releasejudge, (*top_itr)->GetHeightRate());
			return;

		}

	}
	else if (betweentime > -OK && CONTROLL::GetInstance().BufferIsPress(ASIGN_KEY_)){

		if (this->IsInForButton(top_itr, button_height_rate)){

			this->pushsound_->Play();

			this->longjudge_ = Judge(abs(betweentime));
			this->score_judge_.judge = this->longjudge_;
			this->score_judge_.height = (*top_itr)->GetHeightRate();

			top_long->Push();
			this->total_elapsed_ = 0;

		}
		else{

			NoteErase(top_itr, OUCH, (*top_itr)->GetHeightRate());
			return;

		}


	}else if (betweentime > OK){
	
		NoteErase(top_itr, MISSTIME, (*top_itr)->GetHeightRate());
		return;

	}


}

void FADER::ScaleUpdate(int nowtime, long elapsedcount){

	auto itr = this->notelist_.begin();
	while (itr != notelist_.end()){ 
		(*itr)->CountUpdate(nowtime, elapsedcount);
		itr++;
	}

}

void FADER::Draw(float button_height_rate, float animationrate, int nowtime, float highspeed){

	int animenum = (int)(animationrate * 90.0f);

	Vector3 pos = this->DRAW_POS_;
	pos.y += INNER_TOP_POS_;
	pos.x += INNER_LEFT_POS_;

	this->FaderDraw(animenum, animationrate);

	this->effectbomb_->Draw(pos, this->INNER_SIZE_);


	this->NoteDraw(animationrate,nowtime,highspeed);

	SpriteBatch.Begin();
	this->ButtonDraw(button_height_rate);
	SpriteBatch.End();

}

void FADER::FaderDraw(int animecount, float animationrate){

	auto s_itr = this->notelist_.begin();

	LONGNOTE* longnote;

	SPRITE playareasp = this->normal_sprite_;

	if (s_itr != this->notelist_.end()){
		if ((*s_itr)->isLong()){
			longnote = (LONGNOTE*)(*s_itr);
			if (longnote->IsPush()){

				playareasp = (*this->color_playareas_)[longnote->GetColor()];

			}
		}
	}

	SpriteBatch.Begin();
	SpriteBatch.Draw(*playareasp, this->DRAW_POS_, 1.0f);
	SpriteBatch.End();

	GraphicsDevice.SetBlendMode(DXGBLEND_ADD);
	SpriteBatch.Begin();
	SpriteBatch.Draw(*playareasp, this->DRAW_POS_, animationrate);
	SpriteBatch.End();
	GraphicsDevice.SetBlendMode(DXGBLEND_NORMAL);

}

void FADER::NoteDraw(float animationrate, int nowtime, float highspeed){

	Vector3 top_pos = this->DRAW_POS_;
	top_pos.y += INNER_TOP_POS_;
	top_pos.x += INNER_LEFT_POS_;

	SpriteBatch.Begin();
	//ƒm[ƒc‚Ì•`‰æ
	auto itr = this->notelist_.begin();
	while (itr != this->notelist_.end()){

		if (!(*itr)->Draw(top_pos, this->INNER_SIZE_.y, animationrate, nowtime, highspeed, false))break;
		itr++;

	}
	SpriteBatch.End();

	GraphicsDevice.SetBlendMode(DXGBLEND_ADD);
	SpriteBatch.Begin();
	itr = this->notelist_.begin();
	while (itr != this->notelist_.end()){

		if (!(*itr)->Draw(top_pos, this->INNER_SIZE_.y, animationrate, nowtime, highspeed, true))break;
		itr++;

	}
	SpriteBatch.End();
	GraphicsDevice.SetBlendMode(DXGBLEND_NORMAL);

}

void FADER::ButtonDraw(float button_height_rate){

	Vector3 top_pos = this->DRAW_POS_;
	top_pos.y += INNER_TOP_POS_;
	top_pos.x += INNER_LEFT_POS_;

	Vector3 button_pos_ = top_pos;

	button_pos_.y -= 5.0f; //ü‚Ì‘¾‚³
	button_pos_.x -= 8.0f; //ü‚Ì‘¾‚³
	button_pos_.y += (this->INNER_SIZE_.y - BUTTON_SIZE_ + 10.0f) * button_height_rate;//5.0f‚Íü‚Ì‘¾‚³ * 2

	SpriteBatch.Draw(*this->button_sprite_, button_pos_, 1.0f);

}

void FADER::InNote(ABSTRUCT_NOTE* innote){
	
		this->notelist_.push_back(innote);

}

bool FADER::IsInForButton(std::list<ABSTRUCT_NOTE*>::iterator top_itr, float button_height_rate){

	float button_top_rate = button_height_rate * ((this->INNER_SIZE_.y - this->BUTTON_SIZE_) / this->INNER_SIZE_.y);
	float button_down_rate = button_top_rate + (1.0f - (this->INNER_SIZE_.y - this->BUTTON_SIZE_) / this->INNER_SIZE_.y);

	if ((*top_itr)->GetHeightRate() > button_top_rate - ACCEPTABLE_RANGE_ &&
		(*top_itr)->GetHeightRate() < button_down_rate + ACCEPTABLE_RANGE_){

		return true;

	}

	return false;


}

void FADER::NoteErase(std::list<ABSTRUCT_NOTE*>::iterator erase_itr, JUDGELIST judge,float height){

	this->effectbomb_->SetBomb((*erase_itr),judge,height);

	this->notelist_.erase(erase_itr);

	this->score_judge_.judge = judge;
	this->score_judge_.height = height;
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