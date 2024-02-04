#pragma once
#include "Framework.h"

#include "vector"
#include "Enemy/Enemy.h"
#include "Platform/Platform.h"




class Pickup;
class Player;



/* Test Framework realization */
class MyFramework : public Framework
{

protected:


	
	
	Pickup* pickup = nullptr;

	Player* palyer = nullptr;

	int screenWidth = 0;
	int screenHeight = 0;

	int mouseMoveX = 0;
	int mouseMoveY = 0;


	std::vector<Platform> platforms;
	const int numPlatforms = 40;

	std::vector<Enemy> enemys;
	const int numEnemies = 2;

	bool shouldRender = false;

	float restartSec = 2000;

public:


	virtual void PreInit(int& width, int& height, bool& fullscreen)override;

	virtual bool Init()override;

	virtual void Close()override;

	virtual bool Tick()override;

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative)override;

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased)override;

	virtual void onKeyPressed(FRKey k)override;

	virtual void onKeyReleased(FRKey k)override;

	virtual const char* GetTitle() override;


	//additional methods

	void CreateScreen(int& width, int& height);

	void RestartGame();

	virtual ~MyFramework() override;
};