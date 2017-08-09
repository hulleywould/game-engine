#include "PhongShader.hpp"

PhongShader::PhongShader(void):
ambientLight(glm::vec3(0,0,0))
{
    DirectionalLight directionalLight(BaseLight(glm::vec3(1.0f, 1.0f, 1.0f), 2.0f), glm::vec3(1.0f, 1.0f, 1.0f));
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
    addUniform("directionalLight.base.color");
    addUniform("directionalLight.base.intensity");
    addUniform("directionalLight.direction");
    addUniform("specularIntensity");
    addUniform("specularPower");
    addUniform("eyePos");
    
}

void    PhongShader::update(const Transform &transform, Camera &camera, Material &material)
{
    glm::mat4 modelViewProjection = camera.getViewProjection() * transform.getModel();
    setUniform("transform", modelViewProjection);
    setUniform("baseColor", material.getColor());
    setUniformf("specularIntensity", material.getSpecularIntensity());
    setUniformf("specularPower", material.getSpecularPower());
    setUniform("eyePos", camera.getCameraPos());
    setUniform("ambientLight", ambientLight);
    setUniform("directionalLight", directionalLight);
}


void    PhongShader::setAmbientLight(const glm::vec3 &ambience)
{
    ambientLight = ambience;
}

glm::vec3& PhongShader::getAmbientLight()
{
    return ambientLight;
}

void    PhongShader::setDirectionalLight(const DirectionalLight &dir)
{
    directionalLight = dir;
}

DirectionalLight&   PhongShader::getDirectionalLight()
{
    return directionalLight;
} 