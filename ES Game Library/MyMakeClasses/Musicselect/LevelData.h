#pragma once

struct LevelData
{
	int lo;
	int mid;
	int high;

	LevelData(){

		this->lo = 0;
		this->mid = 0;
		this->high = 0;

	}

	LevelData(int lo,int mid,int high){

		this->lo = lo;
		this->mid = mid;
		this->high = high;

	}


	LevelData& operator=(const LevelData& data){

		this->lo = data.lo;
		this->mid = data.mid;
		this->high = data.high;

		return *this;

	}

	int operator[](int num){

		if (num = 0){

			return this->lo;

		}

		if (num = 1){

			return this->mid;

		}

		if (num = 2){

			return this->high;

		}

	}
};