#include <GameEngine/GameEngine.h>
#include <GameEngine/core/load.h>
#include <iostream>

#include <GameEngine/utility/stb_image.h>

using namespace std;

class Game : public GameEngine::Module
{
public:
    void init()
    {
        GameEngine::LOG::DEBUG("GameModule", "Hello");
        engine->me.add(GameEngine::MEDIA::ACTION::PRINT, (std::string) "Hello");

        tex = GameEngine::LOAD::Image("res/milk.png");
        engine->me.add(GameEngine::MEDIA::ACTION::ADD_TEXTURE, std::pair<std::string, GameEngine::texture>("tex", tex));
    }

    void update(float deltaTime)
    {
        engine->me.add(GameEngine::MEDIA::ACTION::CLEAR, GameEngine::vec3(1.0f, 0.4f, 0.0f));
        engine->me.add(GameEngine::MEDIA::ACTION::DRAW_TEXTURE, (std::string) "tex");
    }

private:
    GameEngine::texture tex;
};

int main()
{
    GameEngine::GameEngine engine("Hello World", false);

    engine.add("Game", new Game());

    GameEngine::LOG::DEBUG("Main", "Hello");

    engine.start();

    return 0;
}