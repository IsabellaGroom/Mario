#include "GameScreenLevel2.h"
#include "Texture2D.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Collisions.h"
#include "PowBlock.h"
#include <iostream>
#include <fstream>

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_level_map = nullptr;
	SetLevelMap();
	SetUpLevel();
	GetScore();
}

GameScreenLevel2::~GameScreenLevel2()
{
	m_background_texture = nullptr;
	delete Mario;
	Mario = nullptr;

	SDL_FreeSurface(t_message);
	TTF_CloseFont(t_font);

}

bool GameScreenLevel2::SetUpLevel()
{

	//set up player character
	Mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 30), m_level_map);

	//Load Music
	m_background = new Music();
	m_background->Load("Music/MarioUnderworld.mp3");

	//Load FX
	m_coinFX = new SoundFX();
	m_coinFX->Load("Music/Coin.ogg");
	m_OverFX = new SoundFX();
	m_OverFX->Load("Music/GameOver.wav");

	//Load Coins
	CreateCoin(Vector2D(150, 182));

	CreateCoin(Vector2D(185, 182));
	CreateCoin(Vector2D(185, 255));
	CreateCoin(Vector2D(185, 285));

	CreateCoin(Vector2D(215, 182));
	CreateCoin(Vector2D(215, 255));
	CreateCoin(Vector2D(215, 285));

	CreateCoin(Vector2D(245, 182));
	CreateCoin(Vector2D(245, 255));
	CreateCoin(Vector2D(245, 285));

	CreateCoin(Vector2D(280, 182));
	CreateCoin(Vector2D(280, 255));
	CreateCoin(Vector2D(280, 285));

	CreateCoin(Vector2D(310, 182));

	//Load Enemies
	CreateKoopa(Vector2D(100, 330), FACING_LEFT, KOOPA_SPEED);
	CreateKoopa(Vector2D(185, 182), FACING_RIGHT, KOOPA_SPEED);

	//Load text
	t_font = TTF_OpenFont("SuperMario.ttf", 26);
	t_text = "Score: " + to_string(score);

	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundUG.png"))
	{
		std::cout << "Failed to load background texture" << std::endl;
		return false;
	}


	return true;

}

void GameScreenLevel2::SetLevelMap()
{

	int map[MAP_HEIGHT][MAP_WIDTH] =
	{
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
		{ 1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1 },
		{ 1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1 },
		{ 1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);
}

void GameScreenLevel2::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

	

	//draw coins
	for (int i = 0; i < m_coins.size(); i++)
	{
		if (!m_coins[i]->isDead)
		{
			m_coins[i]->Render();
		}
	}
	//draws characters
	Mario->Render();

	//draw enemies
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();

	}


	//Draw text
	SDL_QueryTexture(t_texture, NULL, NULL, &t_width, &t_height);
	SDL_Rect tempRect = { 0,0,t_width, t_height };


	t_message = TTF_RenderText_Solid(t_font, t_text.c_str(), t_colour);
	if (t_message == NULL)
	{
		cout << "Unable to render text ", TTF_GetError();
	}
	else
	{
		t_texture = SDL_CreateTextureFromSurface(m_renderer, t_message);
	}


	SDL_RenderCopy(m_renderer, t_texture, NULL, &tempRect);
	SDL_RenderPresent(m_renderer);

}

void GameScreenLevel2::Update(float deltaTimer, SDL_Event e)
{
	m_background->Play();
	//cout << score << endl;

	for (int i = 0; i < m_coins.size(); i++)
	{
		if (!m_coins[i]->isDead)
		{
			m_coins[i]->Update(deltaTimer, e);
		}

		if (Collisions::Instance()->Circle(Mario, m_coins[i]))
		{
			m_coinFX->Play();
			score += 1;
			m_coins[i]->isDead = true;
			delete m_coins[i];
		}
	}

	//update Character
	Mario->Update(deltaTimer, e);

	UpdateEnemies(deltaTimer, e);

	t_text = "Score: " + to_string(score);
}

void GameScreenLevel2::UpdateEnemies(float deltaTime, SDL_Event e)
{
	float posX = 0.0f;
	float posY = 0.0f;
	Vector2D newPos;

	if (!m_enemies.empty())
	{

		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			m_enemies[i]->Update(deltaTime, e);

			
			posX = m_enemies[i]->GetPosition().x;
			posY = m_enemies[i]->GetPosition().y;

			//cout << posX << endl;


			if (posX >= SCREEN_WIDTH - 100)
			{
				m_enemies[i]->SwitchFacing(false);
				newPos.x = 50.0f;
				newPos.y = posY;
				m_enemies[i]->SetPosition(newPos);
			}

			if (posX <= 0)
			{
				newPos.x = 400;
				newPos.y = posY;
				m_enemies[i]->SetPosition(newPos);
			}

			//if behind pipe ignore collisions
			if ((m_enemies[i]->GetPosition().y > 300.0f ||
				m_enemies[i]->GetPosition().y <= 64.0f) &&
				(m_enemies[i]->GetPosition().x < 64.0f ||
					m_enemies[i]->GetPosition().x >
					SCREEN_WIDTH - 96.0f))
			{
				
			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i], Mario))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						//Mario dead
						m_background->Stop();
						m_OverFX->Play();
						isDead = true;
					}
				}

				if (m_enemies[i]->health <= 0)
				{
					m_enemies[i]->SetAlive(false);
				}
			}

			//if the enemy is no longer alive then delete
			if (!m_enemies[i]->GetAlive())
			{

				enemyIndexToDelete = i;
				//delete m_enemies[i];
			}

			//remove dead enemies -1 each update
			if (enemyIndexToDelete != -1)
			{
				m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
			}
		}
	}
	else
	{
		cout << "No enemies" << endl;
		if (Mario->GetPosition().x <= 300)
		{
			//isSwitching = true;
		}
	}
}

void GameScreenLevel2::CreateCoin(Vector2D position)
{
	coin = new CharacterCoin(m_renderer, "Images/Coin.png", position, m_level_map);
	m_coins.push_back(coin);
}

void GameScreenLevel2::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	koopa = new CharacterKoopa(m_renderer, "Images/Koopa.png", m_level_map, position, direction, speed);
	m_enemies.push_back(koopa);
}

void GameScreenLevel2::GetScore()
{
	ifstream inFile;
	inFile.open("Score.txt", ios::in);
	inFile >> score;
}

