#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include "../glad/glad.h"

class EBO
{
    private:
    GLuint ID;

    public:
    /// @brief Generates EBO
    /// @param indicies of EBO
    /// @param size of indicies
    EBO(GLuint* indicies, GLsizeiptr size);

    /// @brief binds EBO | makes this EBO the current one
    void Bind();
    /// @brief unbinds any EBO
    void Unbind();
    /// @brief deletes this EBO
    void Delete();
};

#endif // !EBO_CLASS_H