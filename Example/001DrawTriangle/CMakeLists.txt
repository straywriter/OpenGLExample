add_executable(000DrawTriangle ./Main.cpp )
target_include_directories(000DrawTriangle   PUBLIC ${CommonDir})
target_link_libraries(000DrawTriangle  glfw glad ${OPENGL_LIBRARIES})
