#include <iostream>
#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>

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

    glViewport(0,0,450,600); //hm so far this does nothing, or so it seems
    glClearColor(0.25f, 0.82f, 0.83f, 1.0f);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }


    glfwDestroyWindow(window);
    glfwTerminate();


    return 0;
}