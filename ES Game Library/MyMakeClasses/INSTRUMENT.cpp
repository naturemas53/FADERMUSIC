#include "INSTRUMENT.h"
#include "FADER.h"
#include "SINGLENOTE.h"
#include "LONGNOTE.h"
#include "CONTROLL.h"
#include "JUDGELIST_ENUM.h"
#include "BPM_DATA_STRUCT.h"

#include <string>

namespace{

	int MillisecondPerQuaterRhythm(int bpm){

		return (int)(60.0f / (float)bpm * 1 * 1000.0f);

	}

}

INSTRUMENT::INSTRUMENT(LONG max_mouse_y,  std::vector<BPM_DATA>& bpmlist, const char* filename) : MAX_MOUSE_Y_(max_mouse_y)
{

	mouse_y_ = 0;

	faders_.push_back(new FADER(Vector3(1280.0f / 2.0f +12.0f+ 10.0f, 120.0f + 10.0f, 0.0f), Keys_S));
	faders_.push_back(new FADER(Vector3(1280.0f / 2.0f + 12.0f + 10.0f + 160.0f, 120.0f + 10.0f, 0.0f), Keys_D));
	faders_.push_back(new FADER(Vector3(1280.0f / 2.0f + 12.0f + 10.0f + 320.0f, 120.0f + 10.0f, 0.0f), Keys_F));

	this->Setting(filename,bpmlist);

	(*(notes_.begin())) -> RightUp();

	range_hours_show = 1000;

	this->font_ = GraphicsDevice.CreateSpriteFont(_T("Voyager Grotesque Bold"),114);

	this->havecombo_ = 0;
	

}


INSTRUMENT::~INSTRUMENT()
{
	for (auto f_itr : faders_) delete f_itr;
	for (auto itr : notes_) delete itr;

}

void INSTRUMENT::Update(unsigned nowtime, unsigned elapsedtime, long elapsedcount){

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

	for (auto f_itr : faders_)f_itr->Update(nowtime, elapsedtime, button_height_,elapsedcount);

	this->ComboCheck();

}

void INSTRUMENT::Draw(unsigned nowtime, float animation_rate){

	for (auto f_itr : faders_) f_itr->Draw(button_height_, animation_rate, nowtime,range_hours_show);

	if (this->havecombo_ > 0){

		SpriteBatch.DrawString(font_,Vector2(1270.0f,120.0f + 10.0f + 20.0f),Color(0,255,0),
			Vector2_One, Vector3(0.0f, 0.0f, 90.0f), Vector3(1270.0f, 120.0f + 10.0f + 20.0f,0.0f), _T("%dcombo"), this->havecombo_);

	}

}

void INSTRUMENT::ComboCheck(){

	JUDGELIST judge;

	for (auto f_itr = faders_.begin(); f_itr != faders_.end();f_itr++){

		judge = (*f_itr)->GetScoreJudge();

		if (judge != NONE){

			if (judge == MISSTIME || judge == OUCH){

				havecombo_ = 0;
				break;

			}
			else{

				havecombo_++;

			}

		}

	}

}

JUDGECOUNT INSTRUMENT::GetScoreJudge(){

	JUDGECOUNT judge = JUDGECOUNT();

	for (auto itr = faders_.begin(); itr != faders_.end();itr++){

		switch ((*itr)->GetScoreJudge()){

		case UNBELIEVABLE: judge.unbelievable++; break;
		case GREAT: judge.great++; break;
		case OK: judge.ok++; break;
		case OUCH: 
		case MISSTIME: judge.misstime++; break;
		default: break;

		}

	}

	return judge;

}

JUDGECOUNT INSTRUMENT::GetAccuracyJudge(){

	JUDGECOUNT judge = JUDGECOUNT();

	for (auto itr = faders_.begin(); itr != faders_.end(); itr++){

		switch ((*itr)->GetAccuracyJudge()){

		case UNBELIEVABLE: judge.unbelievable++; break;
		case GREAT: judge.great++; break;
		case OK: judge.ok++; break;
		case OUCH:
		case MISSTIME: judge.misstime++; break;
		default: break;

		}

	}

	return judge;

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

	this->range_hours_show = quater_rhythm * 4;

	for (auto fader : faders_) fader->SetBPM(bpm,quater_rhythm);

}

