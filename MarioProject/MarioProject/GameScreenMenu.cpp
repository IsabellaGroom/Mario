#include "GameScreenMenu.h"
#include "Texture2D.h"
#include <iostream>

GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenMenu::~GameScreenMenu()
{
	m_background_texture = nullptr;
}

bool GameScreenMenu::SetUpLevel()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture" << std::endl;
		return false;
	}
	return true;
}

void GameScreenMenu::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
}

void GameScreenMenu::Update(float deltaTime, SDL_Event e)
{

}
