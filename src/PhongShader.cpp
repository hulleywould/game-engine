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
    addUniform("transformProjected");
    addUniform("baseColor");
    addUniform("ambientLight");
    addUniform("directionalLight.base.color");
    addUniform("directionalLight.base.intensity");
    addUniform("directionalLight.direction");
    addUniform("specularIntensity");
    addUniform("specularPower");
    addUniform("eyePos");
    //pointLights
    for (int i = 0; i < MAX_POINT_LIGHT; i++)
    {
        addUniform("pointLights[" + std::to_string(i) + "].base.color");
        addUniform("pointLights[" + std::to_string(i) + "].base.intensity");
        addUniform("pointLights[" + std::to_string(i) + "].atten.constant");
        addUniform("pointLights[" + std::to_string(i) + "].atten.constant");
        addUniform("pointLights[" + std::to_string(i) + "].atten.linear");
        addUniform("pointLights[" + std::to_string(i) + "].atten.exponent");
        addUniform("pointLights[" + std::to_string(i) + "].position");
        addUniform("pointLights[" + std::to_string(i) + "].range");
        
    }
    //spotLights
    for (int i = 0; i < MAX_SPOT_LIGHT; i++)
    {
        addUniform("spotLights[" + std::to_string(i) + "].pointLight.base.color");
        addUniform("spotLights[" + std::to_string(i) + "].pointLight.base.intensity");
        addUniform("spotLights[" + std::to_string(i) + "].pointLight.atten.constant");
        addUniform("spotLights[" + std::to_string(i) + "].pointLight.atten.constant");
        addUniform("spotLights[" + std::to_string(i) + "].pointLight.atten.linear");
        addUniform("spotLights[" + std::to_string(i) + "].pointLight.atten.exponent");
        addUniform("spotLights[" + std::to_string(i) + "].pointLight.position");
        addUniform("spotLights[" + std::to_string(i) + "].pointLight.range");
        addUniform("spotLights[" + std::to_string(i) + "].direction");
        addUniform("spotLights[" + std::to_string(i) + "].cutoff");
    }

}

void    PhongShader::update(const Transform &transform, Camera &camera, Material &material)
{
    glm::mat4 modelViewProjection = camera.getViewProjection() * camera.getWorldToView() * transform.getTransformation();
    glm::mat4 worldView = transform.getProjectedTransformation();
    setUniform("transform", worldView);
    setUniform("transformProjected", modelViewProjection);
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
    for (int i = 0; i < MAX_SPOT_LIGHT; i++)
    {
        setUniform("spotLights[" + std::to_string(i) + "]", spotLights[i]);
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

void    PhongShader::setPointLight(std::vector<PointLight> pointLight)
{
    if (pointLight.size() > MAX_POINT_LIGHT)
    {
        std::cout << "Error: too many point lights. Max is: " << MAX_POINT_LIGHT << std::endl;
        exit(0);
    }

    pointLights = pointLight;
}

std::vector<PointLight>&    PhongShader::getPointLight()
{
    return pointLights;
}

void    PhongShader::setSpotLight(std::vector<SpotLight> spotLight)
{
    if (spotLight.size() > MAX_SPOT_LIGHT)
    {
        std::cout << "Error: too many spot lights. Max is: " << MAX_SPOT_LIGHT << std::endl;
        exit(0);
    }

    spotLights = spotLight;
}

std::vector<SpotLight>&    PhongShader::getSpotLight()
{
    return spotLights;
}

