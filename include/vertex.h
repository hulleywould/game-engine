#ifndef VERTEX_H
# define VERTEX_H

#include <GL/glew.h>
#include <glm/glm.hpp>

/*struct          Position {
    float       x;
    float       y;
    float       z;
};*/

struct          Color {
    GLubyte     r;
    GLubyte     g;
    GLubyte     b;
    GLubyte     a;     
};

struct          Vertex {
    glm::vec3   position;
    //Position    position;
    Color       color;
        
};

#endif