#pragma once
#include "SelectSceneState.h"
#include "MusicDataManager.h"

class SongPlayState : public SelectSceneState{

public:

	static SongPlayState& GetInstance(){

		static SongPlayState instance;

		return instance;

	}

	~SongPlayState() = default;

	void SetDataManager(MusicDataManager* datamanager){ this->datamanager_ = datamanager; }
	void ResetDataManager(){ this->datamanager_ = nullptr; }

private:

	SongPlayState(){
	
		this->AlphaRead();
		this->desideflag_ = false;
		this->datamanager_ = nullptr;

	};

	void AlphaRead();

	void ClassUpdate(float mouseheight, Context* context);
	void ClassDraw();

	bool desideflag_;

	MusicDataManager* datamanager_;

};

#define PLAYSTATE SongPlayState::GetInstance()