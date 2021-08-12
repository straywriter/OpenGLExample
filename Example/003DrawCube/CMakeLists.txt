add_executable(003DrawCube ./003Main.cpp)
target_include_directories(003DrawCube PUBLIC ${CommonDir})
target_link_libraries(003DrawCube glfw glad glm ${OPENGL_LIBRARIES})
