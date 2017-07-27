#ifndef VERTEX_HPP
# define VERTEX_HPP

#include <glm/glm.hpp>

class Vertex {

    public:
        Vertex(const glm::vec3 &pos, const glm::vec2&, const glm::vec3 &normal = glm::vec3(0,0,0));
        ~Vertex(void);
        glm::vec3    *getPos();
        glm::vec2    *getTex();
        glm::vec3    *getNormal();

    private:
        glm::vec3   position;
        glm::vec2   texCoord;
        glm::vec3   normal;
};

#endif // !VERTEX_HPP
