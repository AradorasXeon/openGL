#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include "../glad/glad.h"

class VBO
{
    private:
    GLuint ID;
    public:
    /// @brief Generates Vertex Buffer Object
    /// @param verticies into the VBO
    /// @param size of the verticies
    VBO(GLfloat* verticies, GLsizeiptr size);

    /// @brief binds the current VBO | makes the VBO the current one
    void Bind();
    /// @brief unbinds any buffer array
    void Unbind();
    /// @brief deletes this VBO
    void Delete();
};

#endif // !VBO_CLASS_H