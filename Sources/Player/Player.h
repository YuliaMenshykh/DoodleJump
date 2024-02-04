#pragma once

#include <vector>

class Sprite;
class Projectile;

class Player
{

protected:

	//screen
	int screenWidth;
	int screenHeight;

public:

	Player(int& width, int& height);

	~Player();

	float playerX;
	float playerY;

	float amplitude = 0.2;

	int jumpLength = 25;

	bool isOver = false;

	void ConstructSprite();

	void DrawPlayer();

	void MoveRight();

	void MoveLeft();

	void InitPlayerLocation();

	//sprite
	const int spriteWidth = 60;
	const int spriteHight = 60;

	std::vector<Sprite*> sprites;
	Sprite* spriteToDraw = nullptr;

	const char* path;


	//Handle projectiles

	std::vector<Projectile*> projectiles;

	void Shoot(bool isReleased, int xrelative, int yrelative);

	void DrawProjectile(int xrelative, int yrelative);

	
};
