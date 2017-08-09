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
    for (int i = 0; i < MAX_POINT_LIGHT; i++)
    {
        addUniform("pointLights[" + std::to_string(i) + "].base.color");
        addUniform("pointLights[" + std::to_string(i) + "].base.intensity");
        addUniform("pointLights[" + std::to_string(i) + "].atten.constant");
        addUniform("pointLights[" + std::to_string(i) + "].atten.constant");
        addUniform("pointLights[" + std::to_string(i) + "].atten.linear");
        addUniform("pointLights[" + std::to_string(i) + "].atten.exponent");
        addUniform("pointLights[" + std::to_string(i) + "].position");
    }
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
    for (int i = 0; i < MAX_POINT_LIGHT; i++)
    {
        setUniform("pointLights[" + std::to_string(i) + "]", pointLights[i]);
    }
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

void    PhongShader::setPointLight(PointLight *pointLight)
{
    if ((sizeof(pointLight) / sizeof(pointLight[0])) > MAX_POINT_LIGHT)
    {
        std::cout << "Error: too many point lights. Max is: " << MAX_POINT_LIGHT << std::endl;
        exit(0);
    }

    pointLights = pointLight;
}

PointLight&         PhongShader::getPointLight()
{
    return *pointLights;
}


