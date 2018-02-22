#pragma once

#include "../GameScene.hpp"
#include "../../ESGLib.h"
#include "../../MyMakeClasses/FadeDisplay.h"

class THANK_SCENE : public CGameScene {
public:
	THANK_SCENE()
	{
//		ContentRootDirectory(_T("Content"));
	}

	virtual ~THANK_SCENE()
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

		//SoundDevice.ReleaseAllMusics();
		//SoundDevice.ReleaseAllSounds();

		//GraphicsDevice.ReleaseAllRenderTargets();
		//GraphicsDevice.ReleaseAllStateBlocks();
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

private:
	void Finalize();

private:
	// 変数宣言

	SPRITE thankyousprite_;
	FadeDisplay fade_;

	int time_;
	bool nextflag_;

	SOUND bgm_;

	// 関数プロトタイプ

	bool IsPush();

};
