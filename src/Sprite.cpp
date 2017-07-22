#include "Sprite.hpp"

Sprite::Sprite(void)
{
    vaoID = 0;

}
Sprite::~Sprite(void)
{
    glDeleteVertexArrays(1, &vaoID);

}

Sprite::Sprite(Vertex *vertices, unsigned int numVertices)
{
    drawCount = numVertices;

    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;

    positions.reserve(numVertices);
    texCoords.reserve(numVertices);

    for (unsigned int i = 0; i < numVertices; i++) {
        positions.push_back(*vertices[i].getPos());
        texCoords.push_back(*vertices[i].getTex());
    }

    //position buffer
    glGenBuffers(NUM_BUFFERS, vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

 
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    

    //texture buffer
    glGenBuffers(NUM_BUFFERS, vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);

 
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
    glBindVertexArray(0);
}

void    Sprite::draw()
{
    glBindVertexArray(vaoID);
    glDrawArrays(GL_TRIANGLES, 0, drawCount);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
