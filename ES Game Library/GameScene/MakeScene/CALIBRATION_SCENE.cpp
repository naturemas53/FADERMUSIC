#include "CALIBRATION_SCENE.hpp"
#include "../../StdAfx.h"
#include "../SceneShared.hpp"

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

	mouse_top = 0;
	setting_state = WAIT;

	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void CALIBRATION_SCENE::Finalize()
{
	// TODO: Add your finalization logic here

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
	case CALIBRATION_SCENE::WAIT:

		if (mouse_buffer.IsPressed(Mouse_Button1)){
			setting_state = SETTINGNOW;
		}

		break;

	case CALIBRATION_SCENE::SETTINGNOW:

		mouse_top += mouse_state.Y;

		if (mouse_buffer.IsPressed(Mouse_Button1)){
			setting_state = CHANGEING;
			if (mouse_top < 0) mouse_top *= -1;
		}

		break;

	case CALIBRATION_SCENE::CHANGEING:

		SceneShared().SetLongIntegerForKey("MOUSE_MAX_Y", mouse_top);
		return GAME_SCENE(new SONGPLAY_SCENE());

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
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();

	SpriteBatch.Begin();

	switch (setting_state){

	case WAIT:

		SpriteBatch.DrawString(font_, _T("mostbottom_to_movemouse_to_click"), 
			Vector2(1280.0f / 2.0f, 720.0f / 2.0f), Color(255, 255, 255));

		break;

	case SETTINGNOW:

		SpriteBatch.DrawString(font_, Vector2(1280.0f / 2.0f, 720.0f / 2.0f), Color(255, 255, 255),
			_T("mosttop_to_movemouse_to_click  %d"), mouse_top);

		break;

	case CHANGEING:

		SpriteBatch.DrawString(font_, _T("PLEASE WAIT"),
			Vector2(1280.0f / 2.0f, 720.0f / 2.0f), Color(255, 0,0),Vector2(5.0f,5.0f),
			Vector3_Zero,Vector3_Zero);

		break;

	}

	SpriteBatch.End();

	GraphicsDevice.EndScene();
}
