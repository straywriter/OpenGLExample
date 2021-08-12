
add_executable(006MultipleTexture ./006Main.cpp )
target_include_directories(006MultipleTexture PUBLIC ${CommonDir})
target_link_libraries(006MultipleTexture glfw glad glm stb ${OPENGL_LIBRARIES})

add_custom_command(
  TARGET 006MultipleTexture
  POST_BUILD
  COMMAND
    ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/MultipleTexture.vert
    ${CMAKE_CURRENT_SOURCE_DIR}/MultipleTexture.frag
    ${CMAKE_CURRENT_SOURCE_DIR}/Texture1.jpg
    ${CMAKE_CURRENT_SOURCE_DIR}/Texture2.png
    $<TARGET_FILE_DIR:006MultipleTexture>)

