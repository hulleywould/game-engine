#include "SpotLight.hpp"

SpotLight::SpotLight()
{

}

SpotLight::SpotLight(PointLight pointL, glm::vec3 dir, float cut):
pointLight(pointL),
direction(glm::normalize(dir)),
cutoff(cut)
{

}

SpotLight::~SpotLight()
{

}



//getters and setters
void        SpotLight::setPointLight(const PointLight& pointL)
{
    pointLight = pointL;
}

void        SpotLight::setDirection(const glm::vec3& dir)
{
    direction = glm::normalize(dir);
}

void        SpotLight::setCutOff(const float& cut)
{
    cutoff = cut;
}

PointLight& SpotLight::getPointLight()
{
    return pointLight;
}

glm::vec3&  SpotLight::getDirection()
{
    return direction;
}

float       SpotLight::getCutoff()
{
    return cutoff;
}