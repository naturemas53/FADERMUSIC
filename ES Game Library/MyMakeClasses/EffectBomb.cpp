#include "EffectBomb.h"

std::map<JUDGELIST, SPRITE>* EffectBomb::bombsprites_ = nullptr;
SPRITE EffectBomb::addalphabomb_ = nullptr;

EffectBomb::EffectBomb():
CELLSIZE_(Vector2(120.0f,120.0f)),
ANIMECOUNT_(5),
ONECELLCOUNT_(2)
{

	if (this->bombsprites_ == nullptr){

		this->bombsprites_ = new std::map<JUDGELIST, SPRITE>;

		(*this->bombsprites_)[UNBELIEVABLE] = GraphicsDevice.CreateSpriteFromFile(_T("bomb/pink_bomb.png"));
		(*this->bombsprites_)[GREAT] = GraphicsDevice.CreateSpriteFromFile(_T("bomb/orenge_bomb.png"));
		(*this->bombsprites_)[OK] = GraphicsDevice.CreateSpriteFromFile(_T("bomb/blue_bomb.png"));
	}

	if (this->addalphabomb_ == nullptr){

		this->addalphabomb_ = GraphicsDevice.CreateSpriteFromFile(_T("bomb/white_bomb.png"));

	}

}

EffectBomb::~EffectBomb(){

	if (this->bombsprites_ != nullptr){

		delete this->bombsprites_;
		this->bombsprites_ = nullptr;

	}
}

void EffectBomb::Update(){

	int maxcount = this->ANIMECOUNT_ * this->ONECELLCOUNT_;

	auto itr = this->bombdatas_.begin();
	//auto e_itr = this->bombdatas_.end();

	while (itr != this->bombdatas_.end()){

		itr->nowcount++;

		if (itr->nowcount >= maxcount ){

			itr = this->bombdatas_.erase(itr);
			continue;

		}

		itr++;

	}

}


void EffectBomb::Draw(Vector3 faderpos, Vector2 fadersize){

	auto itr = this->bombdatas_.begin();
	auto e_itr = this->bombdatas_.end();

	int maxcount = this->ANIMECOUNT_ * this->ONECELLCOUNT_;

	Vector3 basepos = faderpos;
	basepos.y -= this->CELLSIZE_.y / 2.0f;
	basepos.x -= (this->CELLSIZE_.x - fadersize.x)  / 2.0f;

	Vector3 pos = basepos;
	SPRITE sp;
	Vector2 cellsize = this->CELLSIZE_;
	RectWH userect;
	int animecount;

	SPRITE addsp = this->addalphabomb_;
	float addalpha;

	for (auto bomb : this->bombdatas_){

		pos = basepos;
		pos.y += fadersize.y * bomb.height;
		animecount = bomb.nowcount / this->ONECELLCOUNT_;
		userect = RectWH(animecount * cellsize.x,0,cellsize.x,cellsize.y);
		sp = bomb.sp;

		SpriteBatch.Begin();
		SpriteBatch.Draw(*sp,pos,userect,1.0f,Vector3_Zero,Vector3(cellsize.x / 2.0f,cellsize.y / 2.0f,0.0f),Vector2_One * 3.0f);
		SpriteBatch.End();

		addalpha = (float)bomb.nowcount / (float)maxcount;

		SpriteBatch.Begin();
		GraphicsDevice.SetBlendMode(DXGBLEND_ADD);
		SpriteBatch.Draw(*addsp, pos, userect, addalpha, Vector3_Zero, Vector3(cellsize.x / 2.0f, cellsize.y / 2.0f, 0.0f), Vector2_One * 3.0f);
		SpriteBatch.End();
		GraphicsDevice.SetBlendMode(DXGBLEND_NORMAL);
	}

}

void EffectBomb::SetBomb(ABSTRUCT_NOTE* noteptr, JUDGELIST judge, float height){

	if (judge == MISSTIME || judge == OUCH || judge == NONE) return;

	auto itr = this->bombdatas_.begin();
	auto e_itr = this->bombdatas_.end();

	while (itr != e_itr){

		if (itr->noteptr == noteptr){

			this->BombReset((*itr), judge, height);
			return;

		}

		itr++;
	}

	//ここまで来たときは新しいノートの申請になる
	SPRITE sp = (*this->bombsprites_)[judge];

	this->bombdatas_.push_back(BOMBNOTICE(noteptr,sp,height));

}

void EffectBomb::BombReset(BOMBNOTICE& resetdata, JUDGELIST judge, float height){

	resetdata.sp = (*this->bombsprites_)[judge];
	resetdata.height = height;
	resetdata.nowcount = 0;

}