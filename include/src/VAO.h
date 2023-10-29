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

 
    void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    /// @brief binds this VAO | makes this VAO the current one
    void Bind();
    /// @brief unbinds any VAO
    void Unbind();
    /// @brief deletes this VAO
    void Delete();
    
};

#endif // !VAO_CLASS_H