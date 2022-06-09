#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <functional>
#include <array>

constexpr uint16_t gcKeysNb = 1024;

namespace camera
{

class FPCamera
{
    public:
        FPCamera(GLFWwindow* window);
    
        inline void SetWorld(const glm::vec3& world_x, const glm::vec3& world_y, const glm::vec3& world_z)
        {
            m_world_x = world_x;
            m_world_y = world_y;
            m_world_z = world_z;
        }

        inline void SetRotation(const GLfloat pitch, const GLfloat yaw)
        { 
            m_pitch = pitch;
            m_yaw = yaw;
        }

        inline void SetYawLimit(const GLfloat low, const GLfloat high)
        {
            m_yaw_limit_low = low;
            m_yaw_limit_high = high;
        }

        inline void SetPitchLimit(const GLfloat low, const GLfloat high)
        {
            m_pitch_limit_low = low;
            m_pitch_limit_high = high;
        }

        inline void SetScreen(const GLfloat width, const GLfloat height)
        { 
            m_screen_w = width;
            m_screen_h = height;
            m_aspect = m_screen_w / m_screen_h;
            m_proj_transform = glm::perspective(glm::radians(45.0f), m_aspect, 0.1f, 100.0f);
        }

        inline void SetPosition(const glm::vec3 pos) { m_world_pos = pos; }
        inline void SetDirection(const glm::vec3& direction) { m_direction = direction; }
        inline void SetSpeed(const GLfloat speed) { m_movenmet_speed = speed; }
        inline void SetSensitivity(const GLfloat sensitivity) { m_sensitivity = sensitivity; }
        inline void SetFov(const GLfloat fov) { m_fov = fov; m_proj_transform = glm::perspective(glm::radians(m_fov), 1.f, 0.1f, 100.0f); }
        inline void SetFovLimit(const GLfloat low, const GLfloat high) { m_fov_limit_low = low; m_fov_limit_high = high; }

        inline const glm::vec3& GetDirection() const { return m_direction; }
        inline const glm::vec3& GetPosition() const { return m_world_pos; }
        glm::mat4 MakeViewRotation() const;

        const glm::mat4& GetViewMatrix() const { return m_view_transform; }
        const glm::mat4& GetProjectMatrix() const { return m_proj_transform; }

        const std::pair<GLfloat, GLfloat> GetPitchYaw() const { return {m_pitch, m_yaw}; } 

        void OnFrameChange();
        void SetKeyCallback(const GLint, const GLint, std::function<void()>&&);

        glm::mat4 GetViewFromRotation(GLfloat pitch, GLfloat yaw);

        static void OnKeyInput(GLFWwindow* window, int key, int scancode, int action, int mode);
        static void OnMouseInput(GLFWwindow* window, double x_pos, double y_pos);
        static void OnScrollInput(GLFWwindow* window, double x_pos, double y_pos);

    private:

        inline bool InitMouseCursor(const GLfloat x_pos, const GLfloat y_pos)
        {
            m_last_cursor_x_pos = x_pos;
            m_last_cursor_y_pos = y_pos;

            return true;
        }

        void ProcessMouse(const GLfloat, const GLfloat);
        void SetKeys(const int, const int);
        void ProcessMovement();
        void ProcessKeyboard(int key, int action);
        void UpdateViewMatrix();
        void UpdateFrameTime();

        using KeysData = std::pair<GLint, std::function<void()>*>;
        // Array index is a key ID, second array index is key state and second array element is callback for that state
        using KeysDataArray = std::array<std::array<std::function<void()>, 10>, gcKeysNb>;
        std::array<GLint, gcKeysNb> m_keys;
        KeysDataArray m_keys_funcs;

        glm::mat4 m_view_transform{1.f};
        glm::mat4 m_proj_transform{1.f};

        glm::vec3 m_world_x{1.f, 0.f, 0.f};
        glm::vec3 m_world_y{0.f, 1.f, 0.f};
        glm::vec3 m_world_z{0.f, 0.f, 1.f};
        glm::vec3 m_world_pos{0.f, 0.f, 3.f};

        glm::vec3 m_camera_x{1.f};
        glm::vec3 m_camera_y{1.f};
        glm::vec3 m_camera_z{1.f};
        glm::vec3 m_direction{0.f, 0.f, -1.f};

        GLFWwindow* m_window{nullptr};

        GLfloat m_pitch{0.f};
        GLfloat m_yaw{-90.f};
        GLfloat m_pitch_limit_low{-89.f};
        GLfloat m_pitch_limit_high{89.f};
        GLfloat m_yaw_limit_low{0.f};
        GLfloat m_yaw_limit_high{0.f};

        GLfloat m_last_cursor_x_pos{0.f};
        GLfloat m_last_cursor_y_pos{0.f};

        GLfloat m_screen_w{800.f};
        GLfloat m_screen_h{600.f};
        GLfloat m_movenmet_speed{5.f};
        GLfloat m_sensitivity{0.1f};
        GLfloat m_last_frame_time{0.f};
        GLfloat m_time_delta{0.f};
        GLfloat m_fov_limit_high{45.f};
        GLfloat m_fov_limit_low{45.f};
        GLfloat m_fov{45.f};
        GLfloat m_aspect{0.f};
};

}