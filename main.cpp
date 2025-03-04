#include <iostream>     //for cout
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex Shader source code
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos; \n"
"void main() \n"
"{\n" 
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// Fragment Shader source code
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main(void)
{
    glfwInit(); // start gl



    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // set min version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // set max version
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // set profile

    // Vertices coordinates
    GLfloat vertices[] =
    {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Top corner
    };

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

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // Create Vertex Shader Object and get its reference
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // Attach Vertex Shader sourceto the Vertex Shader Object
    glCompileShader(vertexShader); // Compile the Verte Shader into machine code

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Create FragmentShader Object and get its reference
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // Attach Fragment Shader sourceto the Fragment Shader Object
    glCompileShader(fragmentShader); // Compile the Fragment Shader into machine code

    GLuint shaderProgram = glCreateProgram(); // Create Shader Program Object and get its reference
    // Attach the vertex and Fragment Shader to the Shader Program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Wrap-up/Link all the shaders together into the Shader Program
    glLinkProgram(shaderProgram);

    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // Create reference containers for the Vertex Array Object and the Vertex Buffer Object
    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glClearColor(0.07f, 0.13f, 0.07f, 1.0f); // set bg color
    glClear(GL_COLOR_BUFFER_BIT);            // clear buffer amd set new color

    glfwSwapBuffers(window); // swap buffers (preloaded and current)

    // Main while loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.07f, 1.0f); // set bg color
        glClear(GL_COLOR_BUFFER_BIT);            // clear buffer amd set new color
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window); // swap buffers (preloaded and current)

        glfwPollEvents(); // take care of all GLFW events
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window); // close window
    glfwTerminate(); // close gl
    return 0;
}