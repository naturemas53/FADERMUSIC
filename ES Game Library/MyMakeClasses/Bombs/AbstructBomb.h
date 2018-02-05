#pragma once
#include "../../ESGLib.h"

class AbstructBomb{

public:

	virtual ~AbstructBomb() = default;

	//FX‚ ‚Á‚Ä‰Šú‰»‚Í”h¶æ‚ÅŽÀ‘•

	virtual int Update(int elapsedtime) = 0;
	virtual void Draw() = 0;

	void SetUseFlag(bool flag){ this->useflag_ = flag; }

	bool IsUse(){ return this->useflag_; }

protected:

	AbstructBomb(int animetime,int holizoncell,int maxcell,Vector2 cellsize):
		ANIMETIME_(animetime),
		HOLIZONCELL_(holizoncell),
		MAXCELL_(maxcell),
		CELLSIZE_(cellsize){
	
		this->time_ = 0;
		this->useflag_ = true;
	
	}

	const int ANIMETIME_;
	const int HOLIZONCELL_;
	const int MAXCELL_;
	const Vector2 CELLSIZE_;

	int time_;

	Vector3 pos_;

	bool useflag_;

};