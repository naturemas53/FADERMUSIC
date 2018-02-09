#pragma once
#include "Context.h"
#include "../../ESGLib.h"

class SelectSceneState{

public:

	~SelectSceneState();

	void Update(float mouseheight, int elapsedtime, Context* context);
	void Draw();

	int Deside(){ return this->desidenum_; }

	void Reset(){ this->desidenum_ = 0; }

protected:

	virtual void AlphaRead() = 0;
	virtual void ClassUpdate(float mouseheight, Context* context) = 0;
	virtual void ClassDraw() = 0;
	
	enum STATE{

		ON,
		OFF

	}state_;

	SelectSceneState();

	int RIGHTTIME_ = 500;
	int time_;

	static SPRITE sprite_;
	SPRITE alpha_;

	int desidenum_;

};