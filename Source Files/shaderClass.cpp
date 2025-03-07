#include"shaderClass.h"

std::string get_file_contents(const char* filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // Create Vertex Shader Object and get its reference
    glShaderSource(vertexShader, 1, &vertexSource, NULL); // Attach Vertex Shader sourceto the Vertex Shader Object
    glCompileShader(vertexShader); // Compile the Verte Shader into machine code

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Create FragmentShader Object and get its reference
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL); // Attach Fragment Shader sourceto the Fragment Shader Object
    glCompileShader(fragmentShader); // Compile the Fragment Shader into machine code

    ID = glCreateProgram(); // Create Shader Program Object and get its reference
    // Attach the vertex and Fragment Shader to the Shader Program
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    // Wrap-up/Link all the shaders together into the Shader Program
    glLinkProgram(ID);

    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
    glUseProgram(ID);
}

void Shader::Delete()
{
    glDeleteProgram(ID);
}