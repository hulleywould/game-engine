#include "PhongShader.hpp"

PhongShader::PhongShader(void):
ambientLight(glm::vec3(0,0,0))
{

}

PhongShader::~PhongShader(void)
{

}

void    PhongShader::initializeShader()
{
    compileShaders("src/shaders/phongShading.vert", "src/shaders/phongShading.frag");
    addAttribute("position");
    addAttribute("texCoord");
    addAttribute("normal");
    linkShaders();

    addUniform("transform");
    addUniform("baseColor");
    addUniform("ambientLight");
}

void    PhongShader::update(const Transform &transform, const Camera &camera, Material &material)
{
    glm::mat4 modelViewProjection = camera.getViewProjection() * transform.getModel();
    setUniform("transform", modelViewProjection);
    setUniform("baseColor", material.getColor());
    setUniform("ambientLight", ambientLight);
}

void    PhongShader::setAmbientLight(const glm::vec3 &ambience)
{
    ambientLight = ambience;
}

glm::vec3& PhongShader::getAmbientLight()
{
    return ambientLight;
}