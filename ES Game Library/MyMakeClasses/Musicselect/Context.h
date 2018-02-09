#pragma once

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
	
	};

	int IsDeside();

private:

	SelectSceneState* state_;

};