cmake_minimum_required(VERSION 3.16)
project("learngl")

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g")

set(APP_SRC "main.cpp")

set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/externals")
set(LINK_DIR "${CMAKE_SOURCE_DIR}/../libs")

link_directories(
    ${CMAKE_BINARY_DIR}/assimp/code
    ${CMAKE_BINARY_DIR}/glew/lib
    ${CMAKE_BINARY_DIR}/glfw/src
    ${CMAKE_BINARY_DIR}/soil/lib
)

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
  IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/glfw/src/libglfw3.a"
  INTERFACE_INCLUDE_DIRECTORIES "${INCLUDE_DIR}/glfw-3.3.4/include/GLFW/"
)

add_library(glew STATIC IMPORTED)
set_target_properties(glew PROPERTIES
  IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/glew/lib/libGLEW.a"
  INTERFACE_INCLUDE_DIRECTORIES "${INCLUDE_DIR}/glew-2.1.0/include/GL/"
)

add_library(soil STATIC IMPORTED)
set_target_properties(soil PROPERTIES
  IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/soil/lib/libSOIL.a"
  INTERFACE_INCLUDE_DIRECTORIES "${INCLUDE_DIR}/soil/include/"
)

add_library(assimp SHARED IMPORTED)
set_target_properties(assimp PROPERTIES
  IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/assimp/code/libassimp.so"
  INTERFACE_INCLUDE_DIRECTORIES "${INCLUDE_DIR}/assimp-3.1.1/include/assimp/"
)

add_executable(app ${APP_SRC})

add_compile_definitions(PUBLIC
  ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets/"
  SHADERS_DIR="${CMAKE_SOURCE_DIR}/shader_utils/shaders/"
  VERTEX_SHADERS_DIR="${CMAKE_SOURCE_DIR}/shader_utils/shaders/vertex/"
  FRAGMENT_SHADERS_DIR="${CMAKE_SOURCE_DIR}/shader_utils/shaders/fragment/"
  MODELS_DIR="${CMAKE_SOURCE_DIR}/assets/models/"
  TEST_DATA_DIR="${CMAKE_SOURCE_DIR}/tests/test_data/"
)

include_directories(
  ${INCLUDE_DIR}/glfw-3.3.4/include
  ${INCLUDE_DIR}/glew-2.1.0/include
  ${INCLUDE_DIR}/assimp-3.1.1/include
  ${INCLUDE_DIR}/glm
  ${INCLUDE_DIR}/soil/include/
  ${CMAKE_SOURCE_DIR}/shader_utils/inc
  ${CMAKE_SOURCE_DIR}/modeling/inc
  ${CMAKE_SOURCE_DIR}/camera/inc
  ${CMAKE_SOURCE_DIR}/graphic_control/inc
)

add_subdirectory(shader_utils)
add_subdirectory(camera)
add_subdirectory(modeling)
add_subdirectory(graphic_control)

set(LINK_LIBRARIES graphic_control shader_tool camera_tool modeling_tool glew glfw soil assimp gtest_main -lGL -ldl -lX11 -lpthread -lXrandr -lXi)

target_link_libraries(app ${LINK_LIBRARIES})
add_subdirectory(tests)
