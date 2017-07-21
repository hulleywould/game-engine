#ifndef SPRITE_HPP
# define SPRITE_HPP

#include <GL/glew.h>
#include "vertex.h"
#include <cstddef>
#include <iostream>

class Sprite {

    public:
        Sprite(void);
        ~Sprite(void);

        void    init(float x, float y, float z, float width, float height);
        void    init2(Vertex *vertices, unsigned int numVertices);

        void    draw();

    private:
        enum {
            POSITION_VB,
            NUM_BUFFERS
        };
        float             x;
        float             y;
        float             z;
        float             width;
        float             height;
        GLuint          vaoID; //vertex array object ID.
        GLuint          vboID[POSITION_VB]; //vertext buffer object ID. GLuint guaranteed to be 32bits
        unsigned int    drawCount;
        
};

#endif