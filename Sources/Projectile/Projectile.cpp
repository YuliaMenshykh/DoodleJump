#include "Projectile.h"
#include "../Framework.h"
#include "iostream"

Projectile::Projectile(int& width, int& height)
	:screenWidth(width), screenHeight(height)
{

	path = "data/bullet.png";
	sprite = createSprite(path);
    setSpriteSize(sprite, spriteWidth, spriteHeight);
}
Projectile::~Projectile()
{
    delete sprite;
}

bool Projectile::DrawSprite()
{
    drawSprite(sprite, projX, projY);

    projX += velocityX;
    projY += velocityY;

    
    if (projX >= screenWidth) 
    {
        projX = 0;
        projY -= 30;
    }
    else if (projX <= 0) 
    {
        projX = screenWidth - 1;
        projY -= 30;
    }

    
    if (projY >= screenHeight && projY <= 0)
    {
        projX = 0;  
        projY = 0;  
        return false;  
    }

    return true;  // Projectile should continue to be drawn
}

void Projectile::Movement(int xrelative, int yrelative, int playerLocX, int playerLocY)
{
    int dx = xrelative - playerLocX;
    int dy = yrelative - playerLocY;

    float length = sqrt(dx * dx + dy * dy);

    // Normalize the direction vector
    if (length != 0)
    {
        dirX = dx / length;
        dirY = dy / length;

    }
  
    //30 is a player's width/2 and height/2
    projX = playerLocX+30;
    projY = playerLocY+30;

    velocityX = dirX * projectileSpeed;
    velocityY = dirY * projectileSpeed;

}

