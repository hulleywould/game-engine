#include "Sprite.hpp"

Sprite::Sprite(void)
{
    vaoID = 0;

}

Sprite::Sprite(const std::string &fileName)
{
    IndexedModel model = OBJModel(fileName).ToIndexedModel();
    initMesh(model);
}

Sprite::~Sprite(void)
{
    glDeleteVertexArrays(1, &vaoID);

}

Sprite::Sprite(Vertex *vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
    IndexedModel model;

    for(unsigned int i = 0; i < numVertices; i++){
        model.positions.push_back(*vertices[i].getPos());
        model.texCoords.push_back(*vertices[i].getTex());
    }

    for (unsigned int i = 0; i < numIndices; i++){
        model.indices.push_back(indices[i]); 
    }

    initMesh(model); 

}

void            Sprite::initMesh(const IndexedModel& model)
{
    drawCount = model.indices.size();

    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    glGenBuffers(NUM_BUFFERS, vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

 
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    

    //texture buffer
    glGenBuffers(NUM_BUFFERS, vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

 
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
    glBindVertexArray(0);
}

void    Sprite::draw()
{
    glBindVertexArray(vaoID);
    glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, drawCount);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
