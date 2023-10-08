#include "../include/src/shaderClass.h"

std::string get_file_content(const char* fileName)
{
    std::ifstream in(fileName, std::ios::binary);
    if(in)
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
    std::string vertexCode = get_file_content(vertexFile);
    std::string fragmentCode = get_file_content(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);     //practically it gives back a handle (a number) for an object
    glShaderSource(vertexShader, 1, &vertexSource, NULL); //handled object is emptied and given source code is copied
    glCompileShader(vertexShader);                              //compiles object's actual source code
    compileErrors(vertexShader, "VERTEX");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    compileErrors(vertexShader, "FRAGMENT");


    ID = glCreateProgram();                   //this is created so shaders can be linked together
    glAttachShader(ID, vertexShader);                //and this is good, because OpenGL can check if the 
    glAttachShader(ID, fragmentShader);              //shader can play together nicely, I think we can glCompile after this, too
    glLinkProgram(ID);                               //links the compiled programs together
    compileErrors(vertexShader, "PROGRAM");


    //We are deleting the shaders now because they are already in the program:
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
    glUseProgram(ID);                //runs compiled shader program
}

void Shader::Delete()
{
    glDeleteProgram(ID);
}

GLuint Shader::getID()
{
    return ID;
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}