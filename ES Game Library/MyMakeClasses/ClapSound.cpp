#include "ClapSound.h"

std::map<JUDGELIST, SOUND>* ClapSound::clapsounds_ = nullptr;

ClapSound::ClapSound(){

	if (this->clapsounds_ == nullptr){

		this->clapsounds_ = new std::map<JUDGELIST, SOUND>;

		(*this->clapsounds_)[UNBELIEVABLE] = SoundDevice.CreateSoundFromFile(_T("clapsounds/unbelievable_sound.wav"));
		(*this->clapsounds_)[GREAT] = SoundDevice.CreateSoundFromFile(_T("clapsounds/great_sound.wav"));
		(*this->clapsounds_)[OK] = SoundDevice.CreateSoundFromFile(_T("clapsounds/ok_sound.wav"));

	}

}

ClapSound::~ClapSound(){

	if (this->clapsounds_ != nullptr){

		for (auto sound : (*this->clapsounds_)){

			SoundDevice.ReleaseSound(sound.second);

		}

		delete this->clapsounds_;
		this->clapsounds_ = nullptr;

	}

}

void ClapSound::Play(JUDGELIST judge){

	if (judge == MISSTIME || judge == OUCH || judge == NONE) return;

	SOUND sound = (*this->clapsounds_)[judge];
	sound->Play();
	
}