#include <GameEngine/GameEngine.h>
#include <iostream>

using namespace std;

class Game : public GameEngine::Module
{
public:
    void init()
    {
        GameEngine::LOG::DEBUG("GameModule", "Hello");
        // engine->add(GameEngine::MEDIA::ACTION::PRINT, (std::string) "Hello");
    }

    void update(float deltaTime)
    {
        // engine->add(GameEngine::MEDIA::ACTION::CLEAR, Vector3(1.0f, 0.4f, 0.0f));
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