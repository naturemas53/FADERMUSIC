#pragma once
#include "../ESGLib.h"
#include <vector>
#include <map>

enum BUTTONTYPE{

	LEFT,
	CENTER,
	RIGHT

};

class CONTROLL
{
public:


	static CONTROLL&GetInstance(){
	
		static CONTROLL controll;

		return controll;

	}

	~CONTROLL() = default;

	void Update();

	bool BufferIsPress(BUTTONTYPE buttontype);
	bool StateIsDown(BUTTONTYPE buttontype);

private:
	CONTROLL(){
	
		keyasign_[LEFT].push_back(Keys_S);
		keyasign_[CENTER].push_back(Keys_D);
		keyasign_[RIGHT].push_back(Keys_F);
	


		padasign_[LEFT].push_back(GamePad_Button1);
		padasign_[CENTER].push_back(GamePad_Button9);
		padasign_[RIGHT].push_back(GamePad_Button10);

		padasign_[LEFT].push_back(GamePad_Button2);
		padasign_[CENTER].push_back(GamePad_Button3);
		padasign_[RIGHT].push_back(GamePad_Button4);

	};

	KeyboardBuffer key_buffer_;
	GamePadBuffer pad_buffer_;

	std::map<BUTTONTYPE, std::vector<Keys> > keyasign_;
	std::map<BUTTONTYPE, std::vector<DWORD> > padasign_;
	

};

