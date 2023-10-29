#include "../include/src/Texture.h"

#ifndef STB_IMAGE_IMPLEMENTATION
    #define STB_IMAGE_IMPLEMENTATION
#endif // !STB_IMAGE_IMPLEMENTATION

#include "../include/stb/stb_image.h" //for some reason you cannot define it in a .h file

Texture::Texture(const char* image, GLenum textureType, GLenum slot, GLenum format, GLenum pixelType)
{
    type = textureType;
    int widthImage, heightImage, numOfColChan;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(image, &widthImage, &heightImage, &numOfColChan, 0);

    glGenTextures(1, &ID);
    glActiveTexture(slot);
    glBindTexture(textureType, ID);
    glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f}
    //glTexParameterfv(textureType, GL_TEXTURE_BORDER_COLOR, flatColor);

    glTexImage2D(textureType, 0, GL_RGBA, widthImage, heightImage, 0, format, pixelType, bytes);
    glGenerateMipmap(textureType);

    stbi_image_free(bytes);
    glBindTexture(textureType, 0);
};

void Texture::TexUnit(Shader& shader, const char* uniform, GLuint unit)
{
    GLuint tex0Uni = glGetUniformLocation(shader.getID(), "tex0");
    shader.Activate();
    glUniform1i(tex0Uni, unit);
};

void Texture::Bind()
{
    glBindTexture(type, ID);
};

void Texture::Unbind()
{
    glBindTexture(type, 0);
};

void Texture::Delete()
{
    glDeleteTextures(1, &ID);
};

