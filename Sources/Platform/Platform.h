

class Sprite;
class Player;

class Platform
{
public:

	Platform(int& width, int& height);
	~Platform();

	//sprite
	int spriteWidth = 70;
	int spriteHeight = 15;

	
	Sprite* sprite = nullptr;
	const char* path;

	float platformX = 0.f;
	float platformY = 0.f;

	float platformSpeed = 0.5f;

	void ConstructSprite();

	void DrawPlatform(Player& player);

	void RandPlatformsLoc();

	void UpdateLocation();

	//Timer

	float lastUpdateTime = 0.f;
	float updateInterval = 3.0f;
	float deltaTime = 0.f;
	float time = 0.f;
	float counter =0.f;
	


	//Score
	int distancePassed = 0;
	int platformPassed = 0;
	int BestResult = 0;
	bool playerLanded;

protected:

	//screen
	int screenWidth;
	int screenHeight;
};