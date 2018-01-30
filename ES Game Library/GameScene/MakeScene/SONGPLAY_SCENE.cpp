// #include "Extension\DirectX11\DXGraphics11.hpp"
#include "SONGPLAY_SCENE.h"
#include "../../StdAfx.h"
#include "../../MyMakeClasses/GamePlayState.h"


/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load all of your content.
/// Initialize will enumerate through any components and initialize them as well.
/// </summary>
bool SONGPLAY_SCENE::Initialize()
{
	
	this->nowstate_ = new GamePlayState();

	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void SONGPLAY_SCENE::Finalize()
{
	// TODO: Add your finalization logic here
	delete this->nowstate_;

}

/// <summary>
/// Allows the game to run logic such as updating the world,
/// checking for collisions, gathering input, and playing audio.
/// </summary>
/// <returns>
/// Scene continued value.
/// </returns>
int SONGPLAY_SCENE::Update()
{
	// TODO: Add your update logic here

	AbstructState* next = this->nowstate_->Update();

	if (next != nullptr){
		delete this->nowstate_;
		this->nowstate_ = next;
	}

	return this->nowstate_->NextScene();
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void SONGPLAY_SCENE::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_Black);

	GraphicsDevice.BeginScene();

	this->nowstate_->Draw();

	GraphicsDevice.EndScene();
}