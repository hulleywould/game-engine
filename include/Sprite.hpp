#ifndef SPRITE_HPP
# define SPRITE_HPP

#include <GL/glew.h>
#include <cstddef>
#include <string>
#include <iostream>
#include <vector>
#include "Vertex.hpp"
#include "obj_loader.h"

class Sprite {

    public:
        Sprite(void);
        Sprite(Vertex *vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
        Sprite(const std::string &fileName);
        ~Sprite(void);
        void    draw();

    private:
        enum {
            POSITION_VB,
            TEXCOORD_VB,
            INDEX_VB,
            NUM_BUFFERS
        };
        void            initMesh(const IndexedModel& model);
        GLuint          vaoID; //vertex array object ID.
        GLuint          vboID[POSITION_VB]; //vertext buffer object ID. GLuint guaranteed to be 32bits
        unsigned int    drawCount;
        
};

#endif