#include "Material.hpp"

Material::Material(void)
{

}

Material::Material(const Texture& myTexture, const glm::vec3& myColor)
{
    texture = myTexture;
    color = myColor;
    specularIntensity = 2.0f;
    specularPower = 32.0f;
}

Material::Material(const Texture& tex, 
                const glm::vec3& col,
                const float& specularIntense,
                const float& specularPow)
{
    texture = tex;
    color = col;
    specularIntensity = specularIntense;
    specularPower = specularPow;

}


Material::~Material(void)
{

}

Texture&    Material::getTexture()
{
    return texture;
}

glm::vec3&  Material::getColor()
{
    return color;
}

float&      Material::getSpecularIntensity()
{
    return specularIntensity;
}

float&      Material::getSpecularPower()
{
    return specularPower;
}
