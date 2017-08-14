#ifndef SPOTLIGHT_HPP
# define SPOTLIGHT_HPP

#include "PointLight.hpp"
#include <glm/glm.hpp>

class SpotLight {
    public:
        SpotLight();
        SpotLight(PointLight pointL, glm::vec3 dir, float cut);
        ~SpotLight();

        //getters and setters
        void        setPointLight(const PointLight& pointLight);
        void        setDirection(const glm::vec3& dir);
        void        setCutOff(const float& cut);

        PointLight& getPointLight();
        glm::vec3&  getDirection();
        float       getCutoff();

    private:
        PointLight  pointLight;
        glm::vec3   direction;
        float       cutoff;
};

#endif