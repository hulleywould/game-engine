#ifndef CAMERA_HPP
# define CAMERA_HPP

#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

class Camera {
    public:
        Camera(void);
        //Camera(const glm::vec3 &pos, float fov, float aspect, float zNear, float zFar);        
        ~Camera(void);

        glm::mat4 getViewProjection() const;
        glm::mat4 getWorldToView() const;
        glm::mat4 perspectiveMatrix() const;
        void        mouseUpdate(const glm::vec2& newMousePosition);
        void        initCamera(const glm::vec3 &pos, float fov, float aspect, float zNear, float zFar);        

        //getters and setters
        glm::vec3&  getCameraPos();
        glm::vec3&  getCameraForward();
        glm::vec3&  getCameraUp();
        glm::vec3&  getViewDirection();
        glm::vec2&  getOldMousePos();

        void        setCameraPos(const glm::vec3& pos);
        void        setCameraForward(const glm::vec3&);
        void        setCameraUp(const glm::vec3& up);
        void        setViewDirection(const glm::vec3& dir);
        void        setOldMousePos(const glm::vec2& pos);
        void        camUpdate(const glm::vec3 &pos);
        

    private:
        
        glm::mat4   perspective;
        glm::vec3   cameraPos;
        glm::vec3   forward;
        glm::vec3   up;
        glm::vec3   viewDirection;
        glm::vec2   oldMousePosition;
};

#endif