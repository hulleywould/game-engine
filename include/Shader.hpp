#ifndef SHADER_HPP
# define SHADER_HPP

#include "Camera.hpp"
#include "Transform.hpp"
#include "Material.hpp"
#include "GlslProgram.hpp"

class Shader: public GlslProgram {
    public:
        Shader(void);
        ~Shader(void);

        void    initializeShader();
        void    update(const Transform &transform, const Camera &camera, Material &material);
};

#endif