// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <SOIL/SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstdint>
#include <exception>
#include <utility>
#include <memory>
#include <list>
#include <functional>
#include <atomic>

#include <shader_tool/program.h>
#include <camera/fp_camera.h>
#include <modeling/model.h>

namespace graphic_control
{

class Program
{
public:
    Program(uint32_t major_v = 3, uint32_t minor_v = 3) 
    : m_major_v(major_v), m_minor_v(minor_v)
    {}

    ~Program() {
        glfwTerminate();
        glfwDestroyWindow(m_window);
    }

    bool Init(bool hide_window = false);

    bool AddShaders(const std::list<std::pair<GLuint, std::string>>& shaders);

    bool LoadModel(const std::filesystem::path& path);

    bool RunMainLoop();

    void AddLocalTransform(glm::mat4 local_trans);

    void TakeScreenshot(const std::filesystem::__cxx11::path &filename);

    void Stop();

    camera::FPCamera& GetCamera() {
        return *m_camera;
    }

    void MainLoop(const std::function<void(ShaderTool::Program &)> &draw_func);
private:

    std::vector<glm::mat4> m_local_trans;
    GLFWwindow* m_window{};
    std::unique_ptr<ShaderTool::Program> m_shaders;
    std::unique_ptr<camera::FPCamera> m_camera;
    std::unique_ptr<model::Model> m_model;
    uint32_t m_major_v;
    uint32_t m_minor_v;
    std::atomic<bool> m_stop{false};
};

} // graphic_control
