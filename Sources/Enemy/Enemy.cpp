#include "Enemy.h"
#include "../Framework.h"
#include"../Player/Player.h"
#include "../Projectile/Projectile.h"
#include "../Pickup/Pickup.h"

Enemy::Enemy(int& width, int& height)
	:screenWidth(width), screenHeight(height)
{
}
Enemy::~Enemy()
{
    for (Sprite* sprite : sprites)
    {
        delete sprite;
    }
    sprites.clear();
}

void Enemy::ConstructSprite()
{
	const std::vector<const char*> spritesPath =
	{
		"data/monster1x1.png",
		"data/monster2x1.png",
	};

	sprites.reserve(2);

	for (const char* path : spritesPath)
	{
		Sprite* newSprite = createSprite(path);
		sprites.emplace_back(newSprite);
		setSpriteSize(newSprite, spriteWidth, spriteHeight);
		spriteX = static_cast<float>(rand() % (screenWidth - spriteWidth));
		spriteY = static_cast<float>(rand() % (screenHeight + 300));
	}

    randomEnemy = std::rand() % sprites.size();
	spriteToDraw = sprites[randomEnemy];
}

void Enemy::UpdateLocatiom()
{
    spriteX = static_cast<float>(rand() % (screenWidth - spriteWidth));
    spriteY = static_cast<float>(rand() % (screenHeight - spriteHeight + 1) - screenHeight);

}

void Enemy::ColisionPickup(Pickup* pickup)
{
    for (Projectile* projectile : pickup->projectiles)
    {
        if (projectile->projX + projectile->spriteWidth > spriteX &&
            projectile->projX < spriteX + spriteWidth &&
            projectile->projY + projectile->spriteHeight > spriteY &&
            projectile->projY < spriteY + spriteHeight)
        {

            UpdateLocatiom();
            break;

        }
    }
}

void Enemy::ColisionPlayerProj(Player& player)
{
    for (Projectile* projectile : player.projectiles)
    {
        if (projectile->projX + projectile->spriteWidth > spriteX &&
            projectile->projX < spriteX + spriteWidth &&
            projectile->projY + projectile->spriteHeight > spriteY &&
            projectile->projY < spriteY + spriteHeight)
        {

            UpdateLocatiom();
            break;

        }
    }
}

void Enemy::DrawEnemy(Player& player, Pickup* pickup)
{
    
    drawSprite(spriteToDraw, spriteX, spriteY);

    if (player.playerY < screenHeight/2)
    {
        spriteY++;
        if (spriteY >= screenHeight - 100)
        {
            UpdateLocatiom();
        }
    }
    

    //Handle collision with projectiles from pickup
    if (pickup->projectiles.size() != 0)
    {
        ColisionPickup(pickup);
        
    }
    
    //Handle collision with player's projectiles
    if (player.projectiles.size() != 0)
    {
        ColisionPlayerProj(player);
    }


    //Handle collision with player
    if (player.playerX + player.spriteWidth > spriteX &&
        player.playerX < spriteX + spriteWidth &&
        player.playerY + player.spriteHight > spriteY &&
        player.playerY < spriteY + spriteHeight &&
        player.amplitude > 0)
    {
        player.amplitude = -4;
        UpdateLocatiom();
        
    }
    else if 
        (player.playerX + player.spriteWidth > spriteX &&
        player.playerX < spriteX + spriteWidth &&
        player.playerY < spriteY + spriteHeight &&
        player.playerY + player.spriteHight > spriteY)
    {
        player.isOver = true;
    }


}

