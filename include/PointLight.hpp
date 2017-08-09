#ifndef POINTLIGHT_HPP
# define POINTLIGHT_HPP

#include <glm/glm.hpp>
#include "BaseLight.hpp"
#include "Attenuation.hpp"

class PointLight {

    public:
        PointLight();
        PointLight(BaseLight b, Attenuation at, glm::vec3 pos);
        ~PointLight();

        //getters and setters
        void        setBase(const BaseLight &);
        void        setAttenuation(const Attenuation &);
        void        setPosition(const glm::vec3 &);

        BaseLight&  getBase();
        Attenuation& getAttenuation();
        glm::vec3&  getPosition();

    private:
        BaseLight   base;
        Attenuation atten;
        glm::vec3   position;

};

#endif