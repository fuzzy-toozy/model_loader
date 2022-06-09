#pragma once

#include <string>

#include <GL/gl.h>

namespace ShaderTool {

class Shader
{
    public:

        using HandleType = GLuint;
        using ShaderType = GLuint;

        Shader(const GLuint, const std::string&);
        ~Shader();

        GLuint GetType()
        {
            return m_type;
        }

        void Attach(GLint);
        void Delete();

    private:

        bool Create(const std::string&);

        ShaderType m_type;
        HandleType m_handle;
};

} // namespace ShaderTool