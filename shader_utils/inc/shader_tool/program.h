#pragma once

#include <list>

#include <shader_tool/shader.h>

namespace ShaderTool
{
    class Program
    {
        public:
            Program();

            void Use();
            void Link();
            void AttachShader(Shader);
            void AttachShaders(const std::list<std::pair<GLuint, std::string>>& shaders);

            GLint GetHadle() const
            {
                return m_handle;
            }

        private:
            GLint m_handle;
    };
} // namespace ShaderTool