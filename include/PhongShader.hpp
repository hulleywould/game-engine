#ifndef PHONG_SHADER_HPP
# define PHONG_SHADER_HPP

#include "Camera.hpp"
#include "Transform.hpp"
#include "Material.hpp"
#include "GlslProgram.hpp"
#include "DirectionalLight.hpp"
#include "BaseLight.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"
#include <iostream>
#include <string>
#include <vector>

class PhongShader: public GlslProgram {
    public:
        PhongShader(void);
        ~PhongShader(void);

        void    initializeShader();
        void    update(const Transform &transform, Camera &camera, Material &material);
        
        void    setAmbientLight(const glm::vec3 &ambience);
        void    setDirectionalLight(const DirectionalLight &dir);
        void    setPointLight(std::vector<PointLight> pointLight);
        void    setSpotLight(std::vector<SpotLight> spotLight);

        glm::vec3&                          getAmbientLight();
        DirectionalLight&                   getDirectionalLight();
        std::vector<PointLight>&            getPointLight();
        std::vector<SpotLight>&             getSpotLight();
        
        int                                 MAX_POINT_LIGHT = 4;
        int                                 MAX_SPOT_LIGHT = 4;

    private:
        glm::vec3           ambientLight;
        DirectionalLight    directionalLight;
        BaseLight           baseLight;
        std::vector<PointLight>  pointLights;
        std::vector<SpotLight>   spotLights;
};

#endif