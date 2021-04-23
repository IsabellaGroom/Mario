#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>
#include <fstream>
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Collisions.h"
#include "PowBlock.h"
#include "Commons.h"



GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	
	m_level_map = nullptr;
	SetLevelMap();
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	m_background_texture = nullptr;
	delete Mario;
	delete Luigi;
	Mario = nullptr;
	Luigi = nullptr;
	delete m_pow_block;
	m_pow_block = nullptr;
	m_enemies.clear();
	m_coins.clear();

	SDL_FreeSurface(t_message);
	TTF_CloseFont(t_font);

}

bool GameScreenLevel1::SetUpLevel()
{

	//set up player character
	Mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	Luigi = new CharacterLuigi(m_renderer, "Images/luigi.png", Vector2D(64, 330), m_level_map);

	//load POW
	m_pow_block = new PowBlock(m_renderer, m_level_map);

	//Load enemies
	CreateKoopa(Vector2D(120,10), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325,32), FACING_LEFT, KOOPA_SPEED);

	//Load Coins
	CreateCoin(Vector2D(320, 350));
	CreateCoin(Vector2D(360, 350));
	CreateCoin(Vector2D(400, 350));

	CreateCoin(Vector2D(250, 120));
	CreateCoin(Vector2D(300, 120));
	CreateCoin(Vector2D(200, 120));

	CreateCoin(Vector2D(100, 20));
	CreateCoin(Vector2D(400, 20));
	
	//Load Music
	m_background = new Music();
	m_background->Load("Music/Mario.mp3");

	//Load FX
	m_coinFX = new SoundFX();
	m_coinFX->Load("Music/Coin.ogg");
	m_OverFX = new SoundFX();
	m_OverFX->Load("Music/GameOver.wav");

	//screenshake variables
	m_screenshake = false;
	m_background_yPos = 0.0f;
	
	//Load text
	t_font = TTF_OpenFont("SuperMario.ttf", 26);
	t_text = "Score: " + to_string(score);

	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture" << std::endl;
		return false;
	}
	return true;
}

void GameScreenLevel1::Render()
{

	//draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

	//draws characters
	Mario->Render();
	Luigi->Render();


	//draw coins
	for (int i = 0; i < m_coins.size(); i++)
	{
		if (!m_coins[i]->isDead)
		{
			m_coins[i]->Render();
		}
	}

	//draws POW
	m_pow_block->Render();


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

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	m_background->Play();
	//shake screen
	if (m_screenshake)
	{

		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;
		
		//ends after duration
		if (m_shake_time <= 0.0f)
		{
			m_screenshake = false;
			m_background_yPos = 0.0f;
		}
	}

	//update Character
	Mario->Update(deltaTime, e);
	Luigi->Update(deltaTime, e);

	//Update functions
	UpdatePOWBlock();
	UpdateEnemies(deltaTime, e);

	for (int i = 0; i < m_coins.size(); i++)
	{
		if (!m_coins[i]->isDead)
		{
			m_coins[i]->Update(deltaTime, e);
		}

		if (Collisions::Instance()->Circle(Mario, m_coins[i]))
		{
			m_coinFX->Play();
			score += 1;
			m_coins[i]->isDead = true;
			delete m_coins[i];
		}
	}

	t_text = "Score: " + to_string(score);
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
					  { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);

}

void GameScreenLevel1::UpdatePOWBlock()
{
	if (Collisions::Instance()->Box(m_pow_block->GetCollisionBox(), Mario->GetCollisionBox()))
	{
		if (Mario->IsJumping())
		{
			//std::cout << "HIT" << std::endl;
			DoScreenShake();
			m_pow_block->TakeHit();
			Mario->CancelJump();
		}
	}
}

void GameScreenLevel1::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	float posY;
	float posX;
	Vector2D newPos;

	if (!m_enemies.empty())
	{
	
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			posX = m_enemies[i]->GetPosition().x;
			posY = m_enemies[i]->GetPosition().y;

			if (posX >= SCREEN_WIDTH - 50)
			{
				newPos.x = 50.0f;
				newPos.y = posY;
				m_enemies[i]->SetPosition(newPos);
			}

			if (posX <= 50)
			{
				newPos.x = 400;
				newPos.y = posY;
				m_enemies[i]->SetPosition(newPos);
			}
			

				m_enemies[i]->Update(deltaTime, e);
				
				//check to see if enemy collides with player
				if ((m_enemies[i]->GetPosition().y > 300.0f ||
					m_enemies[i]->GetPosition().y <= 64.0f) &&
					(m_enemies[i]->GetPosition().x < 64.0f ||
						m_enemies[i]->GetPosition().x >
						SCREEN_WIDTH - 96.0f))
				{
					//ignore collisions if behind pipe
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
			m_background->Stop();
			RecordScore(score);
			isSwitching = true;
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	koopa = new CharacterKoopa(m_renderer, "Images/Koopa.png", m_level_map, position, direction, speed);
	m_enemies.push_back(koopa);
}

void GameScreenLevel1::CreateCoin(Vector2D position)
{
	coin = new CharacterCoin(m_renderer, "Images/Coin.png",position, m_level_map);
	m_coins.push_back(coin);
}

void GameScreenLevel1::RecordScore(int score)
{
	ofstream OutFile;

	OutFile.open("Score.txt", ios::out | ios::app);
	OutFile.clear();
	OutFile << score << endl;
	OutFile.close();
}
