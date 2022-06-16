#include <shader_tool/shader_tool.h>

#include <iostream>
#include <fstream>

namespace ShaderTool
{

void LogFailure(const LogType log_type, GLuint object_id)
{
    static char logbuf[512];

    switch (log_type)
    {
        case LogType::PROGRAM:
            glGetProgramInfoLog(object_id, sizeof(logbuf), NULL, logbuf);
            std::cerr << "Program linking failed" << std::endl << "Error: " << logbuf;
        break;

        case LogType::SHADER:
            glGetShaderInfoLog(object_id, sizeof(logbuf), NULL, logbuf);
            std::cerr << "Shader compiling failed" << std::endl
                  << "Error: " << logbuf;
        break;

        default:
            throw std::runtime_error("Wrong log type!");
    }
}

bool LoadShader(GLuint program, GLuint shader_type, const std::string& shader_file_path)
{
    std::string temp = "";
    std::string src = "";
    std::ifstream in_file;

    in_file.open(shader_file_path);

    if (in_file.is_open()) {
        while(std::getline(in_file, temp)) {
            src += temp + "\n";
        }
    } else {
        std::cerr << "Couldn't open shader file: " << shader_file_path << std::endl;
        return false;
    }

    in_file.close();

    GLuint new_shader = glCreateShader(shader_type);

    if (new_shader == 0) {
        std::cerr << "Couldn't create shader: " << shader_file_path << std::endl;
        return false;
    }

    const GLchar* shaderCode = src.c_str();

    glShaderSource(new_shader, 1, &shaderCode, NULL);
    glCompileShader(new_shader);

    GLint success = 0;
    glGetShaderiv(new_shader, GL_COMPILE_STATUS, &success);

    if (! success) {
        std::cerr << "Error compiling shader: " << shader_file_path << std::endl;
        LogFailure(LogType::SHADER, new_shader);
        return false;
    }

    glAttachShader(program, new_shader);
    glDeleteShader(new_shader);

    return true;
}

void LoadShaders(GLuint program, const std::list<std::pair<GLuint, std::string>>& shaders)
{
    for (const auto& shader_data : shaders) {
        if (! LoadShader(program, shader_data.first, shader_data.second)) {
            glfwTerminate();
            throw std::runtime_error("Failed to compile shaders");
        }
    }

    glLinkProgram(program);

    GLint success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(! success) {
        LogFailure(LogType::PROGRAM, program);
        glfwTerminate();
        throw std::runtime_error("Failed to link program");
    }
}

}
