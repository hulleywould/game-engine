#include "Camera.hpp"

Camera::Camera(void) :
    perspective(glm::mat4()),
    cameraPos(glm::vec3()),
    forward(glm::vec3()),
    up(glm::vec3())
{
}

Camera::~Camera(void)
{

}

void    Camera::initCamera(const glm::vec3 &pos, float fov, float aspect, float zNear, float zFar)
{
    perspective = glm::perspective(fov, aspect, zNear, zFar);
    cameraPos = pos;
    forward = glm::vec3(0.0, 0.0, 1.0);
    up = glm::vec3(0.0, 1.0, 0.0);
}

void    Camera::camUpdate(const glm::vec3 &pos)
{
    cameraPos = pos;
}

glm::mat4 Camera::getViewProjection() const
{
    return perspective * glm::lookAt(cameraPos, cameraPos + forward, up);
}

//getters and setters
glm::vec3&   Camera::getCameraPos()
{
    return cameraPos;
}
glm::vec3&   Camera::getCameraForward()
{
    return forward;
}
glm::vec3&   Camera::getCameraUp()
{
    return up;
}

void        Camera::setCameraPos(const glm::vec3& pos)
{
    cameraPos = pos;
}
void        Camera::setCameraForward(const glm::vec3& camForward)
{
    forward = camForward;
}
void        Camera::setCameraUp(const glm::vec3& camUp)
{
    up = camUp;
}