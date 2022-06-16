#pragma once

#include <filesystem>
#include <unordered_map>

#include <assimp/mesh.h>
#include <assimp/scene.h>

#include <modeling/mesh.h>

namespace model
{

struct PathHash
{
    std::size_t operator()(const std::filesystem::path& path) const noexcept
    {
        return std::filesystem::hash_value(path);
    }
};

using LoadedTextures = std::unordered_map<std::filesystem::path, Texture*, PathHash>;
using Meshes = std::vector<Mesh>;

class Model
{
    public:
        Model(const std::filesystem::path& path);
        void Draw(const ShaderTool::Program& prog);
        static GLuint loadTexture(const std::filesystem::path& path);
    private:

        bool loadModel(const std::filesystem::path& path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        void loadMaterialTextures(aiMaterial* mat, aiTextureType type, Textures& textures);

        Meshes m_meshes;
        LoadedTextures m_loaded_textures;
        std::filesystem::path m_path;
};

}
