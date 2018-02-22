#pragma once

#include "../GameScene.hpp"
#include "../../ESGLib.h"
#include "../../MyMakeClasses/JUDGELIST_ENUM.h"
#include "../../MyMakeClasses/FadeDisplay.h"
#include "../../MyMakeClasses/Result/ScoresManager.h"


class RESULT_SCENE : public CGameScene {
public:
	RESULT_SCENE()
	{
//		ContentRootDirectory(_T("Content"));
	}

	virtual ~RESULT_SCENE()
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

private:
	void Finalize();

private:

	enum STATE{

		FADEIN,
		DISPLAYNOW,
		PUSHWAIT,
		FADEOUT

	};

	// 変数宣言

	bool clearflag_;

	FadeDisplay fade_;
	JUDGECOUNT scorejudge_;
	JUDGECOUNT accuracyjudge_;

	int score_;
	int accuracy_;
	int maxcombo_;

	RESULT_SCENE::STATE state_;

	ScoresManager* scoremanager_;

	MEDIA movie_;

	SOUND bgm_;

	// 関数プロトタイプ

	bool IsPush();

};
