#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>
#include <assimp/material.h>

#include <SOIL/SOIL.h>

#include <modeling/model.h>

namespace model
{

Model::Model(const std::filesystem::path& path)
{
    if (loadModel(path)) {
        std::cout << "Model " << path << " loaded" << std::endl;
    } else {
        throw std::runtime_error("Model loading failed!");
    }
}

void Model::Draw(const ShaderTool::Program& prog)
{
    std::for_each(std::begin(m_meshes), std::end(m_meshes), [&prog](Mesh& m){ m.Draw(prog); });
}

bool Model::loadModel(const std::filesystem::path& path)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);
    if( !scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return false;
    }
    const auto& path_str = path.string();
    m_path = path_str.substr(0, path_str.find_last_of('/'));
    processNode(scene->mRootNode, scene);
    return true;
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for(GLuint i = 0; i < node->mNumMeshes; ++i) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(processMesh(mesh, scene));
    }

    for(GLuint i = 0; i < node->mNumChildren; ++i) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    Vertices vertices;
    Indicies indices;
    Textures textures;

    for(GLuint i = 0; i < mesh->mNumVertices; ++i) {
        Vertex vertex;
        const auto& mesh_vert = mesh->mVertices[i];
        vertex.position.x = mesh_vert.x;
        vertex.position.y = mesh_vert.y;
        vertex.position.z = mesh_vert.z;

        if (mesh->mNormals) {
            const auto& mesh_normal = mesh->mNormals[i];
            vertex.normal.x = mesh_normal.x;
            vertex.normal.y = mesh_normal.y;
            vertex.normal.z = mesh_normal.z;
        }

        if(mesh->mTextureCoords[0]) {
            const auto& texture = mesh->mTextureCoords[0][i];
            vertex.texture_coords.x = texture.x;
            vertex.texture_coords.y = texture.y;
        } else {
            vertex.texture_coords.x = 0;
            vertex.texture_coords.y = 0;
        }

        vertices.push_back(std::move(vertex));
    }

    for(GLuint i = 0; i < mesh->mNumFaces; ++i) {
        aiFace& face = mesh->mFaces[i];
        for(GLuint j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }
    
    if(mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        loadMaterialTextures(material, aiTextureType_DIFFUSE, textures);
        loadMaterialTextures(material, aiTextureType_AMBIENT, textures);
        loadMaterialTextures(material, aiTextureType_SPECULAR, textures);
    }

    return Mesh(std::move(vertices), std::move(indices), std::move(textures));
}

GLuint Model::loadTexture(const std::filesystem::path& path)
{
    int width, height;

    unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

    if (!image) {
        throw std::runtime_error("Soil failed loading texture");
    }

    GLuint texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}


void Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, Textures& textures)
{
    for(GLuint i = 0; i < mat->GetTextureCount(type); ++i) {
        aiString str;
        mat->GetTexture(type, i, &str);
        std::string char_path = str.C_Str();
        std::replace(std::begin(char_path), std::end(char_path), '\\', '/');
        std::filesystem::path p = char_path;
        const auto& texture_path = m_path / "textures" / p.filename();
        const auto& it = m_loaded_textures.find(texture_path);
        if (it != std::end(m_loaded_textures)) {
            textures.push_back(*it->second);
        } else {
            Texture texture;
            texture.id = loadTexture(texture_path);
            texture.type = (type == aiTextureType_DIFFUSE) ? LightType::DIFFUSE : LightType::SPECULAR;
            texture.path = str.C_Str();
            textures.push_back(std::move(texture));
            m_loaded_textures.insert({texture_path, &textures.back()});
        }
    }
}

} // namespace model