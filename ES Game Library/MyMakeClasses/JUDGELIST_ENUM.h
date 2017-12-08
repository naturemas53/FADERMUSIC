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

	unsigned misstime;
	unsigned ok;
	unsigned great;
	unsigned unbelievable;
	unsigned ouch;
};