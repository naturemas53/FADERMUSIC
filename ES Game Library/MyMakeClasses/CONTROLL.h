#pragma once
#include <vector>
#include "../ESGLib.h"

class CONTROLL
{
public:
	
	static CONTROLL&GetInstance(){
	
		static CONTROLL controll;

		return controll;

	}

	~CONTROLL() = default;

	void Update();

	bool BufferIsPress(Keys key);
	bool StateIsDown(Keys key);

private:
	CONTROLL() = default;

	KeyboardBuffer key_buffer_;
	

};

