#include "EffectBomb.h"
#include "Bombs\GreatBomb.h"
#include "Bombs\OKBomb.h"
#include "Bombs\MissBomb.h"
#include "Bombs\UnbelievableBomb.h"

EffectBomb::EffectBomb(){



}

EffectBomb::~EffectBomb(){

	for (auto bomb : this->judgebombs_){

		delete bomb;

	}

}

void EffectBomb::Update(int elapsedtime){

	auto itr = this->nowbomb_.begin();

	while (itr != this->nowbomb_.end()){

		if ((*itr)->Update(elapsedtime)){

			(*itr)->SetUseFlag(false);
			itr = this->nowbomb_.erase(itr);
			continue;

		}

		itr++;

	}

}

void EffectBomb::Draw(){

	for (auto bomb : this->nowbomb_){

		bomb->Draw();

	}

}

void EffectBomb::SetJudgeBomb(Vector3 fader_pos, Vector2 fader_inner, float height, JUDGELIST judge){

	if (judge == NONE) return;
	if (judge == OUCH) judge = MISSTIME;

	for (auto bomb : this->judgebombs_){

		if (bomb->GetType() == judge && !bomb->IsUse()){

			bomb->Init(fader_pos,fader_inner,height);
			this->nowbomb_.push_back(bomb);
			return;

		}

	}

	//‚±‚±‚Ü‚Å—ˆ‚½‚Æ‚«‚Í‰½‚à‚È‚©‚Á‚½

	JudgeBomb* newbomb;

	switch (judge)
	{
	case MISSTIME:

		newbomb = new MissBomb();

		break;

	case OK:

		newbomb = new OKBomb();

		break;

	case GREAT:

		newbomb = new GreatBomb();

		break;

	case UNBELIEVABLE:

		newbomb = new UnbelievableBomb();

		break;

	default:
		return;
		break;
	}

	newbomb->Init(fader_pos,fader_inner,height);
	this->judgebombs_.push_back(newbomb);
	this->nowbomb_.push_back(newbomb);

}
