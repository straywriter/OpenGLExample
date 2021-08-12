#pragma once

#include <string>
#include <iostream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <IApplication.h>

class GLFWApplication : public IApplication
{
  public:
    GLFWwindow *window;
    unsigned int width;
    unsigned int height;
    std::string windowName;

  public:
    GLFWApplication()
    {
        width = 800;
        height = 600;
        windowName = "null";
        init();
    }

    GLFWApplication(unsigned int width, unsigned int height, std::string windowName)
        : width(width), height(height), windowName(windowName)
    {
        init();
    }

    ~GLFWApplication()
    {
        destory();
    }

    bool init() 
    {
        initGLFW();
        if (!initWindow())
            return false;
        if (!initOpenGL())
            return false;
        initOpenGLDebug();
    }

     void run() 
    {
    }

     void destroy() 
    {
        destoryGLFW();
    }

    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    void processInput()
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    void swapBuffer()
    {
        glfwSwapBuffers(window);
    }

    void windowPollEvents()
    {
        glfwPollEvents();
    }

    bool isWindowShouldClose()
    {
        return glfwWindowShouldClose(window);
    }

  private:
    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    bool initWindow()
    {
        const unsigned int SCR_WIDTH = width;
        const unsigned int SCR_HEIGHT = height;
        window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        return true;
    }

    void initGLFW()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    }

    void destoryGLFW()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    bool initOpenGL()
    {
        // glad: load all OpenGL function pointers
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return false;
        }
        return true;
    }

    static void MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                const GLchar *message, const void *userParam)
    {

        {
            // fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            //         (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);

            if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
                return;

            std::cout << "---------------" << std::endl;
            std::cout << "Debug message (" << id << "): " << message << std::endl;

            switch (source)
            {
            case GL_DEBUG_SOURCE_API:
                std::cout << "Source: API";
                break;
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
                std::cout << "Source: Window System";
                break;
            case GL_DEBUG_SOURCE_SHADER_COMPILER:
                std::cout << "Source: Shader Compiler";
                break;
            case GL_DEBUG_SOURCE_THIRD_PARTY:
                std::cout << "Source: Third Party";
                break;
            case GL_DEBUG_SOURCE_APPLICATION:
                std::cout << "Source: Application";
                break;
            case GL_DEBUG_SOURCE_OTHER:
                std::cout << "Source: Other";
                break;
            }
            std::cout << std::endl;

            switch (type)
            {
            case GL_DEBUG_TYPE_ERROR:
                std::cout << "Type: Error";
                break;
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
                std::cout << "Type: Deprecated Behaviour";
                break;
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                std::cout << "Type: Undefined Behaviour";
                break;
            case GL_DEBUG_TYPE_PORTABILITY:
                std::cout << "Type: Portability";
                break;
            case GL_DEBUG_TYPE_PERFORMANCE:
                std::cout << "Type: Performance";
                break;
            case GL_DEBUG_TYPE_MARKER:
                std::cout << "Type: Marker";
                break;
            case GL_DEBUG_TYPE_PUSH_GROUP:
                std::cout << "Type: Push Group";
                break;
            case GL_DEBUG_TYPE_POP_GROUP:
                std::cout << "Type: Pop Group";
                break;
            case GL_DEBUG_TYPE_OTHER:
                std::cout << "Type: Other";
                break;
            }
            std::cout << std::endl;

            switch (severity)
            {
            case GL_DEBUG_SEVERITY_HIGH:
                std::cout << "Severity: high";
                break;
            case GL_DEBUG_SEVERITY_MEDIUM:
                std::cout << "Severity: medium";
                break;
            case GL_DEBUG_SEVERITY_LOW:
                std::cout << "Severity: low";
                break;
            case GL_DEBUG_SEVERITY_NOTIFICATION:
                std::cout << "Severity: notification";
                break;
            }
            std::cout << std::endl;
            std::cout << std::endl;
        }
    }

    void initOpenGLDebug()
    {
        GLint flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

        if (flags)
        {
            // std::cout << "debug init success\n" ;
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

            glDebugMessageCallback(MessageCallback, 0);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
        }
    }
};