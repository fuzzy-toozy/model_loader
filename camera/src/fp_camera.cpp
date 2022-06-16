#include <camera/fp_camera.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <ctime>

namespace camera
{

void FPCamera::TakeScreenshot(const std::filesystem::path& path)
{
        std::vector<uint8_t> pixels(m_screen_w * m_screen_h * 3);
        glReadPixels(0, 0, m_screen_w, m_screen_h, 0x80E0, 
        GL_UNSIGNED_BYTE, pixels.data());
        std::ofstream out_file(path.c_str(), std::ios::binary | std::ios::out);

        // this is the tga header it must be in the beginning of 
        // every (uncompressed) .tga
        uint8_t tga_header[12]={0,0,2,0,0,0,0,0,0,0,0,0};
        // the header that is used to get the dimensions of the .tga
        // header[1]*256+header[0] - width
        // header[3]*256+header[2] - height
        // header[4] - bits per pixel
        // header[5] - ?
        uint8_t header[6]={
            ((int)(m_screen_w % 256)),
            ((int)(m_screen_w / 256)),
            ((int)(m_screen_h % 256)),
            ((int)(m_screen_h / 256)) ,
            24 ,0 };

        out_file.write((char*)tga_header, sizeof(tga_header));
        out_file.write((char*)header, sizeof(header));
        out_file.write((char*)pixels.data(), pixels.size());
}

glm::mat4 FPCamera::MakeViewRotation() const
{
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

    return rotation;
}

void FPCamera::OnScrollInput(GLFWwindow* window, double x_pos, double y_pos)
{
    FPCamera* camera = reinterpret_cast<FPCamera*>(glfwGetWindowUserPointer(window));

    if(camera->m_fov >= camera->m_fov_limit_low && camera->m_fov <= camera->m_fov_limit_high) {
        camera->m_fov -= y_pos;
    }
    if(camera->m_fov <= camera->m_fov_limit_low) {
        camera->m_fov = camera->m_fov_limit_low;  
    }
    if(camera->m_fov >= camera->m_fov_limit_high) {
        camera->m_fov = camera->m_fov_limit_high;
    }
}

void FPCamera::OnKeyInput(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    FPCamera* camera = reinterpret_cast<FPCamera*>(glfwGetWindowUserPointer(window));
    camera->SetKeys(key, action);
    camera->ProcessKeyboard(key, action);
}

void FPCamera::OnMouseInput(GLFWwindow* window, double x_pos, double y_pos)
{
    FPCamera* camera = reinterpret_cast<FPCamera*>(glfwGetWindowUserPointer(window));
    camera->ProcessMouse(x_pos, y_pos);
}

FPCamera::FPCamera(GLFWwindow* window)
{
    m_proj_transform = glm::perspective(glm::radians(45.0f), m_aspect, 0.1f, 100.0f);
    m_window = window;

    glfwSetWindowUserPointer(m_window, this);
    glfwSetKeyCallback(m_window, OnKeyInput);
    glfwSetCursorPosCallback(m_window, OnMouseInput);
    glfwSetScrollCallback(m_window, OnScrollInput);
    SetKeyCallback(GLFW_KEY_SPACE, GLFW_PRESS, [this] () {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::stringstream ss;
    ss << "Screen_" << std::put_time(&tm,"%d-%m-%Y%H-%M-%S") << ".tga";
        TakeScreenshot(ss.str());
    });
}

void FPCamera::OnFrameChange()
{
    UpdateFrameTime();
    ProcessMovement();
    UpdateViewMatrix();
}

void FPCamera::SetKeys(const int key, const int action)
{
    m_keys[key] = action;
}


void FPCamera::ProcessMouse(const GLfloat x_pos, const GLfloat y_pos)
{
    static bool firstMouse = InitMouseCursor(x_pos, y_pos);

    GLfloat x_offset = x_pos - m_last_cursor_x_pos;
    GLfloat y_offset = m_last_cursor_y_pos - y_pos;

    m_last_cursor_x_pos = x_pos;
    m_last_cursor_y_pos = y_pos;

    x_offset *= m_sensitivity;
    y_offset *= m_sensitivity;

    m_yaw += x_offset;
    m_pitch += y_offset;

    if(m_pitch > m_pitch_limit_high) { 
        m_pitch = m_pitch_limit_high;
    }
    if(m_pitch < m_pitch_limit_low) {
        m_pitch = m_pitch_limit_low;
    }

    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_direction = glm::normalize(front);
}

glm::mat4 FPCamera::GetViewFromRotation(GLfloat pitch, GLfloat yaw)
{
    glm::vec3 front;
    pitch += m_pitch;
    yaw += m_yaw;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    auto direction = glm::normalize(front);

    auto cam_z = -direction;
    auto cam_x = glm::normalize(glm::cross(glm::vec3(0.f, 1.f, 0.f), cam_z));
    auto cam_y = glm::cross(cam_z, cam_x);

    glm::mat4 translation = glm::mat4(1.0f);

    glm::mat4 rotation(1.f);

    rotation[0][0] = cam_x.x;
    rotation[1][0] = cam_x.y;
    rotation[2][0] = cam_x.z;
    rotation[0][1] = cam_y.x;
    rotation[1][1] = cam_y.y;
    rotation[2][1] = cam_y.z;
    rotation[0][2] = cam_z.x;
    rotation[1][2] = cam_z.y;
    rotation[2][2] = cam_z.z;

    translation[3][0] = -m_world_pos.x;
    translation[3][1] = -m_world_pos.y;
    translation[3][2] = -m_world_pos.z;

    auto view_transform = rotation * translation;

    return view_transform;
}

void FPCamera::UpdateViewMatrix()
{
    m_camera_z = -m_direction;
    m_camera_x = glm::normalize(glm::cross(m_world_y, m_camera_z));
    m_camera_y = glm::cross(m_camera_z, m_camera_x);

    glm::mat4 translation = glm::mat4(1.0f);

    glm::mat4 rotation = MakeViewRotation();

    translation[3][0] = -m_world_pos.x;
    translation[3][1] = -m_world_pos.y;
    translation[3][2] = -m_world_pos.z;

    m_view_transform = rotation * translation;
}

void FPCamera::UpdateFrameTime()
{
    GLfloat curent_time = glfwGetTime();
    m_time_delta = curent_time - m_last_frame_time;
    m_last_frame_time = curent_time;
}

void FPCamera::ProcessMovement()
{
    GLfloat camera_speed = m_movenmet_speed * m_time_delta;

    if(m_keys[GLFW_KEY_W] == GLFW_PRESS || m_keys[GLFW_KEY_W] == GLFW_REPEAT) {
        m_world_pos += camera_speed * m_direction;
    }
    if(m_keys[GLFW_KEY_S] == GLFW_PRESS || m_keys[GLFW_KEY_S] == GLFW_REPEAT) {
        m_world_pos -= camera_speed * m_direction;
    }
    if(m_keys[GLFW_KEY_A] == GLFW_PRESS || m_keys[GLFW_KEY_A] == GLFW_REPEAT) {
        m_world_pos -= m_camera_x * camera_speed;
    }
    if(m_keys[GLFW_KEY_D] == GLFW_PRESS || m_keys[GLFW_KEY_D] == GLFW_REPEAT) {
        m_world_pos += m_camera_x * camera_speed;
    }
}

void FPCamera::ProcessKeyboard(int key, int action)
{
    const auto& key_callbacks = m_keys_funcs[key];
    const auto& action_for_callback = key_callbacks[action];
    if (action_for_callback) {
        action_for_callback();
    }
}

void FPCamera::SetKeyCallback(const GLint key, const GLint action, std::function<void()>&& func)
{
    m_keys_funcs[key][action] = std::forward<std::function<void()>>(func);
}

}
