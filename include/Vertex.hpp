#ifndef VERTEX_HPP
# define VERTEX_HPP

#include <glm/glm.hpp>

class Vertex {

    public:
        Vertex(const glm::vec3 &pos, const glm::vec2&);
        ~Vertex(void);
        glm::vec3    *getPos();
        glm::vec2    *getTex();

    private:
        glm::vec3   position;
        glm::vec2   texCoord;
};

#endif // !VERTEX_HPP
