#pragma once

struct LONG_POINT{

	int timing;
	float height_rate;

	LONG_POINT(int timing, float height_rate){

		this->timing = timing;
		this->height_rate = height_rate;

	}

	LONG_POINT& operator=(const LONG_POINT& point){

		this->timing = point.timing;
		this->height_rate = point.height_rate;

		return *this;

	}

};