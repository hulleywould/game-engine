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

void    Shader::updateShader(const Transform &transform, const Camera &camera, Material &material)
{
    update(transform, camera, material);
}