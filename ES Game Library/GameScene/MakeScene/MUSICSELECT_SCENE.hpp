#pragma once

#include "../GameScene.hpp"
#include "../../ESGLib.h"
#include "../../MyMakeClasses/FadeDisplay.h"
#include "../../MyMakeClasses/Musicselect/MusicDataManager.h"
#include "../../MyMakeClasses/Musicselect/SelectHighSpeed.h"
#include "../../MyMakeClasses/Musicselect/Context.h"
#include "../../MyMakeClasses/Musicselect/Difficulty.h"
#include <vector>

class MUSICSELECT_SCENE : public CGameScene {
public:
	MUSICSELECT_SCENE()
	{
//		ContentRootDirectory(_T("Content"));
	}

	virtual ~MUSICSELECT_SCENE()
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
		//MediaManager.ReleaseAllMedia();

		SoundDevice.ReleaseAllMusics();
		//SoundDevice.ReleaseAllSounds();

		//GraphicsDevice.ReleaseAllRenderTargets();
		GraphicsDevice.ReleaseAllStateBlocks();
		//GraphicsDevice.ReleaseAllFonts();
		//GraphicsDevice.ReleaseAllSprites();
		GraphicsDevice.ReleaseAllAnimationModels();
		GraphicsDevice.ReleaseAllModels();
		GraphicsDevice.ReleaseAllVertexBuffers();
		GraphicsDevice.ReleaseAllEffects();
	}

	virtual bool Initialize();

	virtual int  Update();
	virtual void Draw();

	void SongDeside();

private:
	void Finalize();

private:
	// 変数宣言
	enum STATE{

		SELECTNOW,
		DESIDE

	}state_;

	FadeDisplay fade_;
	MusicDataManager* datamanager_;
	SelectHighSpeed* highspeed_;
	Difficulty* difficulty_;

	Context* context_;

	SPRITE titlebar_;
	SPRITE stick_;

	int mouse_y_;
	int time_;

	RENDERTARGET screen_;

	MEDIA movie_;

	SOUND bgm_;
	SOUND desidese_;

	// 関数プロトタイプ


};
