#include "Player.h"
#include "../Framework.h"
#include "../Projectile/Projectile.h"



Player::Player(int& width, int& height)
	:screenWidth(width), screenHeight(height)
{
	InitPlayerLocation();
}
Player::~Player()
{
	for (Sprite* sprite : sprites)
	{
		delete sprite;
	}
	sprites.clear();

	for (Projectile* projectile : projectiles)
	{
		delete projectile;
	}
	projectiles.clear();
}


void Player::InitPlayerLocation()
{
	playerX = screenWidth / 2;
	playerY = screenHeight - 400;
}

void Player::ConstructSprite()
{
	const std::vector<const char*> spritesPath =
		{
			"data/spaceLeft.png",
			"data/spacePuca.png",
			"data/spaceRight.png",
		};


	sprites.reserve(3);
	projectiles.reserve(5);

	for (const char* path : spritesPath)
	{
		Sprite* newSprite = createSprite(path);
		sprites.emplace_back(newSprite);
	}
	
	spriteToDraw = sprites[0];
	
}




void Player::DrawPlayer()
{
	amplitude += 0.1;
	playerY += amplitude;


	if (playerY > screenHeight)
	{
		amplitude = -5;
	}
	if (playerY >= screenHeight - 50)
	{
		isOver = true;
	}
	drawSprite(spriteToDraw, playerX, playerY);
}

void Player::MoveRight()
{
	spriteToDraw = sprites[2];
	if (playerX >= screenWidth - spriteWidth)
	{
		playerX = 0;
		drawSprite(spriteToDraw, playerX, playerY);
		
	}
	else
	{
		playerX += jumpLength;
		drawSprite(spriteToDraw, playerX, playerY);
	}

	
}

void Player::MoveLeft()
{
	
	spriteToDraw = sprites[0];
	if (playerX <= 0)
	{
		playerX = screenWidth - spriteWidth;
		drawSprite(spriteToDraw, playerX, playerY);
	}
	else
	{
		playerX -= jumpLength;
		drawSprite(spriteToDraw, playerX, playerY);

	}
	
	
}

void Player::Shoot(bool isReleased, int xrelative, int yrelative)
{
	if (isReleased)
	{
		projectiles.push_back(new Projectile(screenWidth, screenHeight));

		projectiles.back()->Movement(xrelative, yrelative, this->playerX, this->playerY);

		spriteToDraw = sprites[0];
		drawSprite(spriteToDraw, playerX, playerY);
	}
	
	
}

void Player::DrawProjectile(int xrelative, int yrelative)
{
	// Draw and move each projectile
	for (auto it = projectiles.begin(); it != projectiles.end();)
	{
		
		if (!(*it)->DrawSprite())
		{
			delete* it;
			it = projectiles.erase(it);
		}
		else
		{
			(*it)->DrawSprite();
			++it;
		}
	}
	
}



