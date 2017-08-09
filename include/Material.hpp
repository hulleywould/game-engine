#ifndef MATERIAL_HPP
# define MATERIAL_HPP

#include "Texture.hpp"
#include <glm/glm.hpp>

class Material {
    public:
        Material(void);
        Material(const Texture& texture, const glm::vec3& color);
        Material(const Texture& texture, 
                const glm::vec3& color,
                const float& specularIntensity,
                const float& specularPower);
        ~Material(void);


        //getters
        Texture&    getTexture();
        glm::vec3&  getColor();
        float&      getSpecularIntensity();
        float&      getSpecularPower();           

    private:
        Texture     texture;
        glm::vec3   color;
        float       specularIntensity;
        float       specularPower;

};

#endif