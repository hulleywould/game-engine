#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Vector {
    public:
        Vector(void);
        Vector(float x, float y);
        Vector(float x, float y, float z);
        Vector(float x, float y, float z, float w);
        ~Vector(void);

        Vector  rotate(float angle, Vector axis);    

        //getters and setters
        void    setX(const float& xpos);
        void    setY(const float& ypos);
        void    setZ(const float& zpos);
        void    setW(const float& wpos);

        float&  getX();
        float&  getY();
        float&  getZ();
        float&  getW();
        
    private:
        float   x;
        float   y;
        float   z;
        float   w;

};

#endif