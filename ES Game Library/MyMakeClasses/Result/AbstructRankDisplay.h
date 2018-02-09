#pragma once
#include "../../ESGLib.h"
#include <map>

class AbstructRankDisplay{

public:

	virtual ~AbstructRankDisplay() = default;

	virtual int Update(int elapsedtime) = 0;
	virtual void Draw() = 0;
	virtual void Skip(){
	
		this->state_ = AbstructRankDisplay::STOP;
	
	};

	void Start(){

		this->state_ = AbstructRankDisplay::EFFECT;

	};

protected:

	enum STATE{

		WAIT,
		EFFECT,
		STOP

	}state_;

	AbstructRankDisplay(Vector2 size, Vector3 pos = Vector3(900.0f, 360.0f, 0.0f)) :
	POS_(pos),
	SIZE_(size){
	
		this->state_ = AbstructRankDisplay::WAIT;
	
	}

	const Vector3 POS_;
	const Vector2 SIZE_;

	SPRITE ranksprite_;

};