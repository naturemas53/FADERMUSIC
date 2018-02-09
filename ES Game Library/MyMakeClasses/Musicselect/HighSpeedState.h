#pragma once
#include "SelectSceneState.h"
#include "SelectHighSpeed.h"

class HighSpeedState : public SelectSceneState{

public:

	static HighSpeedState& GetInstance(){

		static HighSpeedState instance;

		return instance;

	}

	~HighSpeedState() = default;

	void SetHighSpeedPtr(SelectHighSpeed* highspeed){ this->highspeed_ = highspeed; }
	void ResetHighSpeedptr(){ this->highspeed_ = nullptr; }

private:

	HighSpeedState(){

		this->highspeed_ = nullptr;
		this->AlphaRead();

	};

	void AlphaRead();

	void ClassUpdate(float mouseheight, Context* context);
	void ClassDraw();

	SelectHighSpeed* highspeed_;

};

#define HIGHSPEEDSTATE HighSpeedState::GetInstance()