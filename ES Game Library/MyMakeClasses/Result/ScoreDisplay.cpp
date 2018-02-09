#include "ScoreDisplay.h"
#include "../ImageFont.h"

ScoreDisplay::ScoreDisplay(Vector3 pos, std::string name, int score) : AbstructScoreDisplay(pos)
{

	this->name_ = name;
	this->score_ = score;

}

ScoreDisplay::~ScoreDisplay(){



}

void ScoreDisplay::Draw(){

	Vector3 pos = this->POS_;

	Vector2 cellsize = IMAGEFONT.GetCellSize();
	Vector2 smollcellsize = cellsize / 2.0f;
	Vector2 drawsize;

	drawsize = IMAGEFONT.GetDrawSize(smollcellsize,this->name_.c_str());

	IMAGEFONT.DirectDrawImageString(pos, smollcellsize, Color(255, 255, 255), this->name_.c_str());

	int shownum = (this->scoreshowflag_) ? this->score_ : this->randomnum_;

	pos.y += drawsize.y / 2.0f;

	IMAGEFONT.DirectDrawImageString(pos, cellsize, Color(255, 255, 255), "%8d", shownum);

}