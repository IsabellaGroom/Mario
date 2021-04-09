#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Collisions.h"
#include "PowBlock.h"



GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	score = 0;
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
}

bool GameScreenLevel1::SetUpLevel()
{

	//set up player character
	Mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	Luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(64, 330), m_level_map);

	//load POW
	m_pow_block = new PowBlock(m_renderer, m_level_map);

	//Load enemies
	CreateKoopa(Vector2D(120,10), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325,32), FACING_LEFT, KOOPA_SPEED);

	//Load Coins
	CreateCoin(Vector2D(150, 350));
	CreateCoin(Vector2D(200, 350));
	CreateCoin(Vector2D(250, 250));
	CreateCoin(Vector2D(300, 250));
	CreateCoin(Vector2D(350, 250));
	CreateCoin(Vector2D(100, 150));
	
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


	//draw enemies
	for (int i = 0; i < m_enemies.size(); i++)
	{
			m_enemies[i]->Render();
		
	}

	//draw coins
	for (int i = 0; i < m_coins.size(); i++)
	{
		if (!m_coins[i]->isDead)
		{
			m_coins[i]->Render();
		}
	}

	//draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

	//draws characters
	Mario->Render();
	Luigi->Render();

	//draws POW
	m_pow_block->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	m_background->Play();

	cout << score << endl;
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

	if (Collisions::Instance()->Circle(Mario, Luigi))
	{
		cout << "Circle hit!" << endl;
	}

	if (Collisions::Instance()->Box(Mario->GetCollisionBox(), Luigi->GetCollisionBox()))
	{
		cout << "Box hit!" << endl;
	}


	//cout << m_level_map->GetTileAt(Mario->GetPosition().x, Mario->GetPosition().y) << endl;
	//cout << Mario->GetPosition().y << endl;
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
	//std::cout << "YEEE" << std::endl;

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{

	if (!m_enemies.empty())
	{
	
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
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
							isSwitching = true;						
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
