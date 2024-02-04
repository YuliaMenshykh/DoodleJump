#pragma once


class Sprite;

class Projectile 
{
public:
	Projectile(int& width, int& height);
	~Projectile();

	//sprite
	Sprite* sprite = nullptr;
	int spriteWidth = 20;
	int spriteHeight = 20;
	const char* path;

	bool DrawSprite();

	void Movement(int xrelative, int yrelative, int playerLocX, int playerLocY);

	int projX;
	int projY;

private:
	int screenWidth;
	int screenHeight;

	int velocityX;
	int velocityY;

	int projectileSpeed = 3;

	float dirX = 0.f;
	float dirY = 0.f;

};