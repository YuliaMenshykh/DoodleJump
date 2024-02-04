#include "MyFramework.h"
#include <ctime>
#include "iostream"
#include "Projectile/Projectile.h"
#include "Pickup/Pickup.h"
#include "Player/Player.h"



void MyFramework::CreateScreen(int& width, int& height)
{
	while (true)
	{
		std::cout << "Enter the screen width: ";
		if (std::cin >> width && width > 0)
		{
			screenWidth = width;
			break;
		}
		else
		{
			std::cout << "Invalid input. Please enter a positive integer.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	while (true)
	{
		std::cout << "Enter the screen height: ";
		if (std::cin >> height && height > 0)
		{
			screenHeight = height;
			break;
		}
		else
		{
			std::cout << "Invalid input. Please enter a positive integer.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
}





void MyFramework::PreInit(int& width, int& height, bool& fullscreen)
{
	srand(time(NULL));

	CreateScreen(width, height);

	fullscreen = false;

}


bool MyFramework::Init()
{
	
	//Create player
	palyer = new Player(screenWidth, screenHeight);
	palyer->ConstructSprite();

	//Create platforms
	platforms.reserve(numPlatforms);
	for (int i = 0; i < numPlatforms; ++i)
	{
		platforms.push_back(Platform(screenWidth, screenHeight));
		platforms[i].ConstructSprite();
	}

	//Create enemys
	enemys.reserve(numEnemies);
	for (int i = 0; i < numEnemies; i++)
	{
		enemys.push_back(Enemy(screenWidth, screenHeight));
		enemys[i].ConstructSprite();
	}

	
	//Create pickups
	pickup = new Pickup(screenWidth, screenHeight);

	
	return true;
}

void MyFramework::RestartGame()
{
	unsigned int startTime = getTickCount();

	std::cout << "You loose" << std::endl;
	std::cout << "You passed : " << platforms[0].BestResult << "units" << std::endl;
	std::cout << "You jumped on : " << platforms[0].platformPassed << "platforms" << std::endl;
	std::cout << "Wait 2 second for a new match" << std::endl;
	platforms[0].BestResult = 0;
	platforms[0].platformPassed = 0;

	// Stun game for 2 seconds
	while (getTickCount() - startTime < restartSec)
	{
		
		//Change location for all actors
		for (int i = 0; i < numPlatforms; ++i)
		{
			platforms[i].RandPlatformsLoc();
		}
		for (int i = 0; i < numEnemies; ++i)
		{
			enemys[i].UpdateLocatiom();
		}
		palyer->InitPlayerLocation();
		pickup->ClearProjectiles();
	}

	

	//Start again
	pickup->shouldRender = false;
	palyer->isOver = false;
}

void MyFramework::Close()
{

}

bool MyFramework::Tick()
{
	drawTestBackground();

	
	if (palyer->isOver)
	{
		RestartGame();

	}
	else
	{
		palyer->DrawPlayer();

		for (int i = 0; i < numPlatforms; ++i)
		{
			platforms[i].DrawPlatform(*palyer);
		}

		for (int i = 0; i < numEnemies; ++i)
		{
			enemys[i].DrawEnemy(*palyer, pickup);
		}
		
		pickup->DrawSprite(enemys, palyer->playerX, palyer->playerY);


		if (pickup->shouldRender)
		{
			pickup->DrawProjectile();
		}
		if (shouldRender)
		{
			shouldRender = true;
			palyer->DrawProjectile(mouseMoveX, mouseMoveY);

		}
	}

	return false;
}


void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative)
{
	mouseMoveX = x;
	mouseMoveY = y;

}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased)
{

	if (button == FRMouseButton::LEFT)
	{
		palyer->Shoot(isReleased, mouseMoveX, mouseMoveY);
		shouldRender = true;
	}
	

}

void MyFramework::onKeyPressed(FRKey k)
{
	if (k == FRKey::RIGHT)
	{
		palyer->MoveRight();
	}
	if (k == FRKey::LEFT)
	{
		palyer->MoveLeft();
	}
}

void MyFramework::onKeyReleased(FRKey k)
{

}

const char* MyFramework::GetTitle()
{
	return "Arcanoid";
}

MyFramework::~MyFramework()
{

}