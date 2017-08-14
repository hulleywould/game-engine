#include "Shader.hpp"

Shader::Shader(void)
{

}

Shader::~Shader(void)
{

}

void    Shader::initializeShader()
{
    compileShaders("src/shaders/colorShading.vert", "src/shaders/colorShading.frag");
    addAttribute("position");
    addAttribute("texCoord");
    addAttribute("normal");
    linkShaders();

    addUniform("transform");
    addUniform("color");
}

void    Shader::update(const Transform &transform, const Camera &camera, Material &material)
{
    //glm::mat4 modelViewProjection = camera.getViewProjection() * camera.getWorldToView() * transform.getModel();
    glm::mat4 modelViewProjection = camera.getViewProjection() * camera.getWorldToView() * transform.getTransformation();    
    setUniform("transform", modelViewProjection);
    setUniform("color", material.getColor());
}