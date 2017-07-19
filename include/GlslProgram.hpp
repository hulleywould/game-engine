#ifndef GLSLPROGRAM_HPP
# define GLSLPROGRAM_HPP

#include <string>
#include <iostream>
#include <GL/glew.h>
#include <fstream>
#include <vector>

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
        GLuint  getUniformLocation(const std::string &uniformName);

    private:
        GLuint  programID;
        GLuint  vertexShaderID;
        GLuint  fragmentShaderID;
        int     numAttributes;
        void    compileShader(const std::string filepath, GLuint id);

};

#endif