#include "Material.hpp"

Material::Material(void)
{

}

Material::Material(const Texture& myTexture, const glm::vec3& myColor)
{
    texture = myTexture;
    color = myColor;
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