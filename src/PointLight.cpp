#include "PointLight.hpp"

PointLight::PointLight()
{

}

PointLight::PointLight(BaseLight b, Attenuation at, glm::vec3 pos, float rang):
base(b),
atten(at),
position(pos),
range(rang)
{

}

PointLight::~PointLight()
{

}

void        PointLight::setBase(const BaseLight &b)
{
    base = b;
}

void        PointLight::setAttenuation(const Attenuation &at)
{
    atten = at;
}

void        PointLight::setPosition(const glm::vec3 &pos)
{
    position = pos;
}

void        PointLight::setRange(const float &rang)
{
    range = rang;
}


BaseLight&  PointLight::getBase()
{
    return base;
}

Attenuation&  PointLight::getAttenuation()
{
    return atten;
}

glm::vec3&  PointLight::getPosition()
{
    return position;
}

float&  PointLight::getRange()
{
    return range;
}