#ifndef TEXTURE_HPP
# define TEXTURE_HPP

#include <string>
#include <GL/glew.h>
#include <iostream>
#include <cassert>

class Texture {

    public:
        Texture(void);
        Texture(const std::string &fileName);
        ~Texture(void);

        void useTexture();
    private:
        GLuint  textureID;


};

#endif