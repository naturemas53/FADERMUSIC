#pragma once
#include "../ESGLib.h"
#include "JUDGELIST_ENUM.h"
#include <map>

class ClapSound{

public:

	ClapSound();
	~ClapSound();

	void Play(JUDGELIST judge);

private:

	static std::map<JUDGELIST, SOUND>* clapsounds_;

};