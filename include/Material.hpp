#ifndef MATERIAL_HPP
# define MATERIAL_HPP

#include "Texture.hpp"
#include <glm/glm.hpp>

class Material {
    public:
        Material(void);
        Material(const Texture& texture, const glm::vec3& color);
        ~Material(void);

        Texture&    getTexture();
        glm::vec3&  getColor();    

    private:
        Texture     texture;
        glm::vec3   color;

};

#endif