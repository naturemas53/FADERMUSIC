#include "FADER.h"
#include "SINGLENOTE.h"
#include "LONGNOTE.h"
#include <cstdlib>

SPRITE FADER::button_sprite_ = nullptr;
SPRITE FADER::normal_sprite_ = nullptr;
std::map<Color_by_Name, SPRITE>* FADER::color_playareas_ = nullptr;

FADER::FADER(Vector3 draw_pos, BUTTONTYPE asign_key) :
SIZE_(Vector2(236.0f,596.0f)),
INNER_SIZE_(Vector2(180.0f,540.0f)),
INNER_TOP_POS_((this->SIZE_.x - this->INNER_SIZE_.x) / 2.0f),
INNER_LEFT_POS_((this->SIZE_.y - this->INNER_SIZE_.y) / 2.0f),
BUTTON_SIZE_(195.0f),
ACCEPTABLE_RANGE_(0.009f),
ASIGN_KEY_(asign_key),
DRAW_POS_(draw_pos),
INNER_POS_(Vector3(draw_pos.x + this->INNER_TOP_POS_, draw_pos.y + this->INNER_LEFT_POS_, 0.0f))
{

	if (this->normal_sprite_ == nullptr) this->normal_sprite_ = GraphicsDevice.CreateSpriteFromFile(_T("fader/fader_normal.png"));
	if (this->button_sprite_ == nullptr) this->button_sprite_ = GraphicsDevice.CreateSpriteFromFile(_T("button/newbutton_normal.png"));

	if (this->color_playareas_ == nullptr){

		this->color_playareas_ = new std::map<Color_by_Name, SPRITE>;

		(*this->color_playareas_)[Color_Red] = GraphicsDevice.CreateSpriteFromFile(_T("fader/fader_long_red.png"));
		(*this->color_playareas_)[Color_Green] = GraphicsDevice.CreateSpriteFromFile(_T("fader/fader_long_green.png"));
		(*this->color_playareas_)[Color_Blue] = GraphicsDevice.CreateSpriteFromFile(_T("fader/fader_long_blue.png"));

	}

	this->effectbomb_ = new EffectBomb();

	Vector3 pos = draw_pos;
	pos.y += INNER_TOP_POS_;

	this->longjudge_ = NONE;
	this->score_judge_ = JUDGENOTICE();
	this->accuracy_judge_ = NONE;

	this->total_elapsed_ = 0;

	this->effectbomb_ = new EffectBomb();
	this->clapsound_ = new ClapSound();
}


FADER::~FADER()
{

	if (this->color_playareas_ != nullptr){

		GraphicsDevice.ReleaseSprite((*this->color_playareas_)[Color_Red]);
		GraphicsDevice.ReleaseSprite((*this->color_playareas_)[Color_Green]);
		GraphicsDevice.ReleaseSprite((*this->color_playareas_)[Color_Blue]);

		delete this->color_playareas_;
		this->color_playareas_ = nullptr;

	}

	if (this->normal_sprite_ != nullptr){

		GraphicsDevice.ReleaseSprite(this->normal_sprite_);
		this->normal_sprite_ = nullptr;

	}

	if (this->button_sprite_ != nullptr){

		GraphicsDevice.ReleaseSprite(this->button_sprite_);
		this->button_sprite_ = nullptr;

	}

	delete this->effectbomb_;
	delete this->clapsound_;

}

void FADER::Update(int nowtime, int elapsedtime, float button_height_rate, long elapsedcount){

	KeyboardState key_state = Keyboard->GetState();

	this->score_judge_.judge= NONE;
	this->accuracy_judge_ = NONE;

	this->total_elapsed_ += elapsedtime;

	this->effectbomb_->Update(elapsedtime);

	auto s_itr = this->notelist_.begin();
	
	if (s_itr != this->notelist_.end())
		((*s_itr)->isLong()) ? LongNoteCheck(s_itr, nowtime, elapsedtime, button_height_rate) : SingleNoteCheck(s_itr, nowtime, button_height_rate);
	
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

			if (judge == UNBELIEVABLE){

				this->effectbomb_->SetFlashBomb(this->INNER_POS_, this->INNER_SIZE_, (*top_itr)->GetHeightRate());

			}

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

					this->effectbomb_->SetJudgeBomb(this->INNER_POS_, this->INNER_SIZE_,(*top_itr)->GetHeightRate(), this->longjudge_);

					this->total_elapsed_ -= this->quater_rhythm_ / 4;
				
				}

			}
			else{

				top_long->DownRight(elapsedtime_);

				if (!top_long->IsHaveRightPower()){

					this->effectbomb_->SetLongBreakBomb(this->INNER_POS_, this->INNER_SIZE_,
						top_long->GetHeightRate(), top_long->GetColor(), top_long->GetLongXScale());
					NoteErase(top_itr, MISSTIME,(*top_itr)->GetHeightRate());
					return;
				}
				
			}

			if (top_long->GetTimingSlowMostPoint() < nowtime){

				this->effectbomb_->SetLongBomb(this->INNER_POS_, this->INNER_SIZE_,
					top_long->GetHeightRate(), top_long->GetColor());
				NoteErase(top_itr, this->longjudge_, (*top_itr)->GetHeightRate());
				return;

			}

		}
		else{

			JUDGELIST releasejudge;
			JUDGELIST finaljudge;
			releasejudge = Judge(abs(top_long->GetTimingSlowMostPoint() - nowtime));
			if (releasejudge != MISSTIME && releasejudge != OUCH){
				finaljudge = this->longjudge_;
			}
			else{
				finaljudge = MISSTIME;
				this->effectbomb_->SetLongBreakBomb(this->INNER_POS_,this->INNER_SIZE_,
					top_long->GetHeightRate(),top_long->GetColor(),top_long->GetLongXScale());
			}
			NoteErase(top_itr, finaljudge, (*top_itr)->GetHeightRate());
			return;

		}

	}
	else if (betweentime > -OK && CONTROLL::GetInstance().BufferIsPress(ASIGN_KEY_)){

		if (this->IsInForButton(top_itr, button_height_rate)){

			this->longjudge_ = Judge(abs(betweentime));
			this->score_judge_.judge = this->longjudge_;
			this->score_judge_.height = (*top_itr)->GetHeightRate();

			if (this->longjudge_ == UNBELIEVABLE){

				this->effectbomb_->SetFlashBomb(this->INNER_POS_, this->INNER_SIZE_, (*top_itr)->GetHeightRate());

			}
			this->clapsound_->Play(this->longjudge_);

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

	this->effectbomb_->BeforeDraw();

	this->NoteDraw(animationrate,nowtime,highspeed);

	SpriteBatch.Begin();
	this->ButtonDraw(button_height_rate);
	SpriteBatch.End();

	this->effectbomb_->AfterDraw();
	
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
	//ノーツの描画
	auto itr = this->notelist_.begin();
	while (itr != this->notelist_.end()){

		if (!(*itr)->Draw(top_pos, this->INNER_SIZE_, animationrate, nowtime, highspeed, false))break;
		itr++;

	}
	SpriteBatch.End();

	GraphicsDevice.SetBlendMode(DXGBLEND_ADD);
	SpriteBatch.Begin();
	itr = this->notelist_.begin();
	while (itr != this->notelist_.end()){

		if (!(*itr)->Draw(top_pos, this->INNER_SIZE_, animationrate, nowtime, highspeed, true))break;
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

	button_pos_.y -= 5.0f; //線の太さ
	button_pos_.x -= 8.0f; //線の太さ
	button_pos_.y += (this->INNER_SIZE_.y - BUTTON_SIZE_ + 10.0f) * button_height_rate;//5.0fは線の太さ * 2

	SpriteBatch.Draw(*this->button_sprite_, button_pos_, 1.0f);

}

void FADER::InNote(ABSTRUCT_NOTE* innote){
	
	unsigned size = this->notelist_.size();

	if (size == 0){

		this->notelist_.push_back(innote);
		return;
	}

	auto itr = this->notelist_.begin();
	auto e_itr = this->notelist_.end();

	int inserttiming = innote->GetTiming();
	int checktiming = 0;

	while (itr != e_itr){

		checktiming = (*itr)->GetTiming();

		if (inserttiming < checktiming){

			this->notelist_.insert(itr,innote);
			return;

		}

		itr++;

	}

	//ここまで来たときは遅い
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

	this->effectbomb_->SetJudgeBomb( this->INNER_POS_, this->INNER_SIZE_, (*erase_itr)->GetHeightRate(), judge);

	this->notelist_.erase(erase_itr);

	this->clapsound_->Play(judge);

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