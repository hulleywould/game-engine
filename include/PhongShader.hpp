#ifndef PHONG_SHADER_HPP
# define PHONG_SHADER_HPP

#include "Camera.hpp"
#include "Transform.hpp"
#include "Material.hpp"
#include "GlslProgram.hpp"
#include "DirectionalLight.hpp"
#include "BaseLight.hpp"
#include "PointLight.hpp"
#include <iostream>
#include <string>

class PhongShader: public GlslProgram {
    public:
        PhongShader(void);
        ~PhongShader(void);

        void    initializeShader();
        void    update(const Transform &transform, Camera &camera, Material &material);
        
        void    setAmbientLight(const glm::vec3 &ambience);
        void    setDirectionalLight(const DirectionalLight &dir);
        void    setPointLight(PointLight *pointLight);

        glm::vec3&          getAmbientLight();
        DirectionalLight&   getDirectionalLight();
        PointLight&         getPointLight();
        int                 MAX_POINT_LIGHT = 4;

    private:
        glm::vec3           ambientLight;
        DirectionalLight    directionalLight;
        BaseLight           baseLight;
        
        PointLight          *pointLights;
};

#endif