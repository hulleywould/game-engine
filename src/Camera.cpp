#include "Camera.hpp"

Camera::Camera(void) :
    perspective(glm::mat4()),
    cameraPos(glm::vec3()),
    forward(glm::vec3()),
    up(glm::vec3()),
    viewDirection(glm::vec3(0.0f, 0.0f, -1.0f))
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

void Camera::mouseUpdate(const glm::vec2& newMousePosition)
{
    //delta: how much mouse has moved
    glm::vec2 mouseDelta = newMousePosition - oldMousePosition;
    if (glm::length(mouseDelta) > 50.0f)
    {
        oldMousePosition = newMousePosition;
        return;
    }
    //horizontal axis
    float rotationSpeed = 500.0f;
    viewDirection = glm::mat3(glm::rotate(-mouseDelta.x / rotationSpeed, up)) * viewDirection;
    //vertical axis
    glm::vec3 toRotateAround = glm::cross(viewDirection, up);
    viewDirection = glm::mat3(glm::rotate(-mouseDelta.y / rotationSpeed, toRotateAround)) * viewDirection;
    oldMousePosition = newMousePosition;
    std::cout << "new view posX: " << viewDirection.x << std::endl;
    std::cout << "mouse posX: " << oldMousePosition.x << std::endl;    
    std::cout << "new cam posY: " << cameraPos.x << std::endl;
    
}

glm::mat4 Camera::getViewProjection() const
{
    return perspective * glm::lookAt(cameraPos, cameraPos + forward, up);
}

glm::mat4 Camera::perspectiveMatrix() const
{
    return perspective;
}

glm::mat4 Camera::getWorldToView() const
{
    return glm::lookAt(cameraPos, cameraPos + viewDirection, up);
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

void        Camera::setOldMousePos(const glm::vec2& pos)
{
    oldMousePosition = pos;
}

glm::vec3&  Camera::getViewDirection()
{
    return viewDirection;
}

glm::vec2&  Camera::getOldMousePos()
{
    return oldMousePosition;
}


void        Camera::setViewDirection(const glm::vec3& dir)
{
    viewDirection = glm::normalize(dir);
}