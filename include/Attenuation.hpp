#ifndef ATTENUATION_HPP
# define ATTENUATION_HPP

class Attenuation {
    public:
        Attenuation();
        Attenuation(float constant, float linear, float exponent);
        ~Attenuation();

        //getters and setters
        void    setConstant(const float& constant);
        void    setLinear(const float& linear);
        void    setExponent(const float& expo);

        float&  getConstant();
        float&  getLinear();
        float&  getExponent();

    private:
        float   constant;
        float   linear;
        float   exponent; 
};

#endif