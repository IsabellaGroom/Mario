#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenMenu.h"
#include "GameScreenLose.h"
#include "GameScreenLevel2.h"



GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	m_renderer = renderer;
	m_current_screen = nullptr;
	ChangeScreen(startScreen);

	score = 0;

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
    if (m_current_screen->isDead)
	{
	  ChangeScreen(SCREEN_GAMEOVER);
	}

	if (m_current_screen->restart)
	{
		m_current_screen->restart = false;
		ChangeScreen(SCREEN_LEVEL1);
	}

	if (m_current_screen->isSwitching)
	{
		ChangeScreen(SCREEN_LEVEL2);
	}
	
	m_current_screen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS new_screen)
{
	GameScreenLevel1* tempLevel1;
	GameScreenLevel2* tempLevel2;
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
		tempLevel1 = new GameScreenLevel1(m_renderer);
		m_current_screen = (GameScreen*)tempLevel1;
		tempLevel1 = nullptr;
		break;
	case SCREEN_LEVEL2:
		this_screen = SCREEN_LEVEL2;
		tempLevel2 = new GameScreenLevel2(m_renderer);
		m_current_screen = (GameScreen*)tempLevel2;
		tempLevel2 = nullptr;
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
