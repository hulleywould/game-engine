#ifndef MAINGAME_HPP
# define MAINGAME_HPP

#include <cstdlib>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Sprite.hpp"
#include "Texture.hpp"
#include "GlslProgram.hpp"
#include "Shader.hpp"
#include "Camera.hpp"


enum class GameState {PLAY, EXIT};

class MainGame {
    public:
        MainGame(void);
        ~MainGame(void);

        void    run();
        
        int     initGL();
        int     createWindow(int width, int height);

        //getters and setters
        int         &getWidth();
        int         &getHeight();

        void        setWidth(const int &w);
        void        setHeight(const int &h);
        float       camY;
        float       camX;
        float       camZ;

    private:
        void        processInput();
        void        gameLoop();
        void        initSystems();
        GLFWwindow  *window;
        int         screenWidth;
        int         screenHeight;
        GameState   gameState;
        void        handleContext();
        float       time;
        float       counter;
        Camera      camera;
        Shader      shader;
        
};

#endif