#pragma once
#include "../../ESGLib.h"
#include <random>

class AbstructScoreDisplay{

public:

	virtual ~AbstructScoreDisplay() = default;

	virtual void Update(){

		this->randomnum_ = this->random_();

		if (this->randomnum_ < 0) this->randomnum_ *= -1;
		this->randomnum_ %= 100000000;

	};
	virtual void Draw() = 0;

	void SetScoreShowFlag(bool flag){ this->scoreshowflag_ = flag; }
	bool GetScoreShowFlag(){ return this->scoreshowflag_; }

protected:

	UINT GetRandom(){

		return this->random_();

	}

	AbstructScoreDisplay(Vector3 pos):
	POS_(pos){
	
		this->scoreshowflag_ = false;

		std::random_device seed;
		this->random_ = std::mt19937(seed());
	
	};

	const Vector3 POS_;
	int randomnum_;
	bool scoreshowflag_;
	
	std::mt19937 random_;

};