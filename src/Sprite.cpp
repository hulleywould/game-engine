#include "Sprite.hpp"

Sprite::Sprite(void)
{
    vboID = 0;
}
Sprite::~Sprite(void)
{
    if (vboID != 0)
    {
        glDeleteBuffers(1, &vboID);
    }

}

void    Sprite::init(float xpos, float ypos, float objWidth, float objHeight)
{
    x = xpos;
    y = ypos;
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

    vertexData[1].position.x = x;
    vertexData[1].position.y = y + objHeight;

    vertexData[2].position.x = x;
    vertexData[2].position.y = y;

    //second triangle
    vertexData[3].position.x = x;
    vertexData[3].position.y = y;

    vertexData[4].position.x = x + objWidth;
    vertexData[4].position.y = y;

    vertexData[5].position.x = x + objWidth;
    vertexData[5].position.y = y + objHeight;

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

    vertexData[4].color.r = 0;
    vertexData[4].color.g = 255;
    vertexData[4].color.b = 0;
    vertexData[4].color.a = 255;

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);


}
void    Sprite::draw()
{
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    glEnableVertexAttribArray(0);

    //Posotion attribute pointer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));

     //Color attribute pointer
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, color));

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}