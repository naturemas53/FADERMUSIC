#include "JudgeDisplay.h"
#include "../ImageFont.h"

JudgeDisPlay::JudgeDisPlay(Vector3 pos, std::wstring filename,Vector3 countpos, int count) :
AbstructScoreDisplay(pos),
COUNT_(count),
COUNTPOS_(countpos){

	this->sprite_ = GraphicsDevice.CreateSpriteFromFile(filename.c_str());

}

JudgeDisPlay::~JudgeDisPlay(){

	GraphicsDevice.ReleaseSprite(this->sprite_);

}

void JudgeDisPlay::Draw(){

	int shownum = (this->scoreshowflag_) ? this->COUNT_ : this->randomnum_ % 10000;
	shownum = shownum % 10000;
	Vector2 cellsize = IMAGEFONT.GetCellSize();
	//49はスプライトの大きさ
	float scalerate = 49.0f / cellsize.x;
	cellsize *= scalerate;

	IMAGEFONT.DirectDrawImageString(this->COUNTPOS_,cellsize,Color(255,255,255),"%4d",shownum);

	SPRITE sp = this->sprite_;

	SpriteBatch.Begin();

	SpriteBatch.Draw(*sp,this->POS_);

	SpriteBatch.End();

}