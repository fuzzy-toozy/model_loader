#include <iostream>
#include <fstream>

#include <shader_tool/shader_tool.h>
#include <shader_tool/shader.h>
#include <shader_tool/exceptions.h>

namespace ShaderTool
{

Shader::Shader(const ShaderType type, const std::string& sources_file_path) :
    m_type(type)
{
    if (! Create(sources_file_path)) {
        throw ShaderLoadException("Failed to create shader: " + sources_file_path);
    }
}

Shader::~Shader()
{
    glDeleteShader(m_handle);
}

void Shader::Delete()
{
    glDeleteShader(m_handle);
    m_handle = 0;
}

void Shader::Attach(GLint program)
{
    glAttachShader(program, m_handle);
}


bool Shader::Create(const std::string& sources_file_path)
{
    std::string temp = "";
    std::string src = "";
    std::ifstream in_file;

    in_file.open(sources_file_path);

    if (in_file.is_open()) {
        while(std::getline(in_file, temp)) {
            src += temp + "\n";
        }
    } else {
        std::cerr << "Couldn't open shader file: " << sources_file_path << std::endl;
        return false;
    }

    in_file.close();

    m_handle = glCreateShader(m_type);

    if (m_handle == 0) {
        std::cerr << "Couldn't create shader: " << sources_file_path << std::endl;
        return false;
    }

    const GLchar* shader_code = src.c_str();

    glShaderSource(m_handle, 1, &shader_code, NULL);
    glCompileShader(m_handle);

    GLint success = 0;
    glGetShaderiv(m_handle, GL_COMPILE_STATUS, &success);

    if (! success) {
        std::cerr << "Error compiling shader: " << sources_file_path << std::endl;
        LogFailure(LogType::SHADER, m_handle);
        return false;
    }

    return true;
}

} // namespace ShaderTool