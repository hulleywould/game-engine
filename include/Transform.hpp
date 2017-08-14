#ifndef TRANSFORM_HPP
# define TRANSFORM_HPP

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "Camera.hpp"

class Transform {
    public:
        Transform(void);
        Transform(const glm::vec3 &pos, 
                const glm::vec3 &rot,
                const glm::vec3 &scaling);
        ~Transform(void);
        glm::mat4   getTransformation() const;
        glm::mat4   getProjectedTransformation() const;
        Camera      camera;

        //getters and setters
        glm::vec3   &getPos();
        glm::vec3   &getRot();
        glm::vec3   &getScale();
        glm::vec3   &getTranslation();

        void        setPos(const glm::vec3 &pos);
        void        setRot(const glm::vec3 &rot);
        void        setScale(const glm::vec3 &scaling);
        void        setTranslation(float x, float y, float z);
        void        setProjection(float fov, float width, float height, float zNear, float zFar);
        
    private: 
        glm::vec3   position;
        glm::vec3   rotation;
        glm::vec3   scale;
        glm::vec3   translation;
        float       zNear;
        float       zFar;
        float       width;
        float       height;
        float       fov;

};

#endif