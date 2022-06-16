#include <graphic_control/program.h>

#include <iostream>

int main()
{

    graphic_control::Program program;
    if (!program.Init()) {
        return -1;
    }

    if (! program.AddShaders( {
        { GL_VERTEX_SHADER, VERTEX_SHADERS_DIR + std::string("multiple_lights.vert") },
        { GL_FRAGMENT_SHADER, FRAGMENT_SHADERS_DIR + std::string("multiple_lights.frag") }
        })) {
        return -1;
    }

    if (! program.LoadModel(MODELS_DIR + std::string("eve/Evelynn.fbx"))) {
        return -1;
    }

    //program.AddLocalTransform(glm::rotate(glm::mat4(1.f), 0.5f, glm::vec3(0.0f, 1.0f, 0.f)));

    if (! program.RunMainLoop()) {
        std::cerr << "Main loop exited abnormally" << std::endl;
        return -1;
    }

    return 0;
}
