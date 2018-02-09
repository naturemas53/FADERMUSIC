#pragma once
#include "LevelData.h"
#include <string>

struct SongData{

	std::string songname;
	LevelData level;

	SongData(){

		this->songname = "UNKNOWN";
		this->level = LevelData(0,0,0);

	}

	SongData(std::string str,LevelData& level){

		this->songname = str;
		this->level = level;

	}

	SongData& operator=(const SongData& data){

		this->songname = data.songname;
		this->level = data.level;

		return *this;

	}

};