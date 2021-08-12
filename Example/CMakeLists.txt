
find_package(OpenGL REQUIRED)

set(CommonDir ${CMAKE_CURRENT_SOURCE_DIR}/Common/ CACHE STRING "" FORCE)

add_subdirectory(000CreateWindow)
add_subdirectory(001DrawTriangle)
add_subdirectory(002DrawRect)
# add_subdirectory(2Shader)

# add_subdirectory(.)