#ifndef BASELIGHT_HPP
# define BASELIGHT_HPP

#include <glm/glm.hpp>

class BaseLight {

    public:
        BaseLight();
        BaseLight(glm::vec3 color, float intensity);
        ~BaseLight();

        //getters and setters
        void        setColor(const glm::vec3 &col);
        void        setIntensity(const float &intense);

        glm::vec3&  getColor();
        float&      getIntensity();

    private:
        glm::vec3   color;
        float       intensity;

};

#endif