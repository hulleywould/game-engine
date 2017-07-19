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

    float vertexData[12];

    //first traingle
    vertexData[0] = x + objWidth;
    vertexData[1] = y + objWidth;

    vertexData[2] = x;
    vertexData[3] = y + objHeight;

    vertexData[4] = x;
    vertexData[5] = y;

    //second triangle
    vertexData[6] = x;
    vertexData[7] = y;

    vertexData[8] = x + objWidth;
    vertexData[9] = y;

    vertexData[10] = x + objWidth;
    vertexData[11] = y + objHeight;

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);


}
void    Sprite::draw()
{
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}