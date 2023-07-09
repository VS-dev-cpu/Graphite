#include <Graphite/Engine.hpp>

#include <Graphite/core/ResourceManager.hpp>

using namespace std;

class Game : public Graphite::Module {
  public:
    // TODO: Better 2D UI Support
    void init() {
        log_debug("GameModule", "Hello");
        // engine->me.add(Graphite::ACTION::PRINT, (std::string) "Hello");

        // tex = Graphite::LOAD::Image("res/milk.png");
        // engine->me.add(Graphite::ACTION::ADD_TEXTURE,
        //               std::pair<std::string, Graphite::Texture>("tex", tex));
    }

    void update(float deltaTime) {
        // printf("fps: %f\n", 1.0f / deltaTime);
        // engine->me.add(Graphite::ACTION::CLEAR,
        //                Graphite::vec3(1.0f, 0.4f, 0.0f));
        // engine->me.add(
        //     Graphite::ACTION::DRAW_TEXTURE,
        //     std::tuple<std::string, Graphite::vec2,
        //     Graphite::vec2, float>(
        //         "tex", Graphite::vec2(0.0f, 0.0f),
        //         Graphite::vec2(0.5f, 0.5f), Graphite::time()
        //         * 90.0f));
    }

  private:
    Graphite::Texture tex;
};

int main() {
    Graphite::Engine engine("Hello Graphite", false);

    engine.add(new Game());

    log_debug("Main", "Hello");

    engine.start();

    return 0;
}