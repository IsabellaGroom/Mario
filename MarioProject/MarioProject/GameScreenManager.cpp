#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenMenu.h"
#include "GameScreenLose.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	m_renderer = renderer;
	m_current_screen = nullptr;
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	m_renderer = nullptr;
	delete m_current_screen;
	m_current_screen = nullptr;
}

void GameScreenManager::Render()
{
	m_current_screen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{

	if (m_current_screen->start)
	{
		ChangeScreen(SCREEN_LEVEL1);
	}

    if (m_current_screen->isSwitching)
	{
	  ChangeScreen(SCREEN_GAMEOVER);
	}

	if (m_current_screen->restart)
	{
		m_current_screen->restart = false;
		ChangeScreen(SCREEN_LEVEL1);
	}
	
	m_current_screen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS new_screen)
{
	GameScreenLevel1* tempScreen;
	GameScreenMenu* tempMenu;
	GameScreenLose* tempGameOver;
	//clear the old screen
	if (m_current_screen != nullptr)
	{
		delete m_current_screen;
	}

	switch (new_screen)
	{
	case SCREEN_LEVEL1:
		this_screen = SCREEN_LEVEL1;
		tempScreen = new GameScreenLevel1(m_renderer);
		m_current_screen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
		break;
	case SCREEN_MENU:
		this_screen = SCREEN_MENU;
		tempMenu = new GameScreenMenu(m_renderer);
		m_current_screen = (GameScreen*)tempMenu;
		tempMenu = nullptr;
		break;
	case SCREEN_GAMEOVER:
		this_screen = SCREEN_GAMEOVER;
		tempGameOver = new GameScreenLose(m_renderer);
		m_current_screen = (GameScreen*)tempGameOver;
		tempGameOver = nullptr;
		break;
	default:;
	}

}
