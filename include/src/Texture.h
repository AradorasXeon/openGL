#ifndef TEXTURE_CLASS_FILE
#define TEXTURE_CLASS_FILE

#include "../glad/glad.h"
#include "shaderClass.h"



class Texture
{
    private:
    GLuint ID;
    GLenum type;
    public:
    Texture(const char* image, GLenum textureType, GLenum slot, GLenum format, GLenum pixelType);

    void TexUnit(Shader& shader, const char* uniform, GLuint unit);
    void Bind();
    void Unbind();
    void Delete();
};


#endif // !TEXTURE_CLASS_FILE
