#ifndef MENU_HPP
#define MENU_HPP

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "GlslProgram.hpp"
#include "TextRenderer.hpp"
#include "GameState.hpp"

class Menu {
public:
    Menu();
    ~Menu() = default;

    bool init(int screenWidth, int screenHeight);

    void render();
    void processInput(GLFWwindow* window, GameState& gameState);

private:
    int         screenWidth;
    int         screenHeight;

    GlslProgram menuShader;
    TextRenderer textRenderer;

    int   menuSelection;      // 0 = Start Game, 1 = Exit
    bool  wKeyPressed;
    bool  sKeyPressed;
    bool  enterKeyPressed;
    bool  spaceKeyPressed;
};

#endif


