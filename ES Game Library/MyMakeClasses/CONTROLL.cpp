#include "CONTROLL.h"

void CONTROLL::Update(){

	key_buffer_ = Keyboard->GetBuffer();

}

bool CONTROLL::BufferIsPress(Keys key){

	return key_buffer_.IsPressed(key);

}

bool CONTROLL::StateIsDown(Keys key){

	KeyboardState key_state = Keyboard->GetState();

	return key_state.IsKeyDown(key);

}