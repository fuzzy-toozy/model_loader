include_directories(inc)
target_include_directories(app PUBLIC inc)


file(GLOB SOURCES "src/*.cpp")

add_library(camera_tool STATIC ${SOURCES})