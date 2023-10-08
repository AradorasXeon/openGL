#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include "../glad/glad.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

/// @brief 
/// @param filename the file content we want as string
/// @return the file's content as a string 
std::string get_file_content(const char* filename);

/// @brief class for shader program
class Shader
{
    private:
    GLuint ID;
    void compileErrors(unsigned int shader, const char* type);

    public:
    /// @brief creates the shader program from the vertex and frag files
    /// @param vertexFile path to vertex file
    /// @param fragFile path to fragment file
    Shader(const char* vertexFile, const char* fragFile);

    /// @brief activates the shader program
    void Activate();
    /// @brief deletes the sahder program
    void Delete();
    /// @brief 
    /// @returns handle ID 
    GLuint getID();
};

#endif