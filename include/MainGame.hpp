#ifndef MAINGAME_HPP
# define MAINGAME_HPP

#include <cstdlib>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

enum class GameState {PLAY, EXIT};

class MainGame {
    public:
        MainGame(void);
        ~MainGame(void);

        void    run();
        
        int     initGL();
        int     createWindow(int width, int height);

    private:
        void        processInput();
        void        gameLoop();
        void        initSystems();
        GLFWwindow  *window;
        int         screenWidth;
        int         screenHeight;
        GameState   gameState;
        void        handleContext();
        void        drawGame();
};

#endif