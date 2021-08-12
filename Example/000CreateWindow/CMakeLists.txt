add_executable(000CreateWindow ./Main.cpp ./CreateWindow.hpp)
target_include_directories(000CreateWindow   PUBLIC ${CommonDir})
target_link_libraries(000CreateWindow  glfw glad ${OPENGL_LIBRARIES})
