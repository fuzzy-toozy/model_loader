#include <graphic_control/program.h>

#include <gtest/gtest.h>

#include <iostream>
#include <filesystem>
#include <thread>
#include <iterator>
#include <fstream>
#include <ios>

namespace {
const std::filesystem::path gkVertexShadersDir = VERTEX_SHADERS_DIR;
const std::filesystem::path gkFragmentShadersDir = FRAGMENT_SHADERS_DIR;

const std::filesystem::path gkVertexShaderPath = gkVertexShadersDir / "multiple_lights.vert";
const std::filesystem::path gkFragmentShaderPath = gkFragmentShadersDir / "multiple_lights.frag";

const std::filesystem::path gkTestDataDir = TEST_DATA_DIR;

const std::string gkCubeShotFileName = "CubeMeshShot.tga";
const std::string gkModelShotFileName = "ModelMeshShot.tga";


bool CompareFiles(const std::filesystem::path& lhs,
                  const std::filesystem::path& rhs) {
    std::ifstream lhs_file(lhs, std::ios::in | std::ios::binary);
    std::ifstream rhs_file(rhs, std::ios::in | std::ios::binary);
    std::istream_iterator<uint8_t> lhs_start(lhs_file), lhs_end;
    std::vector<uint8_t> lhs_data(lhs_start, lhs_end);
    std::istream_iterator<uint8_t> rhs_start(rhs_file), rhs_end;
    std::vector<uint8_t> rhs_data(rhs_start, rhs_end);
    if (!lhs_file.is_open()) {
        std::cerr << "Failed to open test file: " << lhs << std::strerror(errno) << std::endl;
        return false;
    }
    if (!rhs_file.is_open()) {
        std::cerr << "Failed to open test file: " << rhs << std::strerror(errno) << std::endl;
        return false;
    }
    // Loading both files to ram is expensive, but whatever
    if (lhs_data == rhs_data) {
        return true;
    }
    return false;
}

}


class ProgramTest : public ::testing::Test {
protected:
    void SetUp() override {
        m_program.Init(true);
    }

    graphic_control::Program m_program;
};

// Make sure vertex shader creates properly
TEST_F(ProgramTest, VertexShaderCreationAndDestruction) {
    ShaderTool::Shader vertex(GL_VERTEX_SHADER);
    EXPECT_EQ(vertex.GetType(), GL_VERTEX_SHADER);
    EXPECT_NO_THROW(vertex.Create(gkVertexShaderPath));
    EXPECT_NO_THROW(vertex.Delete());
}

// Make sure fragment shader creates properly
TEST_F(ProgramTest, FragmentShaderCreationAndDestruction) {
    ShaderTool::Shader fragment(GL_FRAGMENT_SHADER);
    EXPECT_EQ(fragment.GetType(), GL_FRAGMENT_SHADER);
    EXPECT_NO_THROW(fragment.Create(gkFragmentShaderPath));
    EXPECT_NO_THROW(fragment.Delete());
}

// Make sure vertex shader compiles
TEST_F(ProgramTest, VertexShaderLinking) {
    ShaderTool::Program program;
    ShaderTool::Shader vertex(GL_VERTEX_SHADER);
    vertex.Create(gkVertexShaderPath);
    program.AttachShader(vertex);
    EXPECT_NO_THROW(program.Link());
    EXPECT_NO_THROW(program.Use());
}

// Make sure fragment shader compiles
TEST_F(ProgramTest, FragmentShaderLinking) {
    ShaderTool::Program program;
    ShaderTool::Shader fragment(GL_FRAGMENT_SHADER);
    fragment.Create(gkFragmentShaderPath);
    program.AttachShader(fragment);
    EXPECT_NO_THROW(program.Link());
    EXPECT_NO_THROW(program.Use());
}

// Make sure that perspective and view matricies are calculated properly
TEST_F(ProgramTest, CameraTest) {
    auto& camera = m_program.GetCamera();
    camera.UpdateViewMatrix();

    const auto& direction = camera.GetDirection();

    const auto& world_y = glm::vec3(0.f,1.f, 0.f);
    const auto& m_camera_z = -direction;
    const auto& m_camera_x = glm::normalize(glm::cross(world_y, m_camera_z));
    const auto& m_camera_y = glm::cross(m_camera_z, m_camera_x);

    glm::mat4 rotation(1.f);

    rotation[0][0] = m_camera_x.x;
    rotation[1][0] = m_camera_x.y;
    rotation[2][0] = m_camera_x.z;
    rotation[0][1] = m_camera_y.x;
    rotation[1][1] = m_camera_y.y;
    rotation[2][1] = m_camera_y.z;
    rotation[0][2] = m_camera_z.x;
    rotation[1][2] = m_camera_z.y;
    rotation[2][2] = m_camera_z.z;

    const auto& world_pos = camera.GetPosition();

    glm::mat4 translation = glm::mat4(1.0f);

    translation[3][0] = -world_pos.x;
    translation[3][1] = -world_pos.y;
    translation[3][2] = -world_pos.z;

    const auto& view_transform = rotation * translation;

    EXPECT_TRUE(view_transform == camera.GetViewMatrix());
    const auto& perspective_transform = glm::perspective(glm::radians(camera.GetFov()), camera.GetAspect(), camera.GetZnear(), camera.GetZfar());
    EXPECT_TRUE(perspective_transform == camera.GetProjectMatrix());
}

// Just set up data for simple cube with simple texture for each face
// And then draw it, save rendered image to file and compare with golden data
TEST_F(ProgramTest, MeshTest) {
    std::vector<glm::vec3> positions = {
        // front
        {-1.0, -1.0,  1.0},
        {1.0, -1.0,  1.0},
        {1.0,  1.0,  1.0},
        {-1.0,  1.0,  1.0},
        // top
        {-1.0,  1.0,  1.0},
        {1.0,  1.0,  1.0},
        {1.0,  1.0, -1.0},
        {-1.0,  1.0, -1.0},
        // back
        {1.0, -1.0, -1.0},
        {-1.0, -1.0, -1.0},
        {-1.0,  1.0, -1.0},
        {1.0,  1.0, -1.0},
        // bottom
        {-1.0, -1.0, -1.0},
        {1.0, -1.0, -1.0},
        {1.0, -1.0,  1.0},
        {-1.0, -1.0,  1.0},
        // left
        {-1.0, -1.0, -1.0},
        {-1.0, -1.0,  1.0},
        {-1.0,  1.0,  1.0},
        {-1.0,  1.0, -1.0},
        // right
        {1.0, -1.0,  1.0},
        {1.0, -1.0, -1.0},
        {1.0,  1.0, -1.0},
        {1.0,  1.0,  1.0},
        };

        std::vector<glm::vec2> text_postions = {
            // front
            {0.0, 0.0},
            {1.0, 0.0},
            {1.0, 1.0},
            {0.0, 1.0},
            {0.0, 0.0},
            {1.0, 0.0},
            {1.0, 1.0},
            {0.0, 1.0},
            {0.0, 0.0},
            {1.0, 0.0},
            {1.0, 1.0},
            {0.0, 1.0},
            {0.0, 0.0},
            {1.0, 0.0},
            {1.0, 1.0},
            {0.0, 1.0},
            {0.0, 0.0},
            {1.0, 0.0},
            {1.0, 1.0},
            {0.0, 1.0},
            {0.0, 0.0},
            {1.0, 0.0},
            {1.0, 1.0},
            {0.0, 1.0},
            };

        std::vector<GLuint> indices = {
            // front
            0,  1,  2,
            2,  3,  0,
            // top
            4,  5,  6,
            6,  7,  4,
            // back
            8,  9, 10,
            10, 11,  8,
            // bottom
            12, 13, 14,
            14, 15, 12,
            // left
            16, 17, 18,
            18, 19, 16,
            // right
            20, 21, 22,
            22, 23, 20,
            // front
            0,  1,  2,
            2,  3,  0,
            // top
            4,  5,  6,
            6,  7,  4,
            // back
            8,  9, 10,
            10, 11,  8,
            // bottom
            12, 13, 14,
            14, 15, 12,
            // left
            16, 17, 18,
            18, 19, 16,
            // right
            20, 21, 22,
            22, 23, 20,
            // front
            0,  1,  2,
            2,  3,  0,
            // top
            4,  5,  6,
            6,  7,  4,
            // back
            8,  9, 10,
            10, 11,  8,
            // bottom
            12, 13, 14,
            14, 15, 12,
            // left
            16, 17, 18,
            18, 19, 16,
            // right
            20, 21, 22,
            22, 23, 20,
            // front
            0,  1,  2,
            2,  3,  0,
            // top
            4,  5,  6,
            6,  7,  4,
            // back
            8,  9, 10,
            10, 11,  8,
            // bottom
            12, 13, 14,
            14, 15, 12,
            // left
            16, 17, 18,
            18, 19, 16,
            // right
            20, 21, 22,
            22, 23, 20,
            // front
            0,  1,  2,
            2,  3,  0,
            // top
            4,  5,  6,
            6,  7,  4,
            // back
            8,  9, 10,
            10, 11,  8,
            // bottom
            12, 13, 14,
            14, 15, 12,
            // left
            16, 17, 18,
            18, 19, 16,
            // right
            20, 21, 22,
            22, 23, 20,
            // front
            0,  1,  2,
            2,  3,  0,
            // top
            4,  5,  6,
            6,  7,  4,
            // back
            8,  9, 10,
            10, 11,  8,
            // bottom
            12, 13, 14,
            14, 15, 12,
            // left
            16, 17, 18,
            18, 19, 16,
            // right
            20, 21, 22,
            22, 23, 20,
            // front
            0,  1,  2,
            2,  3,  0,
            // top
            4,  5,  6,
            6,  7,  4,
            // back
            8,  9, 10,
            10, 11,  8,
            // bottom
            12, 13, 14,
            14, 15, 12,
            // left
            16, 17, 18,
            18, 19, 16,
            // right
            20, 21, 22,
            22, 23, 20,
            // front
            0,  1,  2,
            2,  3,  0,
            // top
            4,  5,  6,
            6,  7,  4,
            // back
            8,  9, 10,
            10, 11,  8,
            // bottom
            12, 13, 14,
            14, 15, 12,
            // left
            16, 17, 18,
            18, 19, 16,
            // right
            20, 21, 22,
            22, 23, 20,
            // front
            0,  1,  2,
            2,  3,  0,
            // top
            4,  5,  6,
            6,  7,  4,
            // back
            8,  9, 10,
            10, 11,  8,
            // bottom
            12, 13, 14,
            14, 15, 12,
            // left
            16, 17, 18,
            18, 19, 16,
            // right
            20, 21, 22,
            22, 23, 20,
            // front
            0,  1,  2,
            2,  3,  0,
            // top
            4,  5,  6,
            6,  7,  4,
            // back
            8,  9, 10,
            10, 11,  8,
            // bottom
            12, 13, 14,
            14, 15, 12,
            // left
            16, 17, 18,
            18, 19, 16,
            // right
            20, 21, 22,
            22, 23, 20,
            // front
            0,  1,  2,
            2,  3,  0,
            // top
            4,  5,  6,
            6,  7,  4,
            // back
            8,  9, 10,
            10, 11,  8,
            // bottom
            12, 13, 14,
            14, 15, 12,
            // left
            16, 17, 18,
            18, 19, 16,
            // right
            20, 21, 22,
            22, 23, 20,
            // front
            0,  1,  2,
            2,  3,  0,
            // top
            4,  5,  6,
            6,  7,  4,
            // back
            8,  9, 10,
            10, 11,  8,
            // bottom
            12, 13, 14,
            14, 15, 12,
            // left
            16, 17, 18,
            18, 19, 16,
            // right
            20, 21, 22,
            22, 23, 20,
            // front
            0,  1,  2,
            2,  3,  0,
            // top
            4,  5,  6,
            6,  7,  4,
            // back
            8,  9, 10,
            10, 11,  8,
            // bottom
            12, 13, 14,
            14, 15, 12,
            // left
            16, 17, 18,
            18, 19, 16,
            // right
            20, 21, 22,
            22, 23, 20,
            // front
            0,  1,  2,
            2,  3,  0,
            // top
            4,  5,  6,
            6,  7,  4,
            // back
            8,  9, 10,
            10, 11,  8,
            // bottom
            12, 13, 14,
            14, 15, 12,
            // left
            16, 17, 18,
            18, 19, 16,
            // right
            20, 21, 22,
            22, 23, 20,
            // front
            0,  1,  2,
            2,  3,  0,
            // top
            4,  5,  6,
            6,  7,  4,
            // back
            8,  9, 10,
            10, 11,  8,
            // bottom
            12, 13, 14,
            14, 15, 12,
            // left
            16, 17, 18,
            18, 19, 16,
            // right
            20, 21, 22,
            22, 23, 20,
            // front
            0,  1,  2,
            2,  3,  0,
            // top
            4,  5,  6,
            6,  7,  4,
            // back
            8,  9, 10,
            10, 11,  8,
            // bottom
            12, 13, 14,
            14, 15, 12,
            // left
            16, 17, 18,
            18, 19, 16,
            // right
            20, 21, 22,
            22, 23, 20,
            // front
            0,  1,  2,
            2,  3,  0,
            // top
            4,  5,  6,
            6,  7,  4,
            // back
            8,  9, 10,
            10, 11,  8,
            // bottom
            12, 13, 14,
            14, 15, 12,
            // left
            16, 17, 18,
            18, 19, 16,
            // right
            20, 21, 22,
            22, 23, 20,
            };

    model::Vertices vertex_data;

    for (uint32_t i = 0; i < positions.size(); ++i) {
        vertex_data.push_back({positions[i], glm::vec3(0,0,0), text_postions[i]});
    }

    auto texture_id = model::Model::loadTexture(ASSETS_DIR + std::string("container.jpg"));
    model::Textures texts;
    texts.push_back({texture_id, model::LightType::DIFFUSE, ASSETS_DIR + std::string("container.jpg")});
    model::Mesh mesh(vertex_data, indices, texts);

    m_program.AddLocalTransform(glm::rotate(glm::mat4(1.f), 0.5f, glm::vec3(0.0f, 1.0f, 0.f)));

    m_program.AddShaders( {
        { GL_VERTEX_SHADER, VERTEX_SHADERS_DIR + std::string("multiple_lights.vert") },
        { GL_FRAGMENT_SHADER, FRAGMENT_SHADERS_DIR + std::string("multiple_lights.frag") }
    });

    std::thread t([this, &mesh]() {
        m_program.MainLoop([&mesh, this](ShaderTool::Program& prog) {
            mesh.Draw(prog);
        });
        m_program.TakeScreenshot("CubeMeshShot.tga");
    });

    m_program.Stop();
    t.join();
    // Compare rendered image and stored golden image
    EXPECT_TRUE(CompareFiles(gkTestDataDir / gkCubeShotFileName, gkCubeShotFileName));
}

// Load textured fbx model, draw it, store rendered image to file and then compare with golden data
TEST_F(ProgramTest, FullTest) {
    EXPECT_TRUE(m_program.AddShaders( {
            { GL_VERTEX_SHADER, VERTEX_SHADERS_DIR + std::string("multiple_lights.vert") },
            { GL_FRAGMENT_SHADER, FRAGMENT_SHADERS_DIR + std::string("multiple_lights.frag") }
    }));

    EXPECT_TRUE(m_program.LoadModel(MODELS_DIR + std::string("eve/Evelynn.fbx")));

    std::thread t([this]() { m_program.RunMainLoop(); m_program.TakeScreenshot("ModelMeshShot.tga");});
    m_program.Stop();
    t.join();
    // Compare rendered image and stored golden image
    EXPECT_TRUE(CompareFiles(gkTestDataDir / gkModelShotFileName, gkModelShotFileName));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
