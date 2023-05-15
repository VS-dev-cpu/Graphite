#include <GameEngine/GameEngine.h>
#include <iostream>

using namespace std;

class Game : public GameEngine::Module
{
public:
    void init()
    {
        GameEngine::LOG::DEBUG("GameModule", "Hello");
        engine->me.add(GameEngine::MEDIA::ACTION::PRINT, (std::string) "Hello");
    }

    void update(float deltaTime)
    {
        engine->me.add(GameEngine::MEDIA::ACTION::PRINT, (std::string) "Update");
    }

private:
};

int main()
{
    GameEngine::GameEngine engine("Hello World", false);

    engine.add("Game", new Game());

    GameEngine::LOG::DEBUG("Main", "Hello");

    engine.start();

    return 0;
}