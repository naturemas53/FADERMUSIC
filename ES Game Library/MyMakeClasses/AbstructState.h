#pragma once

class AbstructState{

public:

	virtual ~AbstructState() = default;

	virtual AbstructState* Update() = 0;
	virtual void Draw() = 0;

	int NextScene(){ return this->nextscene_; }

protected:

	AbstructState():
	nextscene_(0)
	{};

	int nextscene_;


};