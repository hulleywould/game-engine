#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Texture::Texture(const std::string &fileName)
{
    int width, height, numComponents;
    
    unsigned char *imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, STBI_rgb_alpha);

    if (imageData == NULL)
        std::cerr << "loading texture " << fileName << " failed." << std::endl;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    std::cout << "texture id is: " << textureID << std::endl;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    stbi_image_free(imageData);  
}

Texture::~Texture(void)
{
    glDeleteTextures(1, &textureID);
}

void    Texture::useTexture()
{
    glBindTexture(GL_TEXTURE_2D, textureID);
}