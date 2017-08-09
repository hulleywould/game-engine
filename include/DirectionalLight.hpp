#ifndef DIRECTIONALLIGHT_HPP
# define DIRECTIONALLIGHT_HPP

#include <glm/glm.hpp>
#include "BaseLight.hpp"

class DirectionalLight {

    public:
        DirectionalLight();
        DirectionalLight(BaseLight b, glm::vec3 dir);
        ~DirectionalLight();

        //getters and setters
        void        setBase(const BaseLight &);
        void        setDirection(const glm::vec3 &);

        BaseLight&  getBase();
        glm::vec3&  getDirection();

    private:
        BaseLight   base;
        glm::vec3   direction;

};

#endif