#pragma once
#include "../../ESGLib.h"
#include "LevelEnum.h"
#include "SongData.h"
#include <vector>

class MusicData{

public:

	MusicData(SongData data);
	~MusicData();

	void Draw(Vector3 basepos, bool ismain = false);

	int GetLevel(LEVEL level){ return this->data_.level[level]; }
	Vector2 GetImageSize(){ return this->IMAGESIZE_; }
	Vector2 GetHornSize(){ return this->HORNSIZE_; }
	SongData& GetSongData(){ return this->data_; }

private:

	void DataDraw(Vector3 basepos,Color color);

	static SPRITE backsprite_;
	static std::map<LEVEL,SPRITE>* levelsprites_;

	const Vector2 IMAGESIZE_;
	const Vector2 HORNSIZE_;
	const float INNER_X_;

	SongData data_;

};