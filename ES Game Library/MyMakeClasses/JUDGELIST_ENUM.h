#pragma once

enum JUDGELIST{

	MISSTIME = 300,
	OK = 200,
	GREAT = 100,
	UNBELIEVABLE = 60,
	OUCH = 1,
	NONE = 0

};

struct JUDGECOUNT{

	int misstime;
	int ok;
	int great;
	int unbelievable;

	JUDGECOUNT(){

		this->misstime = 0;
		this->ok = 0;
		this->great = 0;
		this->unbelievable = 0;

	}

	JUDGECOUNT operator += (JUDGECOUNT opponentstructure){

		this->unbelievable = this->unbelievable + opponentstructure.unbelievable;
		this->ok = this->ok + opponentstructure.ok;
		this->great = this->great + opponentstructure.great;
		this->misstime = this->misstime + opponentstructure.misstime;

		return (*this);

	}
		
	int GetScore(){

		int score = 0;

		score += this->unbelievable * 10000;
		score += this->great * 5000;
		score += this->ok * 100;

		return score;

	}

	int GetAccuracy(){

		int accuracy = 0;

		accuracy += this->unbelievable * 100;
		accuracy += this->great * 50;
		accuracy += this->ok * 1;

		return accuracy;

	}

	float GetLifePersent(){

		float life = 0.0f;

		life += this->unbelievable * 0.05f;
		life += this->great * 0.01f;
		life += this->ok * 0.005f;
		life += this->misstime * -0.05f;

		return life;


	}

};

