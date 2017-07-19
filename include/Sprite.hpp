#ifndef SPRITE_HPP
# define SPRITE_HPP

#include <GL/glew.h>

class Sprite {

    public:
        Sprite(void);
        ~Sprite(void);

        void    init(float x, float y, float width, float height);

        void    draw();

    private:
        float             x;
        float             y;
        float             width;
        float             height;
        GLuint          vboID; //vertext buffer object ID. GLuint guaranteed to be 32bits
        
};

#endif