#include "Vector.hpp"

Vector::Vector(void)
{

}

Vector::Vector(float xpos, float ypos):
x(xpos),
y(ypos)
{

}

Vector::Vector(float xpos, float ypos, float zpos):
x(xpos),
y(ypos),
z(zpos)
{

}

Vector::Vector(float xpos, float ypos, float zpos, float wpos):
x(xpos),
y(ypos),
z(zpos),
w(wpos)
{

}

Vector::~Vector(void)
{

}

Vector  Vector::rotate(float angle, Vector axis)
{
    float sinHalfAngle = (float)sin(glm::radians(angle / 2));
    float cosHalfAngle = (float)cos(glm::radians(angle / 2));
    float rX = axis.getX() * sinHalfAngle;
    float rY = axis.getY() * sinHalfAngle;
    float rZ = axis.getZ() * sinHalfAngle;
    float rW = cosHalfAngle;

    return axis;
}    

//getters and setters
void    Vector::setX(const float& xpos)
{
    x = xpos;
}

void    Vector::setY(const float& ypos)
{
    y = ypos;
}

void    Vector::setZ(const float& zpos)
{
    z = zpos;
}

void    Vector::setW(const float& wpos)
{
    w = wpos;
}

float&  Vector::getX()
{
    return x;
}

float&  Vector::getY()
{
    return y;
}

float&  Vector::getZ()
{
    return z;
}

float&  Vector::getW()
{
    return w;
}