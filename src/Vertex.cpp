#include "Vertex.hpp"

Vertex::Vertex(const glm::vec3 &pos, const glm::vec2 &texPos)
{
    position = pos;
    texCoord = texPos;
}

glm::vec3*    Vertex::getPos()
{
    return &position;
}

glm::vec2*    Vertex::getTex()
{
    return &texCoord;
}