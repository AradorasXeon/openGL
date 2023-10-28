#include <iostream>
#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>

#include "../include/src/shaderClass.h"
#include "../include/src/VAO.h"
#include "../include/src/VBO.h"
#include "../include/src/EBO.h"
#include "../include/src/Texture.h"

//Based on: https://www.youtube.com/watch?v=45MIykWJ-C4

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
        -0.5f, -0.5f, 0.0f,         0.1f, 0.0f, 0.6f,   0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,          0.2f, 0.2f, 0.1f,   0.0f, 1.0f,
        0.5f, 0.5f, 0.0f,           0.4f, 0.8f, 0.6f,   1.0f, 1.0f,
        0.5f, -0.5f, 0.0f,          0.7f, 0.9f, 0.2f,   1.0f, 0.0f
    };

    GLuint indicies[] =
    {
        0,1,2,
        0,2,3
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
    
    Shader shaderProgram("../shaders/default.vert", "../shaders/default.frag");
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(verticies, sizeof(verticies));
    EBO EBO1(indicies, sizeof(indicies));   //will be automaticaly (?) attached to VAO

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0); //first 3 numbers from verticies
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))); //next 3 nums
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat))); //next 2 nums
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.getID() , "scale"); //to get the location of "scale" from the default.vert

    //Texture
    Texture superImage("../resources/images/super.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    superImage.TexUnit(shaderProgram, "tex0", 0);
    /*
    int widthImage, heightImage, numOfColChan;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load("../resources/images/super.jpg", &widthImage, &heightImage, &numOfColChan, 0);
    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f}
    //glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint tex0Uni = glGetUniformLocation(shaderProgram.getID(), "tex0");
    shaderProgram.Activate();
    glUniform1i(tex0Uni, 0);
*/
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.65f, 0.65f, 0.65f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();
        glUniform1f(uniID, 0.5f); //can be used only after shader program is activated
        superImage.Bind();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //not glDrawArrays, so EBO is used
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Deleting stuff
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    superImage.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}