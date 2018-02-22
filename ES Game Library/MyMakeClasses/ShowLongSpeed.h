#pragma once
#include "../ESGLib.h"
#include "LONGPOINT_STRUCT.h"
#include <vector>

class ShowLongSpeed{

public:

	ShowLongSpeed();
	~ShowLongSpeed();

	void Update(std::vector<LONG_POINT>& points);
	RENDERTARGET GetSprite(SPRITE trianglesp,int nowtime, std::vector<LONG_POINT>& points);
	void ReleaseSprite(){

		if (ShowLongSpeed::screen_ != nullptr){
			GraphicsDevice.ReleaseRenderTarget(ShowLongSpeed::screen_);
			ShowLongSpeed::screen_ = nullptr;

		}

	}

private:

	static RENDERTARGET screen_;
	static SPRITE arrowsp_;

	const int INSTANCETIME_;

	int total_elapsedtime_;

};