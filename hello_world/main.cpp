#include <GameEngine/GameEngine.h>
#include <GameEngine/core/load.h>
#include <iostream>

using namespace std;

class Game : public GameEngine::Module
{
public:
    // TODO: Easier 2D Renderer (direct-access or wrapper)
    void init()
    {
        GameEngine::LOG::DEBUG("GameModule", "Hello");
        engine->me.add(GameEngine::MEDIA::ACTION::PRINT, (std::string) "Hello");

        tex = GameEngine::LOAD::Image("res/milk.png");
        engine->me.add(GameEngine::MEDIA::ACTION::ADD_TEXTURE, std::pair<std::string, GameEngine::texture>("tex", tex));
    }

    void update(float deltaTime)
    {
        // printf("%f\n", 1.0f / deltaTime);
        engine->me.add(GameEngine::MEDIA::ACTION::CLEAR, GameEngine::vec3(1.0f, 0.4f, 0.0f));
        engine->me.add(GameEngine::MEDIA::ACTION::DRAW_TEXTURE, std::tuple<std::string, GameEngine::vec2, GameEngine::vec2, float>("tex", GameEngine::vec2(0.0f, 0.0f), GameEngine::vec2(0.5f, 0.5f), GameEngine::time() * 90.0f));
    }

private:
    GameEngine::texture tex;
};

int main()
{
    GameEngine::GameEngine engine("Hello World", false);

    engine.add(new Game());

    GameEngine::LOG::DEBUG("Main", "Hello");

    engine.start();

    return 0;
}