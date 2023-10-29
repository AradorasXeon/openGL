#include <iostream>
#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/src/shaderClass.h"
#include "../include/src/VAO.h"
#include "../include/src/VBO.h"
#include "../include/src/EBO.h"
#include "../include/src/Texture.h"

//Based on: https://www.youtube.com/watch?v=45MIykWJ-C4

const unsigned int width = 800;
const unsigned int height = 800;

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
        -0.5f, 0.0f, 0.5f,          0.83f, 0.70f, 0.44f,   0.0f, 0.0f,
        -0.5f, 0.0f, -0.5f,         0.95f, 0.70f, 0.44f,   7.0f, 0.0f,
        0.5f, 0.0f, -0.5f,          0.95f, 0.89f, 0.44f,   0.0f, 0.0f,
        0.5f, 0.0f, 0.5f,           0.95f, 0.89f, 0.2f,    3.0f, 0.0f,
        0.0f, 0.8f, 0.0f,           0.25f, 0.25f, 0.89f,   2.5f, 5.0f
    };

    GLuint indicies[] =
    {
        0,1,2,
        0,2,3,
        0,1,4,
        1,2,4,
        2,3,4,
        3,0,4
    };

    window = glfwCreateWindow(width, height, "Beautiful window", NULL, NULL);
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

    glViewport(0,0,width,height); //hm so far this does nothing, or so it seems || it had an effect when 
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
    Texture superImage("../resources/images/earth.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    superImage.TexUnit(shaderProgram, "tex0", 0);

    float rotation = 0.0f;
    double prevTime = glfwGetTime();

    glEnable(GL_DEPTH_TEST); //enable depth buffer, so we don't get random X-ray vision
    
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.65f, 0.65f, 0.65f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.Activate();

        double currentTime = glfwGetTime();
        if(currentTime - prevTime >= 1/60)
        {
            rotation += 0.5f;
            prevTime = currentTime;
        }

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
        proj = glm::perspective(glm::radians(45.0f), (float)(width/height), 0.1f, 100.0f); //field of view, aspect ratio, near clip, far clip

        int modelLoc = glGetUniformLocation(shaderProgram.getID(), "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        int viewLoc = glGetUniformLocation(shaderProgram.getID(), "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projLoc = glGetUniformLocation(shaderProgram.getID(), "proj");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

        glUniform1f(uniID, 0.5f); //can be used only after shader program is activated
        superImage.Bind();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indicies)/sizeof(int), GL_UNSIGNED_INT, 0); //not glDrawArrays, so EBO is used
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