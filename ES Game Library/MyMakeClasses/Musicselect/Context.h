#pragma once
#include "../../ESGLib.h"

class SelectSceneState;

class MusicDataManager;
class SelectHighSpeed;
class Difficulty;

class Context{

public:

	Context(MusicDataManager* datamanagerptr, SelectHighSpeed* highspeedptr, Difficulty* levelmanager);
	~Context();

	void Update(float mouseheight,int elapsedtime);
	void Draw();

	void SetState(SelectSceneState* state){
	
		this->state_ = state;
		this->sound_->Play();
	
	};

	int IsDeside();

private:

	SelectSceneState* state_;
	SOUND sound_;

};