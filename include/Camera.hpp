#ifndef CAMERA_HPP
# define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera {
    public:
        Camera(void);
        //Camera(const glm::vec3 &pos, float fov, float aspect, float zNear, float zFar);        
        ~Camera(void);

        glm::mat4 getViewProjection() const;
        void    initCamera(const glm::vec3 &pos, float fov, float aspect, float zNear, float zFar);        
        

        //getters and setters
        glm::vec3&  getCameraPos();
        glm::vec3&  getCameraForward();
        glm::vec3&  getCameraUp();

        void        setCameraPos(const glm::vec3& pos);
        void        setCameraForward(const glm::vec3&);
        void        setCameraUp(const glm::vec3&);

    private:
        
        glm::mat4   perspective;
        glm::vec3   cameraPos;
        glm::vec3   forward;
        glm::vec3   up;
};

#endif