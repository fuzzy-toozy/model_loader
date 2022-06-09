#include <iostream>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <modeling/mesh.h>

namespace model
{

Mesh::Mesh(const Vertices& v, const Indicies& i, const Textures& t)
    : m_verticies(v),
      m_textures(t),
      m_indicies(i)

{
    SetupMesh();
    std::cout << "Vert " << m_verticies.size() << " Indices: " << m_indicies.size() << " Textures: " << m_textures.size() << std::endl;
}

Mesh::Mesh(Vertices&& v, Indicies&& i, Textures&& t)
    : m_verticies(std::move(v)),
      m_textures(std::move(t)),
      m_indicies(std::move(i))
{
    SetupMesh();
    std::cout << "Vert " << m_verticies.size() << " Indices: " << m_indicies.size() << " Textures: " << m_textures.size() << std::endl;
}

void Mesh::SetupMesh()
{
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    
    glBufferData(GL_ARRAY_BUFFER, m_verticies.size() * sizeof(Vertex), m_verticies.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicies.size() * sizeof(GLuint), m_indicies.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<GLvoid*>(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, normal)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, texture_coords)));

    glBindVertexArray(0);
}

void Mesh::Draw(const ShaderTool::Program& prog)
{
    GLuint diffuse_nb = 1;
    GLuint specular_nb = 1;

    const auto bufsz = 128u;
    char buf[bufsz];
    auto offset = snprintf(buf, bufsz, "texture_");
    char* name_pos = buf + offset;
    for(GLuint i = 0; i < m_textures.size(); ++i)
    {
        glActiveTexture(GL_TEXTURE0 + i);

        if (m_textures[i].type == LightType::DIFFUSE) {
            snprintf(name_pos, bufsz, "diffuse%u", diffuse_nb++);
        } else if (m_textures[i].type == LightType::SPECULAR) {
            snprintf(name_pos, bufsz, "specular%u", specular_nb++);
        }

        glUniform1f(glGetUniformLocation(prog.GetHadle(), buf), i);
        glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
    }

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_indicies.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    for (GLuint i = 0; i < m_textures.size(); ++i)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

} 