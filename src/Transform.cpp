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
scale(scaling),
translation(glm::vec3(0,0,0))
{

}


glm::mat4   Transform::getTransformation() const
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

glm::mat4   Transform::getProjectedTransformation() const
{   
    glm::mat4 transformationMatrix = getTransformation();
    glm::mat4 projectionMatrix = glm::perspective(fov, width / height, zNear, zFar);

    return projectionMatrix * transformationMatrix;
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

glm::vec3&  Transform::getTranslation()
{
    return translation;
}

void        Transform::setTranslation(float x, float y, float z)
{
    translation = glm::vec3(x,y,z);
}

void        Transform::setProjection(float fieldOfView, float w, float h, float near, float far)
{
    zNear = near;
    zFar = far;
    width = w;
    height = h;
    fov = fieldOfView;
}

