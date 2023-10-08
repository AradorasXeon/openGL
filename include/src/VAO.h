#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include "../glad/glad.h"
#include "VBO.h"

class VAO
{
    private:
    GLuint ID;

    public:
    //Generates Vertex Array Object(s)
    VAO();

    /// @brief Links the VBO to the VAO
    /// @param VBO to be linked
    /// @param layout of the vertex atrib
    void LinkVBO(VBO VBO, GLuint layout);
    /// @brief binds this VAO | makes this VAO the current one
    void Bind();
    /// @brief unbinds any VAO
    void Unbind();
    /// @brief deletes this VAO
    void Delete();
    
};

#endif // !VAO_CLASS_H