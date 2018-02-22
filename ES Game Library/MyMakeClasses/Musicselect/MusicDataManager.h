#pragma once
#include "MusicData.h"

typedef std::vector<MusicData*>::iterator M_ITR;

class MusicDataManager{

public:

	MusicDataManager();
	~MusicDataManager();

	bool Initialize();

	void Update(int elapsedtime);
	void Draw();

	void MoveIncrement();
	void MoveDecrement();

	SongData& GetSelectData(){
	
		return (*this->nowselect_)->GetSongData();
	
	};

private:

	enum STATE{

		UP,
		DOWN,
		STOP

	}state_;

	void CalcItr(int num,M_ITR& itr);
	bool FileRead();

	const int MOVETIME_;

	int time_;
	Vector3 centerpos_;
	Vector3 hornpos_;

	std::vector<MusicData*> musiclist_;

	M_ITR nowselect_;

	SOUND sound_;

};