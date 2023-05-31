#include <Graphite/core/load.h>

#include <fstream>

namespace Graphite::LOAD {

std::string Text(std::string path, std::string ext) {
    if (path == "")
        return "";

    std::ifstream file(path);
    std::string out;

    // Open File
    if (!file.is_open()) {
        if (ext == "")
            return "";
        else {
            file.open(path + ext);
            if (!file.is_open())
                return "";
        }
    }

    // Copy Data
    std::string line;
    while (getline(file, line))
        out += line + "\n";

    file.close();

    return out;
}

texture Image(std::string path) {
    texture out;
    stbi_set_flip_vertically_on_load(1);
    out.data =
        stbi_load(path.c_str(), &out.width, &out.height, &out.nrChannels, 0);

    if (!out.data)
        LOG::WARNING("Image", "Failed to load Image (%s)", path.c_str());

    return out;
}

shader Shader(std::string vertex_path, std::string fragment_path,
              std::string geometry_path) {
    shader out;

    out.vertex = Text(vertex_path);
    out.fragment = Text(fragment_path);
    out.geometry = Text(geometry_path);

    return out;
}

shader Shader(std::string path) { return Shader(path, path, path); }

mesh Mesh() {
    mesh m;

    return m;
}

} // namespace Graphite::LOAD