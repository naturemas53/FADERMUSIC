#include "EffectBomb.h"
#include "Bombs\GreatBomb.h"
#include "Bombs\OKBomb.h"
#include "Bombs\MissBomb.h"
#include "Bombs\UnbelievableBomb.h"

EffectBomb::EffectBomb(){



}

EffectBomb::~EffectBomb(){

	for (auto bomb : this->judgebomb_){

		delete bomb;

	}

	for (auto bomb : this->longbreakbomb_){

		delete bomb;

	}

	for (auto bomb : this->longbomb_){

		delete bomb;

	}

	for (auto bomb : this->flashbomb_){

		delete bomb;

	}
}

void EffectBomb::Update(int elapsedtime){

	auto b_itr = this->nowbeforebomb_.begin();

	while (b_itr != this->nowbeforebomb_.end()){

		if ((*b_itr)->Update(elapsedtime)){

			(*b_itr)->SetUseFlag(false);
			b_itr = this->nowbeforebomb_.erase(b_itr);
			continue;

		}

		b_itr++;

	}

	auto a_itr = this->nowafterbomb_.begin();

	while (a_itr != this->nowafterbomb_.end()){

		if ((*a_itr)->Update(elapsedtime)){

			(*a_itr)->SetUseFlag(false);
			a_itr = this->nowafterbomb_.erase(a_itr);
			continue;

		}

		a_itr++;

	}

}

void EffectBomb::BeforeDraw(){

	for (auto bomb : this->nowbeforebomb_){

		bomb->Draw();

	}

}

void EffectBomb::AfterDraw(){

	for (auto bomb : this->nowafterbomb_){

		bomb->Draw();

	}

}

void EffectBomb::SetJudgeBomb(Vector3 fader_pos, Vector2 fader_inner, float height, JUDGELIST judge){

	if (judge == NONE) return;
	if (judge == OUCH) judge = MISSTIME;

	JudgeBomb* judgebomb;

	for (auto bomb : this->judgebomb_){

		if (bomb->GetType() == judge && !bomb->IsUse()){

			bomb->Init(fader_pos, fader_inner, height);
			this->nowbeforebomb_.push_back(bomb);
			return;

		}

	}

	//‚±‚±‚Ü‚Å—ˆ‚½‚Æ‚«‚Í‰½‚à‚È‚©‚Á‚½

	switch (judge)
	{
	case MISSTIME:

		judgebomb = new MissBomb();

		break;

	case OK:

		judgebomb = new OKBomb();

		break;

	case GREAT:

		judgebomb = new GreatBomb();

		break;

	case UNBELIEVABLE:

		judgebomb = new UnbelievableBomb();

		break;

	default:
		return;
		break;
	}

	judgebomb->Init(fader_pos, fader_inner, height);
	this->judgebomb_.push_back(judgebomb);
	this->nowbeforebomb_.push_back(judgebomb);

}

void EffectBomb::SetLongBreakBomb(Vector3 fader_pos, Vector2 inner_size, float height, Color_by_Name color, float longxscale){

	for (auto bomb : this->longbreakbomb_){

		if (!bomb->IsUse()){

			bomb->Init(fader_pos,inner_size,height,color,longxscale);
			this->nowafterbomb_.push_back(bomb);
			return;

		}

	}

	//‚±‚±‚Ü‚Å—ˆ‚½‚Æ‚«‚Í‰½‚à‚È‚©‚Á‚½

	LongBreakBomb* lonbbreakbomb = new LongBreakBomb();

	lonbbreakbomb->Init(fader_pos,inner_size,height,color,longxscale);
	this->longbreakbomb_.push_back(lonbbreakbomb);
	this->nowafterbomb_.push_back(lonbbreakbomb);

}

void EffectBomb::SetLongBomb(Vector3 fader_pos, Vector2 inner_size, float height, Color_by_Name color){

	for (auto bomb : this->longbomb_){

		if (!bomb->IsUse()){

			bomb->Init(fader_pos, inner_size, height, color);
			this->nowafterbomb_.push_back(bomb);
			return;

		}

	}

	//‚±‚±‚Ü‚Å—ˆ‚½‚Æ‚«‚Í‰½‚à‚È‚©‚Á‚½

	LongBomb* longbomb = new LongBomb();

	longbomb->Init(fader_pos, inner_size, height, color);
	this->longbomb_.push_back(longbomb);
	this->nowafterbomb_.push_back(longbomb);

}

void EffectBomb::SetFlashBomb(Vector3 fader_pos, Vector2 inner_size, float height){

	for (auto bomb : this->flashbomb_){

		if (!bomb->IsUse()){

			bomb->Init(fader_pos, inner_size, height);
			this->nowafterbomb_.push_back(bomb);
			return;

		}

	}

	//‚±‚±‚Ü‚Å—ˆ‚½‚Æ‚«‚Í‰½‚à‚È‚©‚Á‚½

	FlashBomb* flashbomb = new FlashBomb();

	flashbomb->Init(fader_pos, inner_size, height);
	this->flashbomb_.push_back(flashbomb);
	this->nowafterbomb_.push_back(flashbomb);

}