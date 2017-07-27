#include "Vertex.hpp"

Vertex::Vertex(const glm::vec3 &pos, const glm::vec2 &texPos, const glm::vec3 &norm)
{
    position = pos;
    texCoord = texPos;
    normal = norm;
}

Vertex::~Vertex(void)
{
    
}

glm::vec3*    Vertex::getPos()
{
    return &position;
}

glm::vec2*    Vertex::getTex()
{
    return &texCoord;
}

glm::vec3*   Vertex::getNormal()
{
    return &normal;
}