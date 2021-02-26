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
}

bool GameScreenLevel1::SetUpLevel()
{
	//set up player character
	Mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	Luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(64, 330), m_level_map);

	//load POW
	m_pow_block = new PowBlock(m_renderer, m_level_map);

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
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
	
	//draws characters
	Mario->Render();
	Luigi->Render();
	
	//draws POW
	m_pow_block->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//update Character
	Mario->Update(deltaTime, e);
	Luigi->Update(deltaTime, e);
	UpdatePOWBlock();

	if (Collisions::Instance()->Circle(Mario, Luigi))
	{
		cout << "Circle hit!" << endl;
	}

	if (Collisions::Instance()->Box(Mario->GetCollisionBox(), Luigi->GetCollisionBox()))
	{
		cout << "Box hit!" << endl;
	}


	//cout << m_level_map->GetTileAt(Mario->GetPosition().x, Mario->GetPosition().y) << endl;
	cout << Mario->GetPosition().y << endl;
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {
		              { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
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
			//DoScreenShake();
			m_pow_block->TakeHit();
			Mario->CancelJump();
		}
	}
}