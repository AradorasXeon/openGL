#include <iostream>
#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>

//Based on: https://www.youtube.com/watch?v=45MIykWJ-C4

const char* vertexShaderSource = 
"#version 330 core \n"
"layout (location = 0) in vec3 aPos; \n"
"void main()\n"
"{ gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);} \0";

const char* fragmentShaderSource =
"#version 330 core \n"
"out vec4 FragColor;\n"
"void main()\n"
"{FragColor = vec4(0.8f, 0.65f, 0.42f, 1.0f);} \0";

int main()
{
    //std::cout << "Hello there :)" << std::endl;

    GLFWwindow* window;

    if(!glfwInit())
    {
        std::cerr << "glfw failed to init." << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 8);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Could not create window with this

    GLfloat verticies[]=
    {
        -.3f, -.2f,
        0.0f, 0.1f,
        0.8f, 0.9f
    };

    window = glfwCreateWindow(800, 800, "Beautiful window", NULL, NULL);
    if(window == nullptr)
    {
        std::cerr << "Could not create window." << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) //this loads openGL
    {
        std::cerr << "Glad loader failed to get proc address" << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0,0,800,800); //hm so far this does nothing, or so it seems || it had an effect when 
    //I drew the first triangle
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);     //practically it gives back a handle (a number) for an object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //handled object is emptied and given source code is copied
    glCompileShader(vertexShader);                              //compiles object's actual source code

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();                   //this is created so shaders can be linked together
    glAttachShader(shaderProgram, vertexShader);                //and this is good, because OpenGL can check if the 
    glAttachShader(shaderProgram, fragmentShader);              //shader can play together nicely, I think we can glCompile after this, too
    glLinkProgram(shaderProgram);                               //links the compiled programs together

    //We are deleting the shaders now because they are already in the program:
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //We should only send big amount of data from the CPU to the GPU
    //So we need big bags (or buffers)
    GLuint VAO,VBO; //Vertex Array Object (?) /Vertex Buffer Object ----- these could be arrays

    glGenVertexArrays(1, &VAO); //VAO must be generated before VBO  ----- if they are arrays this name makes sense
    //"There is no guarantee that the names form a contiguous set of integers" -- no guarantee of 1,2,3,4,5....
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Binding in OpenGL means a certain object is made to be the "current object"
    //Then operating on the current object is equavilent with the bound object
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
    //stream - modified once, used some times, static - modified once used many times
    //dynamic - verticies will be modified multiple, used many times
    //^^ this is to improve performance
    //Draw - modified, and will be drawn read --? copy--?

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //seems we have to "derefernce" them the other way around
    //especially said here that ordering matters
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    glClearColor(0.25f, 0.82f, 0.83f, 1.0f); //default color in the color buffer

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.25f, 0.82f, 0.83f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);                //runs compiled shader program
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    //Deleting stuff
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}