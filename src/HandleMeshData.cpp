#include "HandleMeshData.hpp"

HandleMeshData::HandleMeshData(void)
{

}

HandleMeshData::~HandleMeshData(void)
{

} 

void    HandleMeshData::handleMesh()
{
    Vertex vertices[] = {   Vertex(glm::vec3(-0.5, -0.5, 0.0), glm::vec2(2.0, 0.0)),
                        Vertex(glm::vec3(0.0, 0.5, 0.0), glm::vec2(0.0, -2.0)),
                        Vertex(glm::vec3(0.5, -0.5, 0.0), glm::vec2(-0.5, 0.0)) };

    Sprite sprite(vertices, sizeof(vertices) / sizeof(vertices[0]));
    sprite.draw();
}