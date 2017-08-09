#include "Sprite.hpp"

Sprite::Sprite(void)
{
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
        model.normals.push_back(*vertices[i].getNormal());
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
    glBindBuffer(GL_ARRAY_BUFFER, vboID[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    //normal buffer
    glBindBuffer(GL_ARRAY_BUFFER, vboID[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

    

    glBindVertexArray(0);
}

void    Sprite::draw()
{
    glBindVertexArray(vaoID);
    glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/*void    Sprite::calcNormals(Vertex *vertices, unsigned int *indices)
{
    Math math;
    for (int i = 0; i < (sizeof(indices) / sizeof(*indices)); i++)
    {
        int i0 = indices[i];
        int i1 = indices[i + 1];
        int i2 = indices[i + 2];

        glm::vec3 v1 = vertices[i1].getPos() - vertices[i0].getPos();
        glm::vec3 v2 = vertices[i2].getPos() - vertices[i0].getPos();

        glm::vec3 normal = glm::fastNormalize(glm::cross(v1, v2));
    }
}*/