#ifndef SPRITE_HPP
# define SPRITE_HPP

#include <GL/glew.h>
#include <cstddef>
#include <iostream>
#include <vector>
#include "Vertex.hpp"

class Sprite {

    public:
        Sprite(void);
        Sprite(Vertex *vertices, unsigned int numVertices);
        ~Sprite(void);
        void    draw();

    private:
        enum {
            POSITION_VB,
            TEXCOORD_VB,
            NUM_BUFFERS
        };
        GLuint          vaoID; //vertex array object ID.
        GLuint          vboID[POSITION_VB]; //vertext buffer object ID. GLuint guaranteed to be 32bits
        unsigned int    drawCount;
        
};

#endif