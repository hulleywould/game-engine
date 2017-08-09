#include "Attenuation.hpp"

Attenuation::Attenuation()
{

}

Attenuation::Attenuation(float con, float lin, float expo)
{
    constant = con;
    linear = lin;
    exponent = expo;
}

Attenuation::~Attenuation()
{

}

//getters and setters
void    Attenuation::setConstant(const float& con)
{
    constant = con;
}

void    Attenuation::setLinear(const float& lin)
{
    linear = lin;
}

void    Attenuation::setExponent(const float& expo)
{
    exponent = expo;
}

float&  Attenuation::getConstant()
{
    return constant;
}

float&  Attenuation::getLinear()
{
    return linear;
}

float&  Attenuation::getExponent()
{
    return exponent;
}