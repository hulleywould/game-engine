#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight()
{

}

DirectionalLight::DirectionalLight(BaseLight b, glm::vec3 dir):
base(b),
direction(glm::normalize(dir))
{

}

DirectionalLight::~DirectionalLight()
{

}

void        DirectionalLight::setBase(const BaseLight &b)
{
    base = b;
}

void        DirectionalLight::setDirection(const glm::vec3 &direc)
{
    direction = glm::normalize(direc);
}

BaseLight&  DirectionalLight::getBase()
{
    return base;
}

glm::vec3&  DirectionalLight::getDirection()
{
    return direction;
}