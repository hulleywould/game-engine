#ifndef SPRITE_HPP
# define SPRITE_HPP

class Sprite {

    public:
        Sprite(void);
        ~Sprite(void);

        void    init(int x, int y, int width, int height);

        void    draw();

    private:
        int     x;
        int     y;
        int width;
        int height;
        
};

#endif