#include <GL/glew.h>

#include <shader_tool/program.h>
#include <shader_tool/shader_tool.h>
#include <shader_tool/exceptions.h>

namespace ShaderTool
{

    Program::Program()
    {
        m_handle = glCreateProgram();
    }

    void Program::AttachShader(Shader shader)
    {
        shader.Attach(m_handle);
    }

    void Program::AttachShaders(const std::list<std::pair<GLuint, std::string>>& shaders)
    {
        for (const auto& [shader_type, shader_source_path] : shaders) {
            ShaderTool::Shader new_shader(shader_type);
            new_shader.Create(shader_source_path);
            AttachShader(new_shader);
        }
    }

    void Program::Use()
    {
        glUseProgram(m_handle);
    }

    void Program::Link()
    {
        glLinkProgram(m_handle);

        GLint success = 0;
        glGetProgramiv(m_handle, GL_LINK_STATUS, &success);

        if(! success) {
            LogFailure(LogType::PROGRAM, m_handle);
            glfwTerminate();
            throw ProgramLinkException("Failed to link program");
        }
    }

} // namespace ShaderTool
