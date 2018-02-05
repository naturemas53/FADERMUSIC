#include "CALIBRATION_SCENE.hpp"
#include "../../StdAfx.h"
#include "../SceneShared.hpp"
#include "../../MyMakeClasses/ImageFont.h"
#include <string>

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load any non-graphic
/// related content.  Calling base.Initialize will enumerate through any components
/// and initialize them as well.
/// </summary>
bool CALIBRATION_SCENE::Initialize()
{
	// TODO: Add your initialization logic here
	InputDevice.CreateMouse();

	font_ = GraphicsDevice.CreateDefaultFont();

	this->title_logo_ = GraphicsDevice.CreateSpriteFromFile(_T("title_logo.png"));

	mouse_top = 0;
	setting_state = CALIBRATIONWAIT;

	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void CALIBRATION_SCENE::Finalize()
{
	// TODO: Add your finalization logic here
	GraphicsDevice.ReleaseSprite(this->title_logo_);
}

/// <summary>
/// Allows the game to run logic such as updating the world,
/// checking for collisions, gathering input, and playing audio.
/// </summary>
/// <returns>
/// Scene continued value.
/// </returns>
int CALIBRATION_SCENE::Update()
{
    // TODO: Add your update logic here

	MouseBuffer mouse_buffer = Mouse->GetBuffer();
	MouseState mouse_state = Mouse->GetState();

	switch (setting_state)
	{

	case CALIBRATION_SCENE::CALIBRATIONWAIT:

		if (fade_.Update()){

			this->setting_state = SETTINGBOTTOM;

		}

		break;

	case CALIBRATION_SCENE::SETTINGBOTTOM:

		if (mouse_buffer.IsPressed(Mouse_Button1)){
			setting_state = SETTINGTOP;
		}

		break;

	case CALIBRATION_SCENE::SETTINGTOP:

		mouse_top += mouse_state.Y;

		if (mouse_buffer.IsPressed(Mouse_Button1)){
			setting_state = READY;
			this->fade_.SetFadeState(FadeDisplay::FADEOUT);
			if (mouse_top < 0) mouse_top *= -1;
		}

		break;

	case CALIBRATION_SCENE::READY:

		if (this->fade_.Update()){

			SceneShared().SetLongIntegerForKey("MOUSE_MAX_Y", mouse_top);
			return GAME_SCENE(new SONGPLAY_SCENE());

		}

		break;

	default:

		break;
	}

	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void CALIBRATION_SCENE::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_Black);

	GraphicsDevice.BeginScene();

	SpriteBatch.Begin();

	//タイトルロゴ

	Vector2 drawsize;
	std::string str;
	std::wstring wstr;

	Vector2 cellsize = IMAGEFONT.GetCellSize() / 2.0f;

	switch (setting_state){

	case CALIBRATIONWAIT:
	case SETTINGBOTTOM:

		wstr = _T("机の一番下までマウスを持っていき、クリックしてください。");

		str = "TAKE THE MOUSE TO THE BOTTOM AND CLICK";

		//SpriteBatch.DrawString(font_, _T("mostbottom_to_movemouse_to_click"),
		//	Vector2(1280.0f / 2.0f, 720.0f / 2.0f), Color(255, 255, 255));

		break;

	case SETTINGTOP:

		wstr = _T("机の一番上までマウスを持っていき、クリックしてください。");

		str = "TAKE THE MOUSE TO THE UP AND CLICK";

		//SpriteBatch.DrawString(font_, Vector2(1280.0f / 2.0f, 720.0f / 2.0f), Color(255, 255, 255),
		//	_T("mosttop_to_movemouse_to_click  %d"), mouse_top);

		break;

	case READY:

		wstr = _T("お待ちください。");

		str = "PLEASE WAIT";


		//SpriteBatch.DrawString(font_, _T("PLEASE WAIT"),
		//	Vector2(1280.0f / 2.0f, 720.0f / 2.0f), Color(255, 0,0),Vector2(5.0f,5.0f),
		//	Vector3_Zero,Vector3_Zero);

		break;

	}


	drawsize = IMAGEFONT.GetDrawSize(cellsize,str.c_str());

	Vector3 pos = Vector3_Zero;
	Viewport viewport = GraphicsDevice.GetViewport();
	pos.x = (viewport.Width - drawsize.x) / 2.0f;
	pos.y = (viewport.Height - drawsize.y) - 100.0f;

	SpriteBatch.Draw(*this->title_logo_,Vector3_Zero);

	SpriteBatch.DrawString(this->font_, Vector2(0.0f, 700.0f), Color(255, 255, 255), wstr.c_str());

	SpriteBatch.End();

	IMAGEFONT.DirectDrawImageString(pos, cellsize, Color(255, 255, 255), str.c_str());

	fade_.Draw();

	GraphicsDevice.EndScene();
}
