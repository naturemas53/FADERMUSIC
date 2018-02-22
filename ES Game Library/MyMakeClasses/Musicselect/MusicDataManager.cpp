#include "MusicDataManager.h"
#include <fstream>

MusicDataManager::MusicDataManager():
MOVETIME_(100){

	this->time_ = MOVETIME_;
	this->state_ = MusicDataManager::STOP;
	this->sound_ = SoundDevice.CreateSoundFromFile(_T("musicselect/sound/songselect.wav"));

}

MusicDataManager::~MusicDataManager(){

	for (auto data : this->musiclist_){

		delete data;

	}

	SoundDevice.ReleaseSound(this->sound_);

}

void MusicDataManager::Update(int elapsedtime){

	if (this->state_ == MusicDataManager::STOP) return;

	this->time_ += elapsedtime;

	if (this->time_ > this->MOVETIME_){

		this->time_ = 0;
		this->state_ = MusicDataManager::STOP;

	}

}

bool MusicDataManager::Initialize(){

	if (!this->FileRead()) return false;

	this->nowselect_ = this->musiclist_.begin();
	Vector2 imagesize = (*this->nowselect_)->GetImageSize();
	this->centerpos_ = Vector3_Zero;
	this->centerpos_.x = (1280.0f - imagesize.x) / 2.0f;
	this->centerpos_.y = (720.0f - imagesize.y) / 2.0f;

	Vector2 hornsize = (*this->nowselect_)->GetHornSize();
	this->hornpos_ = Vector3_Zero;
	this->hornpos_.x = -hornsize.x;
	this->hornpos_.y = hornsize.y;

	return true;

}

void MusicDataManager::MoveIncrement(){

	if (this->state_ != MusicDataManager::STOP) return;

	this->nowselect_++;

	if (this->nowselect_ == this->musiclist_.end()){

		this->nowselect_ = this->musiclist_.begin();
		
	}

	this->time_ = 0;
	this->state_ = MusicDataManager::UP;
	this->sound_->Play();

}

void MusicDataManager::MoveDecrement(){

	if (this->state_ != MusicDataManager::STOP) return;

	if (this->nowselect_ == this->musiclist_.begin()){

		this->nowselect_ = this->musiclist_.end();

	}

	this->nowselect_--;

	this->time_ = 0;
	this->state_ = MusicDataManager::DOWN;
	this->sound_->Play();

}

void MusicDataManager::Draw(){

	Vector3 pos = this->centerpos_;

	if (this->state_ != MusicDataManager::STOP){

		Vector3 movepos = this->hornpos_;

		switch (this->state_){
		case MusicDataManager::UP: movepos *= -1.0f; break;
		case MusicDataManager::DOWN: break;
		default: break;
		}

		float timerate = (float) this->time_ / (float)this->MOVETIME_;
		movepos *= timerate;

		pos += movepos;

	}


	Vector3 hornpos = this->hornpos_;

	pos -= hornpos * 2.0f;

	int selectnumber = 2;
	switch (this->state_){
	case MusicDataManager::UP: selectnumber++; break;
	case MusicDataManager::DOWN: selectnumber--; break;
	default: break;
	}

	M_ITR itr = this->nowselect_;
	this->CalcItr(-selectnumber, itr);

	for (int i = 0; i < 5;i++){

		if (itr == this->musiclist_.end()){

			itr = this->musiclist_.begin();

		}

		(*itr)->Draw(pos, (i == selectnumber));
		
		pos += hornpos;
		itr++;
	}

}

void MusicDataManager::CalcItr(int num,M_ITR& itr){

	if (num == 0) return;

	int count = num;
	count = (count < 0) ? count * -1 : count;

	int movement = (num > 0) ? 1 : -1;

	for (int i = 0; i < count; i++){

		if (itr == this->musiclist_.begin() && movement <= -1){
			itr = this->musiclist_.end();
		}

		itr += movement;

		if (itr == this->musiclist_.end() && movement >= 1){
			itr = this->musiclist_.begin();
		}

	}
	
	return;

}

bool MusicDataManager::FileRead(){

	std::ifstream musiclist("musics/musiclist.txt");
	std::string buf;

	if (!musiclist) return false;

	char* name = new char[256];

	int lo = 0;
	int mid = 0;
	int high = 0;

	while (getline(musiclist, buf)){

		memset(name, 0, sizeof(name));
		sscanf(buf.c_str(), "%s %d %d %d", name, &lo, &mid, &high);

		this->musiclist_.push_back(new MusicData(SongData(name, LevelData(lo, mid, high))));

	}

	delete name;

	if (this->musiclist_.size() == 0){
		return false;
	}

	return true;
}