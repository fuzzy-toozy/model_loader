#include <exception>
#include <iostream>
#include <cstdio>

#include <graphic_control/program.h>

namespace {
void SetDirLight(const ShaderTool::Program& prog, const glm::vec4& dir,
                 const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& color)
{
    constexpr auto bufsz = 128u;
    char buf[bufsz];
    auto offset = snprintf(buf, bufsz, "dirLight.");
    char* name_pos = buf + offset;

    auto prog_handle = prog.GetHadle();

    snprintf(name_pos, bufsz, "direction");
    auto loc = glGetUniformLocation(prog_handle, buf);
    glUniform4fv(loc, 1, glm::value_ptr(dir));

    snprintf(name_pos, bufsz, "ambient");
    loc = glGetUniformLocation(prog_handle, buf);
    glUniform3fv(loc, 1, glm::value_ptr(ambient));

    snprintf(name_pos, bufsz, "diffuse");
    loc = glGetUniformLocation(prog_handle, buf);
    glUniform3fv(loc, 1, glm::value_ptr(diffuse));

    snprintf(name_pos, bufsz, "specular");
    loc = glGetUniformLocation(prog_handle, buf);
    glUniform3fv(loc, 1, glm::value_ptr(specular));

    snprintf(name_pos, bufsz, "color");
    loc = glGetUniformLocation(prog_handle, buf);
    glUniform3fv(loc, 1, glm::value_ptr(color));
}

}

void GLAPIENTRY
MessageCallback( GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar* message,
                const void* userParam )
{
    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
    throw std::runtime_error(message);
}

namespace graphic_control
{

bool Program::Init(bool hide_window)
{
    try {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* desktop = glfwGetVideoMode(monitor);
        GLuint64 screenWidth = 800;
        GLuint64 screenHeight = 600;
        m_window = glfwCreateWindow(screenWidth, screenHeight, "ModelViewer", nullptr, nullptr);
        if (hide_window) {
            glfwHideWindow(m_window);
        }
        if (m_window == nullptr) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }

        m_camera = std::make_unique<camera::FPCamera>(m_window);
        m_camera->SetScreen(screenWidth, screenHeight);

        glfwMakeContextCurrent(m_window);

        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        glewExperimental = GL_TRUE;

        if (glewInit() != GLEW_OK)
        {
            std::cout << "Failed to initialize GLEW" << std::endl;
            return -1;
        }

        glViewport(0, 0, screenWidth, screenHeight);

        glEnable(GL_DEPTH_TEST);
        glEnable ( GL_DEBUG_OUTPUT );
        glDebugMessageCallback( MessageCallback, 0 );

        GLint nrAttributes;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
        std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes
                  << std::endl;
        m_shaders = std::make_unique<ShaderTool::Program>();
    } catch (const std::exception& ex) {
        std::cerr << "Failed to init program: " << ex.what() << std::endl;
        return false;
    }
    
    return true;
}

void Program::AddLocalTransform(glm::mat4 local_trans)
{
    m_local_trans.push_back(local_trans);
}


void Program::MainLoop(const std::function<void(ShaderTool::Program &)> &draw_func)
{
    glfwMakeContextCurrent(m_window);
    camera::FPCamera& camera = *m_camera;
    ShaderTool::Program& program = *m_shaders;
    glm::vec4 light_dir{0, -1, 0, 1};
    glm::vec3 light_color{1, 1, 1};
    glm::vec3 ambient{0.3f, 0.3f, 0.3};
    glm::vec3 diffuse{1.f, 1.0f, 1.0f};
    glm::vec3 specular{1.f, 1.f, 1.f};

    while(!glfwWindowShouldClose(m_window)) {
        camera.OnFrameChange();

        glfwPollEvents();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_STENCIL_TEST);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const auto& proj = camera.GetProjectMatrix();
        const auto& view = camera.GetViewMatrix();

        auto model = glm::mat4(1.f);

        program.Use();

        auto prog_handle = program.GetHadle();

        model *= glm::translate(glm::mat4(1.f), glm::vec3(0.0f, -1.f, -5.f)); // Translate it down a bit so it's at the center of the scene

        // Apply before translation (mathematically)
        for (const auto& trans : m_local_trans) {
            model *= trans;
        }

        //model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        glm::mat3 normal = glm::transpose(glm::inverse(glm::mat3(view * model)));

        auto loc = glGetUniformLocation(prog_handle, "normal_trans");
        glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(normal));

        loc = glGetUniformLocation(prog_handle, "model");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));

        loc = glGetUniformLocation(prog_handle, "projection");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(proj));

        loc = glGetUniformLocation(prog_handle, "view");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(view));

        SetDirLight(program, light_dir, ambient, diffuse, specular, light_color);

        draw_func(program);

        glfwSwapBuffers(m_window);

        if (m_stop.load()) {
            break;
        }
    }

    m_stop.store(false);
}

void Program::TakeScreenshot(const std::filesystem::path& filename)
{
    m_camera->TakeScreenshot(filename);
}

void Program::Stop()
{
    m_stop.store(true);
}

bool Program::AddShaders(const std::list<std::pair<GLuint, std::string>>& shaders)
{
    try {
        m_shaders->AttachShaders(shaders);
        m_shaders->Link();
    } catch (const std::exception& ex) {
        std::cerr << "Failed attaching shaders: " << ex.what() << std::endl;
        return false;
    }

    return true;
}

bool Program::LoadModel(const std::filesystem::path& path)
{
    try {
        m_model = std::make_unique<model::Model>(path);
    } catch (const std::exception& ex) {
        std::cerr << "Failed loading model: " << ex.what() << std::endl;
        return false;
    }

    return true;
}

bool Program::RunMainLoop()
{
    try {
        MainLoop([this](ShaderTool::Program& prog) { m_model->Draw(prog);});
    } catch (const std::exception& ex) {
        std::cerr << "Error in main loop!" << ex.what() << std::endl;
        return false;
    }

    return true;
}

} // grahic_control
