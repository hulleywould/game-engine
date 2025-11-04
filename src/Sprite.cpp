#include "Sprite.hpp"
#include <iostream>

Sprite::Sprite(void)
{
}

Sprite::Sprite(const std::string &fileName)
{
    std::cout << "Loading OBJ file: " << fileName << std::endl;
    OBJModel objModel(fileName);
    std::cout << "Parsing OBJ to IndexedModel..." << std::endl;
    IndexedModel model = objModel.ToIndexedModel();
    std::cout << "Model loaded: " << model.positions.size() << " positions, " 
              << model.indices.size() << " indices" << std::endl;
    initMesh(model);
    std::cout << "Sprite constructor complete, returning..." << std::endl;
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
    std::cout << "initMesh: Starting with " << model.positions.size() << " positions" << std::endl;
    drawCount = model.indices.size();

    if(model.positions.empty() || model.indices.empty())
    {
        std::cerr << "ERROR: Model has no positions or indices!" << std::endl;
        return;
    }

    // Clear any pre-existing OpenGL errors
    while(glGetError() != GL_NO_ERROR);
    
    std::cout << "initMesh: Generating VAO..." << std::endl;
    vaoID = 0;
    glGenVertexArrays(1, &vaoID);
    GLenum err = glGetError();
    if(err != GL_NO_ERROR || vaoID == 0) {
        std::cerr << "ERROR generating VAO: " << err << ", vaoID=" << vaoID << std::endl;
        return;
    }
    
    std::cout << "initMesh: Binding VAO " << vaoID << "..." << std::endl;
    glBindVertexArray(vaoID);
    
    err = glGetError();
    if(err != GL_NO_ERROR) {
        std::cerr << "ERROR binding VAO: " << err << std::endl;
        return;
    }
    std::cout << "initMesh: VAO bound successfully" << std::endl;

    std::cout << "initMesh: Generating " << NUM_BUFFERS << " VBOs..." << std::endl;
    glGenBuffers(NUM_BUFFERS, vboID);
    std::cout << "initMesh: VBOs generated" << std::endl;
    
    // Position buffer
    std::cout << "initMesh: Setting up position buffer..." << std::endl;
    glBindBuffer(GL_ARRAY_BUFFER, vboID[POSITION_VB]);
    std::cout << "initMesh: Allocating position buffer (" << (model.positions.size() * sizeof(model.positions[0])) << " bytes)..." << std::endl;
    glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    std::cout << "initMesh: Position buffer complete" << std::endl;

    // Texture coordinate buffer
    std::cout << "initMesh: Setting up texcoord buffer (has " << model.texCoords.size() << " texcoords)..." << std::endl;
    glBindBuffer(GL_ARRAY_BUFFER, vboID[TEXCOORD_VB]);
    if(!model.texCoords.empty())
    {
        std::cout << "initMesh: Allocating texcoord buffer..." << std::endl;
        glBufferData(GL_ARRAY_BUFFER, model.texCoords.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_DYNAMIC_DRAW);
        std::cout << "initMesh: Texcoord buffer allocated" << std::endl;
    }
    else
    {
        // Create dummy tex coords if none exist
        std::cout << "initMesh: Creating dummy texcoords..." << std::endl;
        std::vector<glm::vec2> dummyTexCoords(model.positions.size(), glm::vec2(0.0f, 0.0f));
        glBufferData(GL_ARRAY_BUFFER, dummyTexCoords.size() * sizeof(dummyTexCoords[0]), &dummyTexCoords[0], GL_DYNAMIC_DRAW);
        std::cout << "initMesh: Dummy texcoords created" << std::endl;
    }
    std::cout << "initMesh: Enabling texcoord attribute..." << std::endl;
    glEnableVertexAttribArray(1);
    std::cout << "initMesh: Setting texcoord pointer..." << std::endl;
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    std::cout << "initMesh: Texcoord buffer complete" << std::endl;

    // Normal buffer
    std::cout << "initMesh: Setting up normal buffer (has " << model.normals.size() << " normals)..." << std::endl;
    glBindBuffer(GL_ARRAY_BUFFER, vboID[NORMAL_VB]);
    if(!model.normals.empty())
    {
        std::cout << "initMesh: Allocating normal buffer (" << (model.normals.size() * sizeof(model.normals[0])) << " bytes)..." << std::endl;
        glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_DYNAMIC_DRAW);
        std::cout << "initMesh: Normal buffer allocated" << std::endl;
    }
    else
    {
        // Create dummy normals if none exist
        std::cout << "initMesh: Creating dummy normals..." << std::endl;
        std::vector<glm::vec3> dummyNormals(model.positions.size(), glm::vec3(0.0f, 0.0f, 1.0f));
        glBufferData(GL_ARRAY_BUFFER, dummyNormals.size() * sizeof(dummyNormals[0]), &dummyNormals[0], GL_DYNAMIC_DRAW);
    }
    std::cout << "initMesh: Enabling normal attribute..." << std::endl;
    glEnableVertexAttribArray(2);
    std::cout << "initMesh: Setting normal pointer..." << std::endl;
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    std::cout << "initMesh: Normal buffer complete" << std::endl;

    // Index buffer
    std::cout << "initMesh: Setting up index buffer (" << model.indices.size() << " indices)..." << std::endl;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID[INDEX_VB]);
    std::cout << "initMesh: Allocating index buffer..." << std::endl;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_DYNAMIC_DRAW);
    std::cout << "initMesh: Index buffer complete" << std::endl;

    std::cout << "initMesh: Unbinding VAO..." << std::endl;
    glBindVertexArray(0);
    std::cout << "initMesh: Mesh initialization complete!" << std::endl;
}

void    Sprite::draw()
{
    glBindVertexArray(vaoID);
    glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}