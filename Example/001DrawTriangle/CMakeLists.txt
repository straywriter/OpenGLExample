add_executable(001DrawTriangle ./Main.cpp )
target_include_directories(001DrawTriangle   PUBLIC ${CommonDir})
target_link_libraries(001DrawTriangle  glfw glad ${OPENGL_LIBRARIES})
