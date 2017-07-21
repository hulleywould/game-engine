#include "Sprite.hpp"

Sprite::Sprite(void)
{
    //vboID = 0;
    vaoID = 0;
    drawCount = 0;
}
Sprite::~Sprite(void)
{
    /*if (vboID != 0)
    {
        glDeleteBuffers(1, &vboID);
    }*/
    glDeleteVertexArrays(1, &vaoID);

}

/*void    Sprite::init(float xpos, float ypos, float zpos, float objWidth, float objHeight)
{
    x = xpos;
    y = ypos;
    z = zpos;
    width = objWidth;
    height = objHeight;

    if (vboID == 0)
    {
        glGenBuffers(1, &vboID);
    }

    Vertex vertexData[6];

    //first traingle
    vertexData[0].position.x = x + objWidth;
    vertexData[0].position.y = y + objWidth;
    vertexData[0].position.z = z;

    vertexData[1].position.x = x;
    vertexData[1].position.y = y + objHeight;
    vertexData[1].position.z = z;

    vertexData[2].position.x = x;
    vertexData[2].position.y = y;
    vertexData[2].position.z = z;

    //second triangle
    vertexData[3].position.x = x;
    vertexData[3].position.y = y;
    vertexData[3].position.z = z;

    vertexData[4].position.x = x + objWidth;
    vertexData[4].position.y = y;
    vertexData[4].position.z = z;

    vertexData[5].position.x = x + objWidth;
    vertexData[5].position.y = y + objHeight;
    vertexData[5].position.z = z;

    for (int i = 0; i < 6; i++)
    {
        vertexData[i].color.r = 255;
        vertexData[i].color.g = 0;
        vertexData[i].color.b = 255;
        vertexData[i].color.a = 255;
    }

    vertexData[1].color.r = 0;
    vertexData[1].color.g = 0;
    vertexData[1].color.b = 255;
    vertexData[1].color.a = 255;

    vertexData[2].color.r = 0;
    vertexData[2].color.g = 255;
    vertexData[2].color.b = 0;
    vertexData[2].color.a = 255;

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);


}*/

void    Sprite::init2(Vertex *vertices, unsigned int numVertices)
{
    drawCount = numVertices;
    /*if (vboID == 0)
    {
        glGenBuffers(1, &vboID);
    }*/

    std::cout << "drawcount: " << drawCount << std::endl;
    std::cout << "numVertices: " << numVertices << std::endl;

    std::cout << "before gen vertex arrays " << vaoID << std::endl;
    if (glGenVertexArrays == NULL) {
        std::cout << "gl gen vertex arrays is null" << std::endl;
    }
    glGenVertexArrays(1, &vaoID);

    std::cout << "gen vertex arrays" << std::endl;

    glBindVertexArray(vaoID);

    std::cout << "bind vertex arrays" << std::endl;

    glGenBuffers(NUM_BUFFERS, vboID);

    std::cout << "gen buffers" << std::endl;

    glBindBuffer(GL_ARRAY_BUFFER, vboID[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindVertexArray(0);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void    Sprite::draw()
{
    glBindVertexArray(vaoID);

    glDrawArrays(GL_TRIANGLES, 0, drawCount);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/*
original draw

void    Sprite::draw()
{
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    glEnableVertexAttribArray(0);

    //Posotion attribute pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));

     //Color attribute pointer
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, color));

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}*/