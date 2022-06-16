#pragma once

#include <string>

#include <GL/gl.h>

namespace ShaderTool {

class Shader
{
    public:

        using HandleType = GLuint;
        using ShaderType = GLuint;

        Shader(const GLuint);
        ~Shader();

        GLuint GetType()
        {
            return m_type;
        }

        HandleType GetHandle() {
            return m_handle;
        }

        void Attach(GLint);
        void Create(const std::string&);
        void Delete();

    private:
        ShaderType m_type;
        HandleType m_handle;
};

} // namespace ShaderTool
