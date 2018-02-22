#include "Context.h"
#include "LevelState.h"
#include "HighSpeedState.h"
#include "SongPlayState.h"

Context::Context(MusicDataManager* datamanagerptr, SelectHighSpeed* highspeedptr, Difficulty* levelmanager){

	PLAYSTATE.SetDataManager(datamanagerptr);
	HIGHSPEEDSTATE.SetHighSpeedPtr(highspeedptr);
	LEVELSTATE.SetLevelManager(levelmanager);

	PLAYSTATE.Reset();

	this->state_ = &PLAYSTATE;
	this->sound_ = SoundDevice.CreateSoundFromFile(_T("musicselect/sound/statemove.wav"));

}
Context::~Context(){

	PLAYSTATE.ResetDataManager();
	HIGHSPEEDSTATE.ResetHighSpeedptr();
	LEVELSTATE.ResetLevelManager();

	SoundDevice.ReleaseSound(this->sound_);

}

void Context::Update(float mouseheight, int elapsedtime){

	this->state_->Update(mouseheight,elapsedtime,this);

}

void Context::Draw(){

	this->state_->Draw();

}

int Context::IsDeside(){

	return this->state_->Deside();

}