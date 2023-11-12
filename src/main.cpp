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
#include "../include/src/Camera.h"

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

    GLfloat verticies[] =
    { //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
        -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
        -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
        0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
        0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

        -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
        -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
        0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

        -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
        0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
        0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

        0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
        0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
        0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

        0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
        -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
        0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
    };

    GLuint indicies[] =
    {
        0, 1, 2, // Bottom side
        0, 2, 3, // Bottom side
        4, 6, 5, // Left side
        7, 9, 8, // Non-facing side
        10, 12, 11, // Right side
        13, 15, 14 // Facing side
    };

    GLfloat lightVerticies[] = 
    {
        -0.1f, -0.1f, 0.1f,
        -0.1f, -0.1f, -0.1f,
        0.1f, -0.1f, -0.1f,
        0.1f, -0.1f, 0.1f,
        -0.1f, 0.1f, 0.1f,
        -0.1f, 0.1f, -0.1f,
        0.1f, 0.1f, -0.1f,
        0.1f, 0.1f, 0.1f
    };

    GLuint lightIndicies[] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 4, 7,
        0, 7, 3,
        3, 7, 6,
        3, 6, 2,
        2, 6, 5,
        2, 5, 1,
        1, 5, 4,
        1, 4, 0,
        4, 5, 6,
        4, 6, 7
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

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(GLfloat), (void*)0); //first 3 numbers from verticies
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))); //next 3 nums
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat))); //next 2 nums
    VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(GLfloat), (void*)(8 * sizeof(GLfloat))); //next 2 nums
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    Shader lightShader("../shaders/light.vert", "../shaders/light.frag");
    VAO lightVAO;
    lightVAO.Bind();

    VBO lightVBO(lightVerticies, sizeof(lightVerticies));
    EBO lightEBO(lightIndicies, sizeof(lightIndicies));

    lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3*sizeof(GLfloat), (void*)0);

    lightVAO.Unbind();
    lightVBO.Unbind();
    lightEBO.Unbind();

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPos);

    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.getID(), "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.getID(), "lightColor"),lightColor.x,lightColor.y,lightColor.z,lightColor.w);

    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.getID(), "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
    glUniform4f(glGetUniformLocation(shaderProgram.getID(), "lightColor"),lightColor.x,lightColor.y,lightColor.z,lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.getID(), "lightPos"),lightPos.x,lightPos.y,lightPos.z);


    //Texture
    Texture superImage("../resources/images/earth.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    superImage.TexUnit(shaderProgram, "tex0", 0);

    glEnable(GL_DEPTH_TEST); //enable depth buffer, so we don't get random X-ray vision
    
    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.65f, 0.65f, 0.65f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Inputs(window);
        camera.updateMatrix(45.0f, 0.1f, 100.0f);
        shaderProgram.Activate();
        glUniform3f(glGetUniformLocation(shaderProgram.getID(), "camPos"), camera.Position.x,camera.Position.y,camera.Position.z);
        camera.Matrix(shaderProgram, "camMatrix");

        superImage.Bind();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indicies)/sizeof(int), GL_UNSIGNED_INT, 0); //not glDrawArrays, so EBO is used
        
        
        lightShader.Activate();
        camera.Matrix(lightShader, "camMatrix");
        lightVAO.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(lightIndicies)/sizeof(int), GL_UNSIGNED_INT,0);
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Deleting stuff
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    lightVAO.Delete();
    lightVBO.Delete();
    lightEBO.Delete();
    superImage.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}