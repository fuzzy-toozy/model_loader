#include <iostream>
#include <fstream>

#include <shader_tool/shader_tool.h>
#include <shader_tool/shader.h>
#include <shader_tool/exceptions.h>

namespace ShaderTool
{

Shader::Shader(const ShaderType type) :
    m_type(type)
{
}

Shader::~Shader()
{
    Delete();
}

void Shader::Delete()
{
    if (m_handle > 0) {
        glDeleteShader(m_handle);
    }
    m_handle = 0;
}

void Shader::Attach(GLint program)
{
    glAttachShader(program, m_handle);
}


void Shader::Create(const std::string& sources_file_path)
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
        throw ShaderLoadException("Failed to open shader file: " + sources_file_path);
    }

    in_file.close();

    m_handle = glCreateShader(m_type);

    if (m_handle == 0) {
        std::cerr << "Couldn't create shader: " << sources_file_path << std::endl;
        throw ShaderLoadException("Failed to create shader: " + sources_file_path);
    }

    const GLchar* shader_code = src.c_str();

    glShaderSource(m_handle, 1, &shader_code, NULL);
    glCompileShader(m_handle);

    GLint success = 0;
    glGetShaderiv(m_handle, GL_COMPILE_STATUS, &success);

    if (! success) {
        std::cerr << "Error compiling shader: " << sources_file_path << std::endl;
        LogFailure(LogType::SHADER, m_handle);
        throw ShaderLoadException("Failed to compile shader: " + sources_file_path);
    }
}

} // namespace ShaderTool
