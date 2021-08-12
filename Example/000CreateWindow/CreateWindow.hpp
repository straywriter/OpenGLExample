#pragma once

#include <GLFWApplication.hpp>

class CreateWindow : public GLFWApplication
{
  public:
    void run() override
    {
        while (!isWindowShouldClose())
        {
            // input
            processInput();

            // render
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            swapBuffer();
            windowPollEvents();
        }
    }

};