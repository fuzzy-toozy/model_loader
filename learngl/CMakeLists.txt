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

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O2")

set(APP_SRC "main.cpp")

set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../include")
set(LINK_DIR "${CMAKE_SOURCE_DIR}/../libs")

link_directories(${LINK_DIR})

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
  IMPORTED_LOCATION "${LINK_DIR}/libglfw3.a"
  INTERFACE_INCLUDE_DIRECTORIES "${INCLUDE_DIR}/GLFW"
)

add_library(glew STATIC IMPORTED)
set_target_properties(glew PROPERTIES
  IMPORTED_LOCATION "${LINK_DIR}/libGLEW.a"
  INTERFACE_INCLUDE_DIRECTORIES "${INCLUDE_DIR}/GL"
)

add_library(soil STATIC IMPORTED)
set_target_properties(soil PROPERTIES
  IMPORTED_LOCATION "${LINK_DIR}/libSOIL.a"
  INTERFACE_INCLUDE_DIRECTORIES "${INCLUDE_DIR}/SOIL"
)

add_library(assimp SHARED IMPORTED)
set_target_properties(assimp PROPERTIES
  IMPORTED_LOCATION "${LINK_DIR}/libassimp.so"
  INTERFACE_INCLUDE_DIRECTORIES "${INCLUDE_DIR}/assimp"
)

add_executable(app ${APP_SRC})

target_compile_definitions(app PUBLIC 
  ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets/"
  SHADERS_DIR="${CMAKE_SOURCE_DIR}/shader_utils/shaders/"
  VERTEX_SHADERS_DIR="${CMAKE_SOURCE_DIR}/shader_utils/shaders/vertex/"
  FRAGMENT_SHADERS_DIR="${CMAKE_SOURCE_DIR}/shader_utils/shaders/fragment/"
  MODELS_DIR="${CMAKE_SOURCE_DIR}/assets/models/"
)

include_directories(
  ${INCLUDE_DIR}
  ${CMAKE_SOURCE_DIR}/shader_utils/inc
  ${CMAKE_SOURCE_DIR}/modeling/inc
  ${CMAKE_SOURCE_DIR}/camera/inc
)

add_subdirectory(shader_utils)
add_subdirectory(camera)
add_subdirectory(modeling)

target_link_libraries(app shader_tool camera_tool modeling_tool glew glfw soil assimp gtest_main -lGL -ldl -lX11 -lpthread -lXrandr -lXi)
