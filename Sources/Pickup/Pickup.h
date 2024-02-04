#pragma once
#include <vector>


class Sprite;
class Enemy;
class Projectile;

class Pickup
{
public:

	Pickup(int& width, int& height);

	~Pickup();

	//Sprite
	Sprite* sprite = nullptr;

	int spriteWidth = 50;

	int spriteHeight = 50;

	int pickupX;

	int pickupY;

	const char* path;

	void DrawSprite(std::vector<Enemy>& enemys,int playerX, int playerY);

	void ClearProjectiles();

	void UpdateLocation();

	void DrawProjectile();

	void CreateProjectile(std::vector<Enemy>& enemys, int playerX, int playerY);

	std::vector<Projectile*> projectiles;

	bool shouldRender = false;

private:

	int screenWidth;
	int screenHeight;

	float currentTime = 0.f;
	float lastProjectileTime = 0.f;
	int createdProjectiles = 0;
	int amountOfBullets = 70;

	
};