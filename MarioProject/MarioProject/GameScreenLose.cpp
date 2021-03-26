#include "GameScreenLose.h"
#include "Texture2D.h"
#include <iostream>

GameScreenLose::GameScreenLose(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenLose::~GameScreenLose()
{
	m_background_texture = nullptr;
}

bool GameScreenLose::SetUpLevel()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/GameOver.png"))
	{
		std::cout << "Failed to load background texture " << std::endl;
		return false;
	}
	return true;
}


void GameScreenLose::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
}

void GameScreenLose::Update(float deltaTimer, SDL_Event e)
{

}
