#ifndef PHONG_SHADER_HPP
# define PHONG_SHADER_HPP

#include "Camera.hpp"
#include "Transform.hpp"
#include "Material.hpp"
#include "GlslProgram.hpp"
#include "DirectionalLight.hpp"
#include "BaseLight.hpp"

class PhongShader: public GlslProgram {
    public:
        PhongShader(void);
        ~PhongShader(void);

        void    initializeShader();
        void    update(const Transform &transform, const Camera &camera, Material &material);
        
        void    setAmbientLight(const glm::vec3 &ambience);
        void    setDirectionalLight(const DirectionalLight &dir);

        glm::vec3&          getAmbientLight();
        DirectionalLight&   getDirectionalLight();

    private:
        glm::vec3           ambientLight;
        DirectionalLight    directionalLight;
        BaseLight           baseLight; 
};

#endif