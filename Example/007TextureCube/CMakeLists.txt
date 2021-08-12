
add_executable(007TextureCube ./007Main.cpp )
target_include_directories(007TextureCube PUBLIC ${CommonDir})
target_link_libraries(007TextureCube glfw glad glm stb ${OPENGL_LIBRARIES})

add_custom_command(
  TARGET 007TextureCube
  POST_BUILD
  COMMAND
    ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/TextureCube.vert
    ${CMAKE_CURRENT_SOURCE_DIR}/TextureCube.frag
    ${CMAKE_CURRENT_SOURCE_DIR}/TextureCube.tga
    $<TARGET_FILE_DIR:007TextureCube>)

