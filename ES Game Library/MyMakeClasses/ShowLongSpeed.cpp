#include "ShowLongSpeed.h"
#include <math.h>

RENDERTARGET ShowLongSpeed::screen_ = nullptr;
SPRITE ShowLongSpeed::arrowsp_ = nullptr;

ShowLongSpeed::ShowLongSpeed():
INSTANCETIME_(1000){

	if (ShowLongSpeed::screen_ == nullptr){

		ShowLongSpeed::screen_ = GraphicsDevice.CreateRenderTarget(210,536,PixelFormat_RGBA8888,DepthFormat_Unknown);

	}
	if (ShowLongSpeed::arrowsp_ == nullptr){

		ShowLongSpeed::arrowsp_ = GraphicsDevice.CreateSpriteFromFile(_T("triangle/arrow.png"));

	}

	this->total_elapsedtime_ = 0;

}

ShowLongSpeed::~ShowLongSpeed(){

	if (ShowLongSpeed::screen_ != nullptr){
		GraphicsDevice.ReleaseRenderTarget(ShowLongSpeed::screen_);
		ShowLongSpeed::screen_ = nullptr;

	}
	if (ShowLongSpeed::arrowsp_ != nullptr){
		GraphicsDevice.ReleaseSprite(ShowLongSpeed::arrowsp_);
		ShowLongSpeed::arrowsp_ = nullptr;
	}

}

void ShowLongSpeed::Update(std::vector<LONG_POINT>& points){

	int elapsedtime = GameTimer.GetElapsedMilliSecond();

	this->total_elapsedtime_ -= elapsedtime;

	if (this->total_elapsedtime_ > this->INSTANCETIME_){

		this->total_elapsedtime_ -= this->INSTANCETIME_;

	}

}

RENDERTARGET ShowLongSpeed::GetSprite(SPRITE trianglesp,int nowtime, std::vector<LONG_POINT>& points){

	int longtime = points.back().timing - points.front().timing;

	GraphicsDevice.SetRenderTarget(ShowLongSpeed::screen_);

	GraphicsDevice.Clear(Color(0.0f,0.0f,0.0f,0.0f));

	SpriteBatch.Begin();

	Vector3 pos = Vector3_Zero;
	SPRITE sp = this->arrowsp_;

	int time = this->total_elapsedtime_;
	float timerate;

	for (; time < longtime + 2000;time += this->INSTANCETIME_){

		timerate = (float)time / (float)longtime;

		SpriteBatch.Draw(*sp, Vector3(0.0f, 536.0f * -timerate, 0.0f));

	}

	sp = trianglesp;

	SpriteBatch.Draw(*sp, Vector3_Zero,Color(255, 255, 255));

	SpriteBatch.End();
	
	GraphicsDevice.SetDefaultRenderTarget();

	return ShowLongSpeed::screen_;

}