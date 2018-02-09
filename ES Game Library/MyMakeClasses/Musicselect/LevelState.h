#pragma once
#include "SelectSceneState.h"
#include "Difficulty.h"

class LevelState : public SelectSceneState{

public:

	static LevelState& GetInstance(){

		static LevelState instance;

		return instance;

	}

	~LevelState() = default;

	void SetLevelManager(Difficulty* levelmanager){ this->levelmanager_ = levelmanager; }
	void ResetLevelManager(){ this->levelmanager_ = nullptr; }

private:

	LevelState(){

		this->AlphaRead();
		this->levelmanager_ = nullptr;

	};

	void AlphaRead();

	void ClassUpdate(float mouseheight, Context* context);
	void ClassDraw();

	Difficulty* levelmanager_;

};

#define LEVELSTATE LevelState::GetInstance()