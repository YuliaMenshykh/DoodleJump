#include "../Pickup/Pickup.h"
#include "../Framework.h"
#include "../Enemy/Enemy.h"
#include "../Projectile/Projectile.h"


Pickup::Pickup(int& width, int& height)
	:screenWidth(width), screenHeight(height)
{
	path = "data/Pickup.png";
	sprite = createSprite(path);
	setSpriteSize(sprite, spriteWidth, spriteHeight);

	pickupX = static_cast<float>(rand() % (screenWidth - spriteWidth));
	pickupY = static_cast<float>(rand() % (screenHeight + 100));
}
Pickup::~Pickup()
{
	delete sprite;

	for (auto projectile : projectiles)
	{
		delete projectile;
	}
	ClearProjectiles();


}
void Pickup::ClearProjectiles()
{
	projectiles.clear();
}

void Pickup::CreateProjectile(std::vector<Enemy>& enemys,int playerX, int playerY)
{
	for (const auto& enemy : enemys)
	{
		if (enemy.spriteX >= 0 && enemy.spriteX < screenWidth &&
			enemy.spriteY >= 0 && enemy.spriteY < screenHeight &&
			enemy.spriteY <= screenHeight - 50)
		{

			if (currentTime - lastProjectileTime >= 0.1f)
			{
				projectiles.push_back(new Projectile(screenWidth, screenHeight));
				projectiles.back()->Movement(enemy.spriteX, enemy.spriteY, playerX, playerY);
				createdProjectiles++;
				lastProjectileTime = currentTime;
			}
			if (createdProjectiles >= amountOfBullets)
			{
				createdProjectiles = 0;
				ClearProjectiles();
				shouldRender = false;
			}
		}
	}
}

void Pickup::UpdateLocation()
{
	pickupX = static_cast<float>(rand() % (screenWidth - spriteWidth));
	pickupY = static_cast<float>(rand() % screenHeight + 1) - screenHeight * 2;

}

void Pickup::DrawSprite(std::vector<Enemy>& enemys, int playerX, int playerY)
{

	currentTime = getTickCount() * 0.001f;


	//Delete if colide with the player
	if (playerX + 60 > pickupX && playerX < pickupX + 60 &&
		playerY + 60 > pickupY && playerY < pickupY + 60) 
	{
		
		UpdateLocation();

		shouldRender = true;
		lastProjectileTime = currentTime;
		
	}
	else 
	{
		
		drawSprite(sprite, pickupX, pickupY);

		//Delete if too low
		if (pickupY >= screenHeight - 100) 
		{
			UpdateLocation();
		}

		//Move when the player move
		if (playerY < 200)
		{
			pickupY++;
		}

		CreateProjectile(enemys, playerX, playerY);
	}

}

void Pickup::DrawProjectile()
{
	//draw and move each projectile
	if (shouldRender)
	{
		for (auto it = projectiles.begin(); it != projectiles.end();)
		{
			if ((*it)->DrawSprite())
			{
				++it;
			}
			else
			{
				delete* it;
				it = projectiles.erase(it);
			}
		}
	}

}


	
