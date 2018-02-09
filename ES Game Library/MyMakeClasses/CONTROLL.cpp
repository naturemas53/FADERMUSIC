#include "CONTROLL.h"

void CONTROLL::Update(){

	key_buffer_ = Keyboard->GetBuffer();
	pad_buffer_ = GamePad(0)->GetBuffer();
}

bool CONTROLL::BufferIsPress(BUTTONTYPE type){

	for (auto button : this->keyasign_[type]){

		if (this->key_buffer_.IsPressed(button)){

			return true;

		}

	}

	for (auto button : this->padasign_[type]){

		if (this->pad_buffer_.IsPressed(button)){

			return true;

		}

	}

	return false;

}

bool CONTROLL::StateIsDown(BUTTONTYPE type){

	KeyboardState key_state = Keyboard->GetState();
	GamePadState pad_state = GamePad(0)->GetState();

	for (auto button : this->keyasign_[type]){

		if (key_state.IsKeyDown(button)){

			return true;

		}

	}

	DWORD number;

	for (auto button : this->padasign_[type]){

		number = button - GamePad_Button1;

		if (pad_state.Buttons[number] != 0){

			return true;

		}

	}

	return false;

}