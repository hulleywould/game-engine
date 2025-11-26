#ifndef GLSLPROGRAM_HPP
# define GLSLPROGRAM_HPP

#include <string>
#include <map>
#include <iostream>
#include <GL/glew.h>
#include <fstream>
#include <vector>
#include "Transform.hpp"
#include "Camera.hpp"
#include "Material.hpp"
#include "DirectionalLight.hpp"
#include "BaseLight.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"

class GlslProgram {
    public:
        GlslProgram(void);
        ~GlslProgram(void);

        void    compileShaders(const std::string &vertexShaderFilePath,
                            const std::string &fragmentShaderFilePath);
        void    linkShaders();
        void    addAttribute(const std::string attributeName);
        void    use();
        void    unuse();
        void    update(const Transform &transform, const Camera &camera, Material &material);
        void    addUniform(const std::string &uniformName);
        void    setUniformi(const std::string &uniformName, int value);
        void    setUniformf(const std::string &uniformName, float value);
        void    setUniform(const std::string &uniformName, glm::vec2 value);
        void    setUniform(const std::string &uniformName, glm::vec3 value);
        void    setUniform(const std::string &uniformName, glm::mat4 value);
        void    setUniform(const std::string &uniformName, PointLight pointlight);
        void    setUniform(const std::string &uniformName, DirectionalLight directionalLight);
        void    setUniform(const std::string &uniformName, BaseLight baselight);
        void    setUniform(const std::string &uniformName, SpotLight spotLight);
        
        std::map<std::string, int> uniformMap;

    private:
        GLuint  programID;
        GLuint  vertexShaderID;
        GLuint  fragmentShaderID;
        int     numAttributes;
    protected:
        void    compileShader(const std::string filepath, GLuint id);

};

#endif