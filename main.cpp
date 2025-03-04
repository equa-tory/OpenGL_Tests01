#include <iostream>     //for cout
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(void)
{
    glfwInit(); // start gl

    // set version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // set profile

    GLFWwindow *window = glfwCreateWindow(800, 800, "GL", NULL, NULL); // create window
    if(window == NULL) // if failed to create window
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // set context

    gladLoadGL(); // load glad

    glViewport(0, 0, 800, 800); // set viewport

    

    // Vertices coordinates
    GLfloat vertices[] =
    {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,    // Lower left corner
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,     // Lower right corner
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  // Top corner
        -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
        0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,  // Inner right
        0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f      // Inner top
    };

    GLuint inddices[] =
    {
        0, 3, 5, // Lower left triangle
        3, 2, 4, // Lower right triangle
        5, 4, 1  // Upper triangle
    };
    
    // Create reference containers for the Vertex Array Object and the Vertex Buffer Object
    GLuint VAO, VBO, EBO;

    // Generate the VAO and VBO with only 1 object each
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Make the VAO the current Vertex Array Object by binding it
    glBindVertexArray(VAO);

    // Bind the VBO specifying it's a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Introduce the vertices into the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(inddices), inddices, GL_STATIC_DRAW);

    // Configure the Vertex Attribute so that OpenGL knows how to read the VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    // Enable the Vertex Attribute so that OpenGL knows to use it
    glEnableVertexAttribArray(0);

    // Bind both the VAO and VBO to 0 so that we don't accidentally modify the VAO and VBO we created earlier
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // glClearColor(0.07f, 0.13f, 0.07f, 1.0f); // set bg color
    // glClear(GL_COLOR_BUFFER_BIT);            // clear buffer amd set new color
    // glfwSwapBuffers(window); // swap buffers (preloaded and current)

    // Main while loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.07f, 1.0f);             // set bg color
        glClear(GL_COLOR_BUFFER_BIT);                        // clear buffer amd set new color
        glUseProgram(shaderProgram);                         // Tell OpenGL which Shader Program we want to use
        glBindVertexArray(VAO);                              // Bind the VAO so OpenGL knows to use it
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); // Draw the triangle
        glfwSwapBuffers(window);                             // swap buffers (preloaded and current)

        glfwPollEvents(); // take care of all GLFW events
    }

    // Delete all the objects we've created
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window); // close window
    glfwTerminate();           // close gl
    return 0;
}