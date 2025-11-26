#ifndef MAINGAME_HPP
# define MAINGAME_HPP

#include <cstdlib>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Sprite.hpp"
#include "Texture.hpp"
#include "GlslProgram.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "PhongShader.hpp"
#include "TextRenderer.hpp"


enum class GameState {PLAY, EXIT, MENU};

class MainGame {
    public:
        MainGame(void);
        ~MainGame(void);

        void    run();

        void     initGL();
        void     createWindow(int width, int height);

        //getters and setters
        int         &getWidth();
        int         &getHeight();

        void        setWidth(const int &w);
        void        setHeight(const int &h);
        float       camY;
        float       camX;
        float       camZ;
        static double    xpos;
        static double    ypos;
        static bool      mouseButtonPressed;

    private:
        void        processInput();
        void        gameLoop();
        void        initSystems();
        void        renderMenu();
        void        processMenuInput();
        GLFWwindow  *window;
        int         screenWidth;
        int         screenHeight;
        GameState   gameState;
        void        handleContext();
        float       time;
        float       counter;
        Camera      camera;
        PhongShader         shader;
        PointLight          pLight1;
        PointLight          pLight2;
        SpotLight           sLight1;
        GlslProgram         menuShader;
        TextRenderer        textRenderer;
        int                 menuSelection; // 0 = Start Game, 1 = Exit
        bool                wKeyPressed;
        bool                sKeyPressed;
        bool                enterKeyPressed;
        bool                spaceKeyPressed;
        
};

#endif