void INSTRUMENT::Setting(const char* filename, std::vector<BPM_DATA>& bpmlist){

	FILE* file;
	
	char buffer[256] = {};
	std::string str;

	file = fopen(filename,"r");

	do{
/*
		if (!std::getline(file, str)){

			::OutputDebugString(_T("\n\n\nBPM‚ðŒ©‚Â‚¯‚ç‚ê‚Ü‚¹‚ñ‚Å‚µ‚½\n\n\n"));

			return;

		}*/

		if (fscanf(file,"%s",buffer) == EOF){

			return;

		}

		str = buffer;


	} while (str != "BPM");

	//std::getline(file, str);
	this->ReadBpm(file, bpmlist);

	do{

		//if (!std::getline(file, str)){

		//	::OutputDebugString(_T("\n\n\nNOTES‚ðŒ©‚Â‚¯‚ç‚ê‚Ü‚¹‚ñ‚Å‚µ‚½\n\n\n"));

		//	return;

		//}


		if (fscanf(file, "%s", buffer) == EOF){

			return;

		}

		str = buffer;

	} while (str != "NOTES");

	this->ReadNote(file, bpmlist);

}

void INSTRUMENT::ReadBpm(FILE* file, std::vector<BPM_DATA>& bpmlist){

	//std::string str;
	//std::string timing;
	//std::string bpm;

	unsigned timing;
	unsigned bpm;

	int i = 0;

	char buffer[256] = {};

	do{

		//if (!std::getline(*file, str)) break;

		//fgets(buffer, sizeof(buffer), file);

		timing = 0;
		bpm = 0;

		fscanf(file, "%u %u", &timing, &bpm);

		if (timing != 0 || bpm != 0){

			/*timing = str.substr(0, 6);
			bpm = str.substr(7, 3);

			bpmlist.push_back(BPM_DATA(std::stoi(timing), std::stoi(bpm)));*/

			bpmlist.push_back(BPM_DATA(timing,bpm));

		}
		else{
			break;
		}

	} while (true);

}

void INSTRUMENT::ReadNote(FILE* file, std::vector<BPM_DATA>& bpmlist){

	int number = 0;
	unsigned timing;
	float height_rate;
	char type;

	LONGNOTE* newlong;
	SINGLENOTE* newsingle;

	int prevtiming = -1;

	int colorstep = 0;
	Color_by_Name color;

	bool nowlong = false;

	char buffer[256] = {};



	long range_count;
	int range_time;
	long firsthave_count;

	do{

		range_count = 0;
		range_time = 0;
		firsthave_count = 1;

		if (fscanf(file, "%d %u %f %c", &number,&timing,&height_rate,&type) != EOF){

			if (nowlong){

				newlong->AddPoint(timing,height_rate);

				if (type == 'E'){
					
					faders_[number]->InNote(newlong);
					notes_.push_back(newlong);
					nowlong = false;

				}

			}
			else{

				if (prevtiming != timing ) colorstep++;

				switch (colorstep % 3)
				{
				case 0: color = Color_Red; break;
				case 1: color = Color_Blue; break;
				case 2: color = Color_Green; break;
				}
				
				this->RangeCalculation(timing, &range_time, &range_count, &firsthave_count, bpmlist);

				if (type == 'S'){

					newsingle = new SINGLENOTE(timing, height_rate, color, range_count, range_time, firsthave_count);
					faders_[number]->InNote(newsingle);
					notes_.push_back(newsingle);

				}
				else{

					newlong = new LONGNOTE(timing, height_rate, color, range_count, range_time, firsthave_count);
					nowlong = true;

				}

				prevtiming = timing;

			}
			

		}
		else{ break; }

	} while (true);

}

void INSTRUMENT::RangeCalculation(unsigned timing, int* range_time, long* range_count, long* firsthave_count, std::vector<BPM_DATA>& bpmlist){

	auto itr = bpmlist.begin();
	auto fitr = bpmlist.end();
	fitr--;

	while (itr != fitr){ 
	
		if ((itr + 1)->timing > timing) break;
		itr++;

	}

	long totalcount = 0;

	*range_count = 1340000;

	int i_timing = (int)timing;

	for ( (*range_time) = 0; totalcount < (*range_count); (*range_time)++){

		if ((i_timing - *range_time) <= 0){

			//(*range_time) += ((*range_count) - totalcount) / itr->bpm;
			(*firsthave_count) += ((*range_count) - totalcount);
			break;

		}

		if ((i_timing - *range_time) < (int)itr->timing && itr != bpmlist.begin()){
			itr--;
		}

		totalcount += itr->bpm;

	}

}

//void INSTRUMENT::SetNote(){
//
//
//	SINGLENOTE* newsingle;
//	LONGNOTE* newlong;
//
//	newsingle = new SINGLENOTE(8535, 0.5f, Color_Red);
//	notes_.push_back(newsingle);
//	faders_[0]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(9652, 0.5f, Color_Green);
//	notes_.push_back(newsingle);
//	faders_[0]->InNote(newsingle);
//
//
//	newsingle = new SINGLENOTE(9968, 0.5f, Color_Blue);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	//-------------------------
//
//	newsingle = new SINGLENOTE(10285, 0.5f, Color_Red);
//	notes_.push_back(newsingle);
//	faders_[0]->InNote(newsingle);
//
//
//	newsingle = new SINGLENOTE(11368, 0.5f, Color_Green);
//	notes_.push_back(newsingle);
//	faders_[0]->InNote(newsingle);
//
//
//	newsingle = new SINGLENOTE(11668, 0.5f, Color_Blue);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	//-------------------------
//
//	newsingle = new SINGLENOTE(12050, 0.45f, Color_Red);
//	notes_.push_back(newsingle);
//	faders_[0]->InNote(newsingle);
//
//
//	newsingle = new SINGLENOTE(12368, 0.45f, Color_Green);
//	notes_.push_back(newsingle);
//	faders_[1]->InNote(newsingle);
//
//
//	newsingle = new SINGLENOTE(12685, 0.45f, Color_Blue);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//
//	newsingle = new SINGLENOTE(13184, 0.45f, Color_Red);
//	notes_.push_back(newsingle);
//	faders_[1]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(13483, 0.45f, Color_Green);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	//-------------------------
//
//	newsingle = new SINGLENOTE(13850, 0.5f, Color_Blue);
//	notes_.push_back(newsingle);
//	faders_[0]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(14167, 0.5f, Color_Red);
//	notes_.push_back(newsingle);
//	faders_[1]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(14467, 0.5f, Color_Green);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(14883, 0.5f, Color_Blue);
//	notes_.push_back(newsingle);
//	faders_[1]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(15200, 0.5f, Color_Red);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	//-------------------------
//
//	newsingle = new SINGLENOTE(15636, 0.9f, Color_Green);
//	notes_.push_back(newsingle);
//	faders_[0]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(15949, 0.88f, Color_Blue);
//	notes_.push_back(newsingle);
//	faders_[1]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(16265, 0.86f, Color_Red);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(16714, 0.84f, Color_Green);
//	notes_.push_back(newsingle);
//	faders_[0]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(17008, 0.82f, Color_Blue);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	//
//
//	newsingle = new SINGLENOTE(17357, 0.8f, Color_Red);
//	notes_.push_back(newsingle);
//	faders_[0]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(17674, 0.78f, Color_Green);
//	notes_.push_back(newsingle);
//	faders_[1]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(18007, 0.76f, Color_Blue);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(18441, 0.74f, Color_Red);
//	notes_.push_back(newsingle);
//	faders_[1]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(18791, 0.72f, Color_Green);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	//
//
//	newsingle = new SINGLENOTE(19139, 0.7f, Color_Blue);
//	notes_.push_back(newsingle);
//	faders_[0]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(19454, 0.68f, Color_Red);
//	notes_.push_back(newsingle);
//	faders_[1]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(19769, 0.66f, Color_Green);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(20202, 0.64f, Color_Blue);
//	notes_.push_back(newsingle);
//	faders_[0]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(20419, 0.62f, Color_Red);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	//
//
//	newsingle = new SINGLENOTE(20869, 0.6f, Color_Green);
//	notes_.push_back(newsingle);
//	faders_[0]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(21185, 0.58f, Color_Blue);
//	notes_.push_back(newsingle);
//	faders_[1]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(21502, 0.56f, Color_Red);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(21935, 0.54f, Color_Green);
//	notes_.push_back(newsingle);
//	faders_[1]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(22285, 0.52f, Color_Blue);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	//
//
//	newsingle = new SINGLENOTE(22635, 0.5f, Color_Red);
//	notes_.push_back(newsingle);
//	faders_[0]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(22969, 0.48f, Color_Green);
//	notes_.push_back(newsingle);
//	faders_[1]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(23297, 0.46f, Color_Blue);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(23710, 0.44f, Color_Red);
//	notes_.push_back(newsingle);
//	faders_[0]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(23927, 0.42f, Color_Green);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	//
//
//	newsingle = new SINGLENOTE(24377, 0.4f, Color_Blue);
//	notes_.push_back(newsingle);
//	faders_[0]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(24694, 0.38f, Color_Red);
//	notes_.push_back(newsingle);
//	faders_[1]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(24994, 0.36f, Color_Green);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(25410, 0.34f, Color_Blue);
//	notes_.push_back(newsingle);
//	faders_[1]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(25777, 0.32f, Color_Red);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	//
//
//	newsingle = new SINGLENOTE(26127, 0.3f, Color_Green);
//	notes_.push_back(newsingle);
//	faders_[0]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(26459, 0.28f, Color_Blue);
//	notes_.push_back(newsingle);
//	faders_[1]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(26791, 0.26f, Color_Red);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(27224, 0.24f, Color_Green);
//	notes_.push_back(newsingle);
//	faders_[0]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(27457, 0.22f, Color_Blue);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	//
//
//	newsingle = new SINGLENOTE(27889, 0.2f, Color_Red);
//	notes_.push_back(newsingle);
//	faders_[0]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(28222, 0.18f, Color_Green);
//	notes_.push_back(newsingle);
//	faders_[1]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(28555, 0.16f, Color_Blue);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(28988, 0.14f, Color_Red);
//	notes_.push_back(newsingle);
//	faders_[1]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(29338, 0.12f, Color_Green);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	//-------------------------
//
//	newlong = new LONGNOTE(29687, 0.5f, Color_Blue);
//	newlong->AddPoint(30318,0.3f);
//	notes_.push_back(newlong);
//	faders_[1]->InNote(newlong);
//
//	newsingle = new SINGLENOTE(30784, 0.3f, Color_Red);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(31017, 0.3f, Color_Green);
//	notes_.push_back(newsingle);
//	faders_[0]->InNote(newsingle);
//
//	//
//
//	newlong = new LONGNOTE(31450, 0.45f, Color_Blue);
//	newlong->AddPoint(32101, 0.25f);
//	notes_.push_back(newlong);
//	faders_[0]->InNote(newlong);
//
//	newsingle = new SINGLENOTE(32551, 0.25f, Color_Red);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(32767, 0.25f, Color_Green);
//	notes_.push_back(newsingle);
//	faders_[1]->InNote(newsingle);
//
//	//
//
//	newlong = new LONGNOTE(33184, 0.4f, Color_Blue);
//	newlong->AddPoint(33850, 0.2f);
//	notes_.push_back(newlong);
//	faders_[1]->InNote(newlong);
//
//	newsingle = new SINGLENOTE(34297, 0.2f, Color_Red);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(34514, 0.2f, Color_Green);
//	notes_.push_back(newsingle);
//	faders_[0]->InNote(newsingle);
//
//	//
//
//	//newsingle = new SINGLENOTE(48614, 0.1f, Color_Red);
//	//notes_.push_back(newsingle);
//	//faders_[0]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(49063, 0.1f, Color_Blue);
//	notes_.push_back(newsingle);
//	faders_[0]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(49438, 0.1f, Color_Red);
//	notes_.push_back(newsingle);
//	faders_[1]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(49752, 0.1f, Color_Green);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(49985, 0.2f, Color_Blue);
//	notes_.push_back(newsingle);
//	faders_[0]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(49985, 0.2f, Color_Blue);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(50401, 0.15f, Color_Red);
//	notes_.push_back(newsingle);
//	faders_[0]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(50401, 0.15f, Color_Red);
//	notes_.push_back(newsingle);
//	faders_[1]->InNote(newsingle);
//
//	newsingle = new SINGLENOTE(50401, 0.15f, Color_Red);
//	notes_.push_back(newsingle);
//	faders_[2]->InNote(newsingle);
//
//	//
//
//	newlong = new LONGNOTE(50850, 0.0f, Color_Green);
//	newlong->AddPoint(52648,1.0f);
//	notes_.push_back(newlong);
//	faders_[1]->InNote(newlong);
//
//	newlong = new LONGNOTE(58000, 0.7f, Color_Blue);
//	newlong->AddPoint(59836, 0.4f);
//	newlong->AddPoint(61549, 0.4f);
//	newlong->AddPoint(63314, 0.3f);
//	newlong->AddPoint(65000, 0.7f);
//	notes_.push_back(newlong);
//	faders_[0]->InNote(newlong);
//
//
//}