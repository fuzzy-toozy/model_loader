include_directories(inc)
target_include_directories(app PUBLIC inc)

file(GLOB SOURCES "src/*.cpp")

add_library(graphic_control STATIC ${SOURCES})
