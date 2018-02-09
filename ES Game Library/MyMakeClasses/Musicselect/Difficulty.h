#pragma once
#include "../../ESGlib.h"
#include "LevelEnum.h"
#include <map>

class Difficulty{

public:

	Difficulty();
	~Difficulty();

	void Draw();
	void SetLevel(LEVEL level){ this->level_ = level; }
	LEVEL GetLevel(){ return this->level_; }

private:

	LEVEL level_;

	std::map<LEVEL,SPRITE> sprite_;

};