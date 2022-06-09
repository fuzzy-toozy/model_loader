// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <SOIL/SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <iostream>
#include <cmath>
#include <tuple>
#include <cassert>

#include <cstdlib> 
#include <ctime>

#include <shader_tool/shader_tool.h>
#include <shader_tool/program.h>
#include <camera/fp_camera.h>
#include <modeling/model.h>

GLuint make_vao(GLfloat* vertices, size_t v_len, GLuint* indices = nullptr, size_t i_len = 0)
{
    assert(vertices != nullptr);
    assert(v_len > 0);

    if (indices != nullptr) {
        assert(i_len > 0);
    }

    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(*vertices) * v_len, vertices, GL_STATIC_DRAW);

    if (indices) {
        GLuint EBO;
        glGenBuffers(1, &EBO);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*indices) * i_len, indices, GL_STATIC_DRAW);
    }

    return VAO;
}

std::tuple<int, int, GLuint> make_texture(const std::string& texture_path)
{
    int width, height;

    unsigned char* image = SOIL_load_image(texture_path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

    std::cerr << "IMAGE: " << (size_t)image << std::endl;

    GLuint texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    return {width, height, texture};
}

void DrawCube(const ShaderTool::Program& prog, const glm::vec3& color,
const glm::vec3& trans_pos, const glm::mat4& view, const glm::mat4& scale, const glm::mat4& project)
{
        glm::mat4 trans_light(1.f);
        trans_light = glm::translate(trans_light, trans_pos);

        auto loc = glGetUniformLocation(prog.GetHadle(), "translate");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(trans_light));

        loc = glGetUniformLocation(prog.GetHadle(), "scale");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(scale));

        loc = glGetUniformLocation(prog.GetHadle(), "view");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(view));

        loc = glGetUniformLocation(prog.GetHadle(), "projection");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(project));

        loc = glGetUniformLocation(prog.GetHadle(), "cube_color");
        glUniform3fv(loc, 1, glm::value_ptr(color));

        glDrawArrays(GL_TRIANGLES, 0, 36);
}

void SetDirLight(const ShaderTool::Program& prog, const glm::vec4& dir,
const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& color)
{
    const auto bufsz = 128u;
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

void SetPointLight(const ShaderTool::Program& prog, size_t id, const glm::vec4& pos, float constant, float linear, float quadratic,
const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& color)
{
    const auto bufsz = 128u;
    char buf[bufsz];
    auto offset = snprintf(buf, bufsz, "pointLights[%lu].", id);
    char* name_pos = buf + offset;

    auto prog_handle = prog.GetHadle();

    snprintf(name_pos, bufsz, "position");
    auto loc = glGetUniformLocation(prog_handle, buf);
    glUniform4fv(loc, 1, glm::value_ptr(pos));

    snprintf(name_pos, bufsz, "constant");
    loc = glGetUniformLocation(prog_handle, buf);
    glUniform1f(loc, constant);

    snprintf(name_pos, bufsz, "linear");
    loc = glGetUniformLocation(prog_handle, buf);
    glUniform1f(loc, linear);

    snprintf(name_pos, bufsz, "quadratic");
    loc = glGetUniformLocation(prog_handle, buf);
    glUniform1f(loc, quadratic);

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

void SetSpotLight(const ShaderTool::Program& prog, const glm::vec4& pos,  const glm::vec4& dir, float cutoff, float outcutoff, float constant, float linear, float quadratic,
const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& color)
{
    const auto bufsz = 128u;
    char buf[bufsz];
    auto offset = snprintf(buf, bufsz, "spotLight.");
    char* name_pos = buf + offset;

    auto prog_handle = prog.GetHadle();

    snprintf(name_pos, bufsz, "position");
    auto loc = glGetUniformLocation(prog_handle, buf);
    glUniform4fv(loc, 1, glm::value_ptr(pos));

    snprintf(name_pos, bufsz, "direction");
    loc = glGetUniformLocation(prog_handle, buf);
    glUniform4fv(loc, 1, glm::value_ptr(dir));

    snprintf(name_pos, bufsz, "cutoff");
    loc = glGetUniformLocation(prog_handle, buf);
    glUniform1f(loc, cutoff);

    snprintf(name_pos, bufsz, "outcutoff");
    loc = glGetUniformLocation(prog_handle, buf);
    glUniform1f(loc, outcutoff);

    snprintf(name_pos, bufsz, "constant");
    loc = glGetUniformLocation(prog_handle, buf);
    glUniform1f(loc, constant);

    snprintf(name_pos, bufsz, "linear");
    loc = glGetUniformLocation(prog_handle, buf);
    glUniform1f(loc, linear);

    snprintf(name_pos, bufsz, "quadratic");
    loc = glGetUniformLocation(prog_handle, buf);
    glUniform1f(loc, quadratic);

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

struct Attenuation
{
    float constant;
    float linear;
    float quadratic;
};

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* desktop = glfwGetVideoMode(monitor);
    GLuint64 screenWidth = desktop->width;
    GLuint64 screenHeight = desktop->height;

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)  
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glViewport(0, 0, screenWidth, screenHeight);

    float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    GLuint vao1 = make_vao(vertices, sizeof(vertices) / sizeof(vertices[0]));

    glBindVertexArray(vao1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    ShaderTool::Program prog1;
    prog1.AttachShaders(
        {
            { GL_VERTEX_SHADER, VERTEX_SHADERS_DIR + std::string("multiple_lights.vert") },
            { GL_FRAGMENT_SHADER, FRAGMENT_SHADERS_DIR + std::string("multiple_lights.frag") }
        }
    );
    prog1.Link();

    ShaderTool::Program prog2;
    prog2.AttachShaders(
        {
            { GL_VERTEX_SHADER, VERTEX_SHADERS_DIR + std::string("simple2.vert") },
            { GL_FRAGMENT_SHADER, FRAGMENT_SHADERS_DIR + std::string("simple2.frag") }
        }
    );
    prog2.Link();

    ShaderTool::Program prog3;
    prog3.AttachShaders({
        {GL_VERTEX_SHADER, VERTEX_SHADERS_DIR + std::string("simple_color.vert")},
        {GL_FRAGMENT_SHADER, FRAGMENT_SHADERS_DIR + std::string("simple_color.frag")}
    });
    prog3.Link();


    glEnable(GL_DEPTH_TEST);

    GLint nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes
    << std::endl;

    GLfloat lastTime = glfwGetTime();
    int nbFrames = 0;

    GLfloat lastFrame = 0.f;

    
    camera::FPCamera camera(window);
    camera.SetScreen(screenWidth, screenHeight);

    model::Model loaded_model1(MODELS_DIR + std::string("nano/scene.fbx"));

    GLfloat quadVertices[] = {   // Vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // Positions   // TexCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    GLuint quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glBindVertexArray(0);

    //lPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(!glfwWindowShouldClose(window)) {
        camera.OnFrameChange();

        glfwPollEvents();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_STENCIL_TEST);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const auto& proj = camera.GetProjectMatrix();
        const auto& view = camera.GetViewMatrix();


        prog2.Use();
        glBindVertexArray(vao1);
        
        auto model = glm::mat4(1.f);

        prog1.Use();

        auto prog_handle = prog1.GetHadle();

        model = glm::mat4(1.f);
        model = glm::translate(model, glm::vec3(0.0f, -2.0f, -0.1f)); // Translate it down a bit so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down

        glm::mat3 normal = glm::transpose(glm::inverse(glm::mat3(view * model)));

        auto loc = glGetUniformLocation(prog_handle, "normal_trans");
        glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(normal));

        loc = glGetUniformLocation(prog_handle, "model");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));

        loc = glGetUniformLocation(prog_handle, "projection");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(proj));

        loc = glGetUniformLocation(prog_handle, "view");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(view));

        glm::vec3 ambient{0.3f, 0.3f, 0.3};
        glm::vec3 diffuse{1.f, 1.0f, 1.0f};
        glm::vec3 specular{1.f, 1.f, 1.f};
        SetDirLight(prog1, glm::vec4(0, -1, 0, 1), ambient, glm::vec3(2,2,2), specular, glm::vec3(1, 1, 1));

        loaded_model1.Draw(prog1);

        prog1.Use();

        auto view1 = camera.GetViewFromRotation(0, 180.f);

        prog_handle = prog1.GetHadle();

        loc = glGetUniformLocation(prog_handle, "view");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(view1));
        
        loaded_model1.Draw(prog1);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;

}
