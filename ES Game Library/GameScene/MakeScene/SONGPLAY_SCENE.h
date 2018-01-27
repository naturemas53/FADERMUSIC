#pragma once

#include "../../ESGLib.h"
#include "../GameScene.hpp"
#include <vector>
#include "../../MyMakeClasses/JUDGELIST_ENUM.h"
#include "../../MyMakeClasses/BPM_DATA_STRUCT.h"

class INSTRUMENT;
class UI;

class SONGPLAY_SCENE : public CGameScene {
public:
	SONGPLAY_SCENE() : DefaultFont(GraphicsDevice.CreateDefaultFont())
	{
//		ContentRootDirectory(_T("Content"));
	}

	virtual ~SONGPLAY_SCENE()
	{

		Finalize();

#ifdef _INC_SQUIRREL
		Squirrel.ReleaseAllScripts();
#endif
#ifdef _INC_NUI
		NUI.ReleaseAllKinects();
#endif
#ifdef _INC_LIVE2D
		Live2D.ReleaseAllModels();
#endif
#ifdef _INC_EFFEKSEER
		Effekseer.ReleaseAllEffects();
#endif
#ifdef _INC_DIRECT2D
		Direct2D.ReleaseAllResources();
#endif
		MediaManager.ReleaseAllMedia();

		SoundDevice.ReleaseAllMusics();
		SoundDevice.ReleaseAllSounds();

		GraphicsDevice.ReleaseAllRenderTargets();
		GraphicsDevice.ReleaseAllStateBlocks();
		GraphicsDevice.ReleaseAllFonts();
		GraphicsDevice.ReleaseAllSprites();
		GraphicsDevice.ReleaseAllAnimationModels();
		GraphicsDevice.ReleaseAllModels();
		GraphicsDevice.ReleaseAllVertexBuffers();
		GraphicsDevice.ReleaseAllEffects();

	}

public:
	virtual bool Initialize();

	virtual int  Update();
	virtual void Draw();

private:
	void Finalize();
	FONT DefaultFont;

private:
	// ïœêîêÈåæ
	INSTRUMENT* instrument_;
	UI* ui_;

	MEDIA movie_;

	int nowtime_;
	int songlength_;

	int score_;
	float life_;
	int accuracy_;
	int maxcombo_;

	int prevtime_;
	float animation_rate_;
	int elapsedtime;
	
	int bpm_;
	int quater_rhythm_;
	int quaver_rhythm_;

	std::vector<BPM_DATA> bpmlist_;

	//Ç∆ÇËÇ†Ç¶Ç∏Ç≈Å´
	bool start_;

	SOUND bgm_;

	// ä÷êîêÈåæ
	long GetElapsedCount(int elapsedtime);
	void ToUITellValue();

};
