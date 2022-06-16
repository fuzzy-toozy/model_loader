#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <list>
#include <string>

namespace ShaderTool
{
    enum class LogType : uint8_t
    {
        PROGRAM,
        SHADER
    };

    void LogFailure(const LogType log_type, GLuint object_id);

    bool LoadShader(GLuint program, GLuint shader_type, const std::string& shader_file_path);
    void LoadShaders(GLuint program, const std::list<std::pair<GLuint, std::string>>& shaders);
}