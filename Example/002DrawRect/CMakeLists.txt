add_executable(002DrawRect ./002Main.cpp)
target_include_directories(002DrawRect PUBLIC ${CommonDir})
target_link_libraries(002DrawRect glfw glad ${OPENGL_LIBRARIES})
