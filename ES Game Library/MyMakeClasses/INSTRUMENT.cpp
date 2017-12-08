#include "INSTRUMENT.h"
#include "FADER.h"
#include "SINGLENOTE.h"
#include "LONGNOTE.h"
#include "CONTROLL.h"


INSTRUMENT::INSTRUMENT(LONG max_mouse_y) : MAX_MOUSE_Y_(max_mouse_y)
{

	mouse_y_ = 0;

	faders_.push_back(new FADER(Vector3(1280.0f / 2.0f +12.0f+ 10.0f, 120.0f + 10.0f, 0.0f), Keys_S));
	faders_.push_back(new FADER(Vector3(1280.0f / 2.0f + 12.0f + 10.0f + 160.0f, 120.0f + 10.0f, 0.0f), Keys_D));
	faders_.push_back(new FADER(Vector3(1280.0f / 2.0f + 12.0f + 10.0f + 320.0f, 120.0f + 10.0f, 0.0f), Keys_F));
	
	SetNote();

	(*(notes_.begin())) -> RightUp();

	range_hours_show = 1000;
	

}


INSTRUMENT::~INSTRUMENT()
{
	for (auto f_itr : faders_) delete f_itr;
	for (auto itr : notes_) delete itr;

}

void INSTRUMENT::Update(unsigned nowtime, unsigned elapsedtime_){

	RightUp(nowtime);


	MouseState mouse = Mouse->GetState();

	mouse_y_ += (LONG)((float)mouse.Y * 3.0f);

	if (mouse_y_ < 0){

		mouse_y_ = 0;

	}

	if (mouse_y_ > MAX_MOUSE_Y_){

		mouse_y_ = MAX_MOUSE_Y_;

	}

	button_height_ = (float)mouse_y_ / (float)MAX_MOUSE_Y_;

	if (CONTROLL::GetInstance().StateIsDown(Keys_Up)){

		if (range_hours_show >= 300) range_hours_show -= 30;

	}

	if (CONTROLL::GetInstance().StateIsDown(Keys_Down)){

		range_hours_show += 30;

	}

	for (auto f_itr : faders_)f_itr->Update(nowtime, elapsedtime_, button_height_);

}

void INSTRUMENT::Draw(unsigned nowtime, float animation_rate){

	for (auto f_itr : faders_) f_itr->Draw(button_height_, animation_rate, nowtime,range_hours_show);

}

void INSTRUMENT::RightUp(unsigned nowtime){

	auto itr = notes_.begin();
	itr++;

	int rightupnum = 0;

	while (itr != notes_.end()){

		if (!(*itr)->isRightUp()){

			(*itr)->RightUp();

		}

		if ((*itr)->GetTiming() != (*(itr - 1))->GetTiming() &&  (*itr)->GetTiming() > nowtime ){

			rightupnum++;

		}

		if (rightupnum >= 3) break;

		itr++;

	}

}

void INSTRUMENT::SetBPM(unsigned bpm, unsigned quater_rhythm){

	this->songbpm_ = bpm;
	this->quater_rhythm_ = quater_rhythm;

	for (auto fader : faders_) fader->SetBPM(bpm,quater_rhythm);

}

void INSTRUMENT::SetNote(){


	SINGLENOTE* newsingle;
	LONGNOTE* newlong;

	newsingle = new SINGLENOTE(8535, 0.5f, Color_Red);
	notes_.push_back(newsingle);
	faders_[0]->InNote(newsingle);

	newsingle = new SINGLENOTE(9652, 0.5f, Color_Green);
	notes_.push_back(newsingle);
	faders_[0]->InNote(newsingle);


	newsingle = new SINGLENOTE(9968, 0.5f, Color_Blue);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	//-------------------------

	newsingle = new SINGLENOTE(10285, 0.5f, Color_Red);
	notes_.push_back(newsingle);
	faders_[0]->InNote(newsingle);


	newsingle = new SINGLENOTE(11368, 0.5f, Color_Green);
	notes_.push_back(newsingle);
	faders_[0]->InNote(newsingle);


	newsingle = new SINGLENOTE(11668, 0.5f, Color_Blue);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	//-------------------------

	newsingle = new SINGLENOTE(12050, 0.45f, Color_Red);
	notes_.push_back(newsingle);
	faders_[0]->InNote(newsingle);


	newsingle = new SINGLENOTE(12368, 0.45f, Color_Green);
	notes_.push_back(newsingle);
	faders_[1]->InNote(newsingle);


	newsingle = new SINGLENOTE(12685, 0.45f, Color_Blue);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);


	newsingle = new SINGLENOTE(13184, 0.45f, Color_Red);
	notes_.push_back(newsingle);
	faders_[1]->InNote(newsingle);

	newsingle = new SINGLENOTE(13483, 0.45f, Color_Green);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	//-------------------------

	newsingle = new SINGLENOTE(13850, 0.5f, Color_Blue);
	notes_.push_back(newsingle);
	faders_[0]->InNote(newsingle);

	newsingle = new SINGLENOTE(14167, 0.5f, Color_Red);
	notes_.push_back(newsingle);
	faders_[1]->InNote(newsingle);

	newsingle = new SINGLENOTE(14467, 0.5f, Color_Green);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	newsingle = new SINGLENOTE(14883, 0.5f, Color_Blue);
	notes_.push_back(newsingle);
	faders_[1]->InNote(newsingle);

	newsingle = new SINGLENOTE(15200, 0.5f, Color_Red);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	//-------------------------

	newsingle = new SINGLENOTE(15636, 0.9f, Color_Green);
	notes_.push_back(newsingle);
	faders_[0]->InNote(newsingle);

	newsingle = new SINGLENOTE(15949, 0.88f, Color_Blue);
	notes_.push_back(newsingle);
	faders_[1]->InNote(newsingle);

	newsingle = new SINGLENOTE(16265, 0.86f, Color_Red);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	newsingle = new SINGLENOTE(16714, 0.84f, Color_Green);
	notes_.push_back(newsingle);
	faders_[0]->InNote(newsingle);

	newsingle = new SINGLENOTE(17008, 0.82f, Color_Blue);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	//

	newsingle = new SINGLENOTE(17357, 0.8f, Color_Red);
	notes_.push_back(newsingle);
	faders_[0]->InNote(newsingle);

	newsingle = new SINGLENOTE(17674, 0.78f, Color_Green);
	notes_.push_back(newsingle);
	faders_[1]->InNote(newsingle);

	newsingle = new SINGLENOTE(18007, 0.76f, Color_Blue);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	newsingle = new SINGLENOTE(18441, 0.74f, Color_Red);
	notes_.push_back(newsingle);
	faders_[1]->InNote(newsingle);

	newsingle = new SINGLENOTE(18791, 0.72f, Color_Green);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	//

	newsingle = new SINGLENOTE(19139, 0.7f, Color_Blue);
	notes_.push_back(newsingle);
	faders_[0]->InNote(newsingle);

	newsingle = new SINGLENOTE(19454, 0.68f, Color_Red);
	notes_.push_back(newsingle);
	faders_[1]->InNote(newsingle);

	newsingle = new SINGLENOTE(19769, 0.66f, Color_Green);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	newsingle = new SINGLENOTE(20202, 0.64f, Color_Blue);
	notes_.push_back(newsingle);
	faders_[0]->InNote(newsingle);

	newsingle = new SINGLENOTE(20419, 0.62f, Color_Red);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	//

	newsingle = new SINGLENOTE(20869, 0.6f, Color_Green);
	notes_.push_back(newsingle);
	faders_[0]->InNote(newsingle);

	newsingle = new SINGLENOTE(21185, 0.58f, Color_Blue);
	notes_.push_back(newsingle);
	faders_[1]->InNote(newsingle);

	newsingle = new SINGLENOTE(21502, 0.56f, Color_Red);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	newsingle = new SINGLENOTE(21935, 0.54f, Color_Green);
	notes_.push_back(newsingle);
	faders_[1]->InNote(newsingle);

	newsingle = new SINGLENOTE(22285, 0.52f, Color_Blue);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	//

	newsingle = new SINGLENOTE(22635, 0.5f, Color_Red);
	notes_.push_back(newsingle);
	faders_[0]->InNote(newsingle);

	newsingle = new SINGLENOTE(22969, 0.48f, Color_Green);
	notes_.push_back(newsingle);
	faders_[1]->InNote(newsingle);

	newsingle = new SINGLENOTE(23297, 0.46f, Color_Blue);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	newsingle = new SINGLENOTE(23710, 0.44f, Color_Red);
	notes_.push_back(newsingle);
	faders_[0]->InNote(newsingle);

	newsingle = new SINGLENOTE(23927, 0.42f, Color_Green);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	//

	newsingle = new SINGLENOTE(24377, 0.4f, Color_Blue);
	notes_.push_back(newsingle);
	faders_[0]->InNote(newsingle);

	newsingle = new SINGLENOTE(24694, 0.38f, Color_Red);
	notes_.push_back(newsingle);
	faders_[1]->InNote(newsingle);

	newsingle = new SINGLENOTE(24994, 0.36f, Color_Green);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	newsingle = new SINGLENOTE(25410, 0.34f, Color_Blue);
	notes_.push_back(newsingle);
	faders_[1]->InNote(newsingle);

	newsingle = new SINGLENOTE(25777, 0.32f, Color_Red);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	//

	newsingle = new SINGLENOTE(26127, 0.3f, Color_Green);
	notes_.push_back(newsingle);
	faders_[0]->InNote(newsingle);

	newsingle = new SINGLENOTE(26459, 0.28f, Color_Blue);
	notes_.push_back(newsingle);
	faders_[1]->InNote(newsingle);

	newsingle = new SINGLENOTE(26791, 0.26f, Color_Red);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	newsingle = new SINGLENOTE(27224, 0.24f, Color_Green);
	notes_.push_back(newsingle);
	faders_[0]->InNote(newsingle);

	newsingle = new SINGLENOTE(27457, 0.22f, Color_Blue);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	//

	newsingle = new SINGLENOTE(27889, 0.2f, Color_Red);
	notes_.push_back(newsingle);
	faders_[0]->InNote(newsingle);

	newsingle = new SINGLENOTE(28222, 0.18f, Color_Green);
	notes_.push_back(newsingle);
	faders_[1]->InNote(newsingle);

	newsingle = new SINGLENOTE(28555, 0.16f, Color_Blue);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	newsingle = new SINGLENOTE(28988, 0.14f, Color_Red);
	notes_.push_back(newsingle);
	faders_[1]->InNote(newsingle);

	newsingle = new SINGLENOTE(29338, 0.12f, Color_Green);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	//-------------------------

	newlong = new LONGNOTE(29687, 0.5f, Color_Blue);
	newlong->AddPoint(30318,0.3f);
	notes_.push_back(newlong);
	faders_[1]->InNote(newlong);

	newsingle = new SINGLENOTE(30784, 0.3f, Color_Red);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	newsingle = new SINGLENOTE(31017, 0.3f, Color_Green);
	notes_.push_back(newsingle);
	faders_[0]->InNote(newsingle);

	//

	newlong = new LONGNOTE(31450, 0.45f, Color_Blue);
	newlong->AddPoint(32101, 0.25f);
	notes_.push_back(newlong);
	faders_[0]->InNote(newlong);

	newsingle = new SINGLENOTE(32551, 0.25f, Color_Red);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	newsingle = new SINGLENOTE(32767, 0.25f, Color_Green);
	notes_.push_back(newsingle);
	faders_[1]->InNote(newsingle);

	//

	newlong = new LONGNOTE(33184, 0.4f, Color_Blue);
	newlong->AddPoint(33850, 0.2f);
	notes_.push_back(newlong);
	faders_[1]->InNote(newlong);

	newsingle = new SINGLENOTE(34297, 0.2f, Color_Red);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	newsingle = new SINGLENOTE(34514, 0.2f, Color_Green);
	notes_.push_back(newsingle);
	faders_[0]->InNote(newsingle);

	//

	//newsingle = new SINGLENOTE(48614, 0.1f, Color_Red);
	//notes_.push_back(newsingle);
	//faders_[0]->InNote(newsingle);

	newsingle = new SINGLENOTE(49063, 0.1f, Color_Blue);
	notes_.push_back(newsingle);
	faders_[0]->InNote(newsingle);

	newsingle = new SINGLENOTE(49438, 0.1f, Color_Red);
	notes_.push_back(newsingle);
	faders_[1]->InNote(newsingle);

	newsingle = new SINGLENOTE(49752, 0.1f, Color_Green);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	newsingle = new SINGLENOTE(49985, 0.2f, Color_Blue);
	notes_.push_back(newsingle);
	faders_[0]->InNote(newsingle);

	newsingle = new SINGLENOTE(49985, 0.2f, Color_Blue);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	newsingle = new SINGLENOTE(50401, 0.15f, Color_Red);
	notes_.push_back(newsingle);
	faders_[0]->InNote(newsingle);

	newsingle = new SINGLENOTE(50401, 0.15f, Color_Red);
	notes_.push_back(newsingle);
	faders_[1]->InNote(newsingle);

	newsingle = new SINGLENOTE(50401, 0.15f, Color_Red);
	notes_.push_back(newsingle);
	faders_[2]->InNote(newsingle);

	//

	newlong = new LONGNOTE(50850, 0.0f, Color_Green);
	newlong->AddPoint(52648,1.0f);
	notes_.push_back(newlong);
	faders_[1]->InNote(newlong);

	newlong = new LONGNOTE(58000, 0.7f, Color_Blue);
	newlong->AddPoint(59836, 0.4f);
	newlong->AddPoint(61549, 0.4f);
	newlong->AddPoint(63314, 0.3f);
	newlong->AddPoint(65000, 0.7f);
	notes_.push_back(newlong);
	faders_[0]->InNote(newlong);


}