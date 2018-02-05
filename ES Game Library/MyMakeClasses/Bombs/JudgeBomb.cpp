#include "JudgeBomb.h"
SPRITE JudgeBomb::addsprite_ = nullptr;

JudgeBomb::JudgeBomb(int animetime, int holizoncell, int maxcell, Vector2 cellsize, JUDGELIST myjudge) :
AbstructBomb(animetime, holizoncell, maxcell, cellsize) {

	if (this->addsprite_ == nullptr){

		this->addsprite_ = GraphicsDevice.CreateSpriteFromFile(_T("bomb/white_bomb.png"));

	}

	this->judge_ = myjudge;

};

JudgeBomb::~JudgeBomb(){

	if (this->addsprite_ != nullptr){

		GraphicsDevice.ReleaseSprite(this->addsprite_);
		this->addsprite_ = nullptr;

	}

}