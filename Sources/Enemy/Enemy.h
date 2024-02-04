

#include <vector>

class Sprite;
class Player;
class Pickup;


class Enemy
{
public:

    Enemy(int& width, int& height);
    ~Enemy();

    void ConstructSprite();

    void DrawEnemy(Player& player, Pickup* pickup);

    void UpdateLocatiom();

    void ColisionPickup(Pickup* pickup);

    void ColisionPlayerProj(Player& player);

    float spriteX;
    float spriteY;

private:
    int spriteWidth = 75;
    int spriteHeight = 30;

    int screenWidth;
    int screenHeight;

    std::vector<Sprite*> sprites;
    Sprite* spriteToDraw = nullptr;

    float time = 0.f;
    float deltaTime = 0.f;
    float lastUpdateTime = 0.f;
    float counter = 0.f;

    float randomEnemy = 0;

};