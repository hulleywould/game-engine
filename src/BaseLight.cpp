#include "BaseLight.hpp"

BaseLight::BaseLight()
{

}

BaseLight::BaseLight(glm::vec3 col, float intense):
color(col),
intensity(intense)
{

}

BaseLight::~BaseLight()
{

}

void        BaseLight::setColor(const glm::vec3 &col)
{
    color = col;
}

void        BaseLight::setIntensity(const float &intense)
{
    intensity = intense;
}

glm::vec3&  BaseLight::getColor()
{
    return color;
}

float&      BaseLight::getIntensity()
{
    return intensity;
}