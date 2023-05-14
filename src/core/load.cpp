#include <GameEngine/core/load.h>

#include <GameEngine/utility/

namespace GameEngine::LOAD
{
    void image(std::string path)
    {
        int width, height, nrChannels;
        unsigned char *data = stbi_load((PATH_TEXTURE + path).c_str(), &width, &height, &nrChannels, 0);
    }

    void shader()
    {
    }

    void mesh()
    {
    }
}