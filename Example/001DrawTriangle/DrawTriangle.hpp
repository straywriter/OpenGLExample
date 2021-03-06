#pragma once

#include <GLFWApplication.hpp>
#include <chrono>


GLfloat vertices[] = {0.0f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f};

class DrawTrangle : public GLFWApplication
{
  public:
    int vertexShader;
    int fragmentShader;
    int shaderProgram;

    unsigned int VAO, VBO;

    void run()
    {
        createShader();
        createProgram();
        createVBO();
        createVAO();

        mainLoop();
    }

  private:
    void mainLoop()
    {
        while (!isWindowShouldClose())
        {
            // input
            processInput();

            // render
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            render();
            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            swapBuffer();
            windowPollEvents();
        }
    }

    void createShader()
    {

        const char *vertexShaderSource = "#version 330 core\n"
                                         "in vec2 position;\n"
                                         "void main()\n"
                                         "{\n"
                                         "   gl_Position = vec4(position, 0.0, 1.0);\n"
                                         "}\0";

        const char *fragmentShaderSource = "#version 330 core\n"
                                           "out vec4 FragColor;\n"
                                           "uniform vec3 TriangleColor;"
                                           "void main()\n"
                                           "{\n"
                                           "   FragColor =  vec4(TriangleColor, 1.0);\n"
                                           "}\0";

        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // fragment shader
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }

    void setUniform()
    {
    }

    void createProgram()
    {

        int success;
        char infoLog[512];
        // link shaders
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        // check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void createVAO()
    {
        glGenVertexArrays(1, &VAO);
        // glGenBuffers(1, &VBO);

        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex
        // attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        // Specify the layout of the vertex data
        // GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
        // glEnableVertexAttribArray(posAttrib);
        // glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

        glBindVertexArray(0);
    }

    void createVBO()
    {
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void render()
    {
        static auto t_start = std::chrono::high_resolution_clock::now();
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll
                                // do so to keep things a bit more organized

        // Get the location of the color uniform
        GLint uniColor = glGetUniformLocation(shaderProgram, "TriangleColor");
        // Set the color of the triangle
        auto t_now = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();

        glUniform3f(uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);

        glDrawArrays(GL_TRIANGLES, 0, 6);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
};