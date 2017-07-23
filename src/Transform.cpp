#include "Transform.hpp"

Transform::Transform(void)
{
    position = glm::vec3(0.0,0.0,0.0);
    rotation = glm::vec3(0.0,0.0,0.0);
    scale = glm::vec3(1.0, 1.0, 1.0);
}

Transform::Transform(const glm::vec3 &pos, const glm::vec3 &rot, const glm::vec3 &scaling) :
position(pos),
rotation(rot),
scale(scaling)
{

}


glm::mat4   Transform::getModel() const
{
    glm::mat4 posMatrix = glm::translate(position);
    glm::mat4 rotxMatrix = glm::rotate(rotation.x, glm::vec3(1.0, 0.0, 0.0));
    glm::mat4 rotyMatrix = glm::rotate(rotation.y, glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 rotzMatrix = glm::rotate(rotation.z, glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 scaleMatrix = glm::scale(scale);
    //matrices must be multiplied in reverse order to work 
    glm::mat4 rotMatrix = rotzMatrix * rotyMatrix * rotxMatrix; 
    return posMatrix * rotMatrix * scaleMatrix;
}


Transform::~Transform(void)
{

}

//getters and setters

glm::vec3&  Transform::getPos()
{
    return position;
}

glm::vec3&  Transform::getRot()
{
    return rotation;
}

glm::vec3&  Transform::getScale()
{
    return scale;
}

void        Transform::setPos(const glm::vec3 &pos)
{
    position = pos;
}

void        Transform::setRot(const glm::vec3 &rot)
{
    rotation = rot;
}

void        Transform::setScale(const glm::vec3 &scaling)
{
    scale = scaling;
}

