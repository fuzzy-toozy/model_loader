#pragma once

#include <vector>
#include <filesystem>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <shader_tool/program.h>

namespace model
{

enum class LightType
{
    DIFFUSE,
    SPECULAR
};

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture_coords;
};

struct Texture
{
    GLuint id;
    LightType type;
    std::filesystem::path path;
};

using Vertices = std::vector<Vertex>;
using Indicies = std::vector<GLuint>;
using Textures = std::vector<Texture>;

class Mesh
{
    public:

        Mesh(const Vertices&, const Indicies&, const Textures&);
        Mesh(Vertices&&, Indicies&&, Textures&&);

        void Draw(const ShaderTool::Program&);
        void SetupMesh();

        const Vertices& GetVerticies() const { return m_verticies; }
        const Indicies& GetIndicies() const { return m_indicies; }
        const Textures& GetTextures() const { return m_textures; }

    private:
        Vertices m_verticies;
        Textures m_textures;
        Indicies m_indicies;
        GLuint m_vao, m_vbo, m_ebo;

};

}