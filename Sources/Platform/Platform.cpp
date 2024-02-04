#include "Platform.h"
#include "../Sources/Framework.h"
#include "../Player/Player.h"
#include <vector>

Platform::Platform(int& width, int& height)
    : screenWidth(width), screenHeight(height)
{
}
Platform::~Platform()
{
    delete sprite;
}

void Platform::ConstructSprite()
{
	path = "data/Platform.png";
	sprite = createSprite(path);
	setSpriteSize(sprite, spriteWidth, spriteHeight);

    RandPlatformsLoc();
}

void Platform::RandPlatformsLoc()
{
    platformX = static_cast<float>(rand() % (screenWidth - spriteWidth));
    platformY = static_cast<float>(rand() % (screenHeight + 600));
}

void Platform::UpdateLocation() 
{
    time = getTickCount();
    time *= 0.001f;
    
    deltaTime = time - lastUpdateTime;
    lastUpdateTime = time;

    counter += deltaTime;

    if (counter >= 3.0f) 
    {
        platformPassed += 1;
        counter = 0.0f;

        platformX = static_cast<float>(rand() % (screenWidth - spriteWidth));
        platformY = static_cast<float>(rand() % (400));

        drawSprite(sprite, platformX, platformY);
        playerLanded = true;
    }
    
}

void Platform::DrawPlatform(Player& player)
{

    drawSprite(sprite, platformX, platformY);

    //Colision player + platform
    if (player.playerX + player.spriteWidth > platformX && 
        player.playerX < platformX + spriteWidth &&
        player.playerY  + player.spriteHight > platformY  &&
        player.playerY + player.spriteHight < platformY + spriteHeight &&
        player.amplitude>0)
    {
        player.amplitude = -5;
       
    }
   
    if (player.playerY < screenHeight / 2)
    {
        platformY++;
    }
    else if (player.playerY < screenHeight / 3)
    {
        player.playerY++;

    }

   
    if (platformY >= screenHeight-50)
    {
       UpdateLocation();

       if (playerLanded)
       {
           distancePassed += player.spriteHight;
           if (distancePassed > BestResult)
           {
               BestResult = distancePassed;
           }
       }
    }
    
   
    playerLanded = false;
}



