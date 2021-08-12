
#include <GLFWApplication.hpp>
#include <LoadShader.hpp>

#include <chrono>

GLfloat vertices[] = {0.0f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f};

class ExternalShader : public GLFWApplication
{

  public:
    // int vertexShader;
    // int fragmentShader;
    int shaderProgram;

    unsigned int VAO, VBO;

    void run()
    {
        // createShader();
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

    void setUniform()
    {
    }

    void createProgram()
    {
        shaderProgram = LoadShaders("SimpleVertexShader.vert", "SimpleFragmentShader.frag");
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