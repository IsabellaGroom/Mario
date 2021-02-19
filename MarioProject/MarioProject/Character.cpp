#include "Character.h"
#include "Texture2D.h"
#include "constants.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map)
{
	m_renderer = renderer;
	m_position = start_position;
	m_texture = new Texture2D(m_renderer);
	m_facing_direction = FACING_RIGHT;
	m_moving_left = false;
	m_moving_right = false;
	m_jump_force = INITIAL_JUMP_FORCE;
	m_collision_radius = 15.0f;
	m_can_jump = true;
	m_jumping = false;
	m_current_level_map = map;

	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load background texture" << std::endl;
	}
}

Character::~Character()
{
	m_renderer = nullptr;
}

void Character::Render()
{
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}


}

void Character::Update(float deltaTime, SDL_Event e)
{
	//cout << "Y: " << m_position.y << " X: " << m_position.x << endl;

	//deal with jumping first
	if (m_jumping)
	{
		cout << "JUMPING" << endl;
		//adjust position
		m_position.y -= m_jump_force * deltaTime;

		//reduce jump force
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;
		m_position.y += m_jump_force * deltaTime;

		//deltaTime?

		//is jump force 0?
		if (m_jump_force < 0.0f)
		{
			m_jumping = false;
		}

		AddGravity(deltaTime);
	}

	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}

	//collision position variables
	int centralX_position = (int)(m_position.x + (m_texture->GetWidth() * 0.5)
		/ TILE_WIDTH);
	int foot_position = (int)(m_position.y + m_texture->GetHeight())
		/ TILE_HEIGHT;

	//deal with gravity
	if (m_current_level_map->GetTileAt(foot_position, centralX_position) == 0)
	{
		AddGravity(deltaTime);
	}
	else
	{
		//collided with ground so we can jump again
		m_can_jump = true;
	}
	
}


void Character::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}

Vector2D Character::GetPosition()
{
	return m_position;
}

void Character::MoveLeft(float deltaTime)
{
	m_facing_direction = FACING_LEFT;
	m_position.x -= MOVESPEED;
	
}

void Character::MoveRight(float deltaTime)
{
	m_facing_direction = FACING_RIGHT;
	m_position.x += MOVESPEED;
	//*deltaTime?
	
}

void Character::AddGravity(float deltaTime)
{
	m_jump_force = INITIAL_JUMP_FORCE;
	//keeps character on the floor
	if ((m_position.y + 64) <= SCREEN_HEIGHT)
	{
		m_position.y += GRAVITY * deltaTime;
		//strength of gravity
	}
	else
	{
		//program always runs this
		m_can_jump = true;
	}
}

void Character::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
	}
}

float Character::GetCollisionRadius()
{
	return m_collision_radius;
}
