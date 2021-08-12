
add_executable(005Texture ./005Main.cpp )
target_include_directories(005Texture PUBLIC ${CommonDir})
target_link_libraries(005Texture glfw glad glm stb ${OPENGL_LIBRARIES})

add_custom_command(
  TARGET 005Texture
  POST_BUILD
  COMMAND
    ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/Texture.frag
    ${CMAKE_CURRENT_SOURCE_DIR}/Texture.vert
    ${CMAKE_CURRENT_SOURCE_DIR}/Texture.jpg
    $<TARGET_FILE_DIR:005Texture>)

