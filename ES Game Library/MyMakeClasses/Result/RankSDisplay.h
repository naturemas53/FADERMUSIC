#pragma once
#include "AbstructRankDisplay.h"
#include <vector>

class RankSDisPlay : public AbstructRankDisplay{

public:

	RankSDisPlay();
	~RankSDisPlay();

	virtual int Update(int elapsedtime);
	virtual void Draw();
	virtual void Skip();

private:

	struct ScaleData{

		int time_;
		float targetscale_;


		ScaleData(){

			this->time_ = 0;
			this->targetscale_ = 0.0f;

		}

		ScaleData(int time, float scale){

			this->time_ = time;
			this->targetscale_ = scale;

		}

		ScaleData& operator= (const ScaleData& data){

			this->time_ = data.time_;
			this->targetscale_ = data.targetscale_;

			return *this;

		}

	};

	float scale_;
	int nowtime_;

	std::vector<ScaleData> datas_;
	std::vector<ScaleData>::iterator nowdata_;

};