#pragma once

#include <stdexcept>
#include <string>

namespace ShaderTool
{
    class ShaderLoadException : public std::runtime_error
    {
        public:
            ShaderLoadException(const std::string& msg) : std::runtime_error(msg)
            {}
    };

    class ProgramLinkException : public std::runtime_error
    {
        public:
            ProgramLinkException(const std::string& msg) : std::runtime_error(msg)
            {}
    };
}