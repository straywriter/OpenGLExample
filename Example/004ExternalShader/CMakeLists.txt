add_executable(004ExternalShader ${CMAKE_CURRENT_SOURCE_DIR}/004Main.cpp )
target_include_directories(004ExternalShader PUBLIC ${CommonDir})
target_link_libraries(004ExternalShader glfw glad glm ${OPENGL_LIBRARIES})

add_custom_command(
  TARGET 004ExternalShader
  POST_BUILD
  COMMAND
    ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/SimpleFragmentShader.frag
    ${CMAKE_CURRENT_SOURCE_DIR}/SimpleVertexShader.vert
    $<TARGET_FILE_DIR:004ExternalShader>)

