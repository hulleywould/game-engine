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
        //GLuint  getUniformLocation(const std::string &uniformName);
        void    addUniform(const std::string &uniformName);
        void    setUniformi(const std::string &uniformName, int value);
        void    setUniformf(const std::string &uniformName, float value);
        void    setUniform(const std::string &uniformName, glm::vec3 value);
        void    setUniform(const std::string &uniformName, glm::mat4 value);
        
        std::map<std::string, int> uniformMap;

    private:
        enum {
            TRANSFORM_U,
            NUM_UNIFORMS
        };
        GLuint  uniforms[NUM_UNIFORMS];
        GLuint  programID;
        GLuint  vertexShaderID;
        GLuint  fragmentShaderID;
        int     numAttributes;
    protected:
        void    compileShader(const std::string filepath, GLuint id);

};

#endif