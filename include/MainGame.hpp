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
#include "menu.hpp"

enum class GameState {PLAY, EXIT};

class MainGame {
    public:
        MainGame(void);
        ~MainGame(void);

        void    run();

        void     initGL();
        void     createWindow(int width, int height);
        static void     cursor_enter(GLFWwindow *window, int entered);

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
        PhongShader         shader;
        PointLight          pLight1;
        PointLight          pLight2;
        SpotLight           sLight1;

};

#endif
