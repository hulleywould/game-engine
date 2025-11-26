#include "Menu.hpp"

#include <iostream>

Menu::Menu()
    : screenWidth(0)
    , screenHeight(0)
    , menuSelection(0)
    , wKeyPressed(false)
    , sKeyPressed(false)
    , enterKeyPressed(false)
    , spaceKeyPressed(false)
{
}

bool Menu::init(int width, int height)
{
    screenWidth = width;
    screenHeight = height;

    std::cout << "Initializing menu shader..." << std::endl;
    menuShader.compileShaders("src/shaders/menu2D.vert", "src/shaders/menu2D.frag");
    menuShader.addAttribute("position");
    menuShader.linkShaders();
    menuShader.addUniform("screenSize");
    menuShader.addUniform("color");
    std::cout << "Menu shader initialized successfully." << std::endl;

    // Initialize text renderer with system DejaVuSans font (common on Ubuntu)
    std::string fontPath = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
    if (!textRenderer.init(screenWidth, screenHeight, fontPath, 24)) {
        std::cout << "WARNING: TextRenderer failed to initialize. Menu text will not be shown." << std::endl;
    }

    return true;
}

void Menu::render()
{
    // Unbind any previous shaders/VAOs
    glUseProgram(0);
    glBindVertexArray(0);

    // Disable depth testing for 2D menu rendering
    glDisable(GL_DEPTH_TEST);
    // Disable face culling for 2D
    glDisable(GL_CULL_FACE);
    // Enable blending for proper rendering
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    menuShader.use();

    // Set screen size uniform
    menuShader.setUniform("screenSize", glm::vec2((float)screenWidth, (float)screenHeight));

    // Button dimensions
    float btnWidth = 250.0f;
    float btnHeight = 80.0f;
    float btnX = (screenWidth - btnWidth) / 2.0f;
    float startBtnY = screenHeight / 2.0f - 60.0f;
    float exitBtnY = screenHeight / 2.0f + 60.0f;

    // Background quad
    float bgVertices[] = {
        0.0f, 0.0f,
        (float)screenWidth, 0.0f,
        (float)screenWidth, (float)screenHeight,
        0.0f, (float)screenHeight
    };

    GLuint bgVAO, bgVBO;
    glGenVertexArrays(1, &bgVAO);
    glGenBuffers(1, &bgVBO);
    glBindVertexArray(bgVAO);
    glBindBuffer(GL_ARRAY_BUFFER, bgVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bgVertices), bgVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    menuShader.setUniform("color", glm::vec3(0.2f, 0.2f, 0.2f));
    unsigned int bgIndices[] = {0, 1, 2, 0, 2, 3};
    GLuint bgEBO;
    glGenBuffers(1, &bgEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bgEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bgIndices), bgIndices, GL_STATIC_DRAW);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDeleteBuffers(1, &bgEBO);

    // Start Game button
    float startBtnVertices[] = {
        btnX, startBtnY,
        btnX + btnWidth, startBtnY,
        btnX + btnWidth, startBtnY + btnHeight,
        btnX, startBtnY + btnHeight
    };

    GLuint startBtnVAO, startBtnVBO;
    glGenVertexArrays(1, &startBtnVAO);
    glGenBuffers(1, &startBtnVBO);
    glBindVertexArray(startBtnVAO);
    glBindBuffer(GL_ARRAY_BUFFER, startBtnVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(startBtnVertices), startBtnVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    if (menuSelection == 0) {
        menuShader.setUniform("color", glm::vec3(0.0f, 1.0f, 0.0f));
    } else {
        menuShader.setUniform("color", glm::vec3(0.0f, 0.6f, 0.0f));
    }
    unsigned int startBtnIndices[] = {0, 1, 2, 0, 2, 3};
    GLuint startBtnEBO;
    glGenBuffers(1, &startBtnEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, startBtnEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(startBtnIndices), startBtnIndices, GL_STATIC_DRAW);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDeleteBuffers(1, &startBtnEBO);

    // Exit button
    float exitBtnVertices[] = {
        btnX, exitBtnY,
        btnX + btnWidth, exitBtnY,
        btnX + btnWidth, exitBtnY + btnHeight,
        btnX, exitBtnY + btnHeight
    };

    GLuint exitBtnVAO, exitBtnVBO;
    glGenVertexArrays(1, &exitBtnVAO);
    glGenBuffers(1, &exitBtnVBO);
    glBindVertexArray(exitBtnVAO);
    glBindBuffer(GL_ARRAY_BUFFER, exitBtnVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(exitBtnVertices), exitBtnVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    if (menuSelection == 1) {
        menuShader.setUniform("color", glm::vec3(1.0f, 0.0f, 0.0f));
    } else {
        menuShader.setUniform("color", glm::vec3(0.6f, 0.0f, 0.0f));
    }
    unsigned int exitBtnIndices[] = {0, 1, 2, 0, 2, 3};
    GLuint exitBtnEBO;
    glGenBuffers(1, &exitBtnEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, exitBtnEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(exitBtnIndices), exitBtnIndices, GL_STATIC_DRAW);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDeleteBuffers(1, &exitBtnEBO);

    // Cleanup button/background VAOs/VBOs
    glDeleteVertexArrays(1, &bgVAO);
    glDeleteBuffers(1, &bgVBO);
    glDeleteVertexArrays(1, &startBtnVAO);
    glDeleteBuffers(1, &startBtnVBO);
    glDeleteVertexArrays(1, &exitBtnVAO);
    glDeleteBuffers(1, &exitBtnVBO);

    menuShader.unuse();

    // Render centered labels
    float textScale = 1.0f;
    std::string startLabel = "START GAME";
    std::string exitLabel  = "EXIT";

    glm::vec2 startSize = textRenderer.getTextSize(startLabel, textScale);
    glm::vec2 exitSize  = textRenderer.getTextSize(exitLabel,  textScale);

    float startCenterMenuY = startBtnY + btnHeight / 2.0f;
    float exitCenterMenuY  = exitBtnY  + btnHeight / 2.0f;

    float startCenterTextY = screenHeight - startCenterMenuY;
    float exitCenterTextY  = screenHeight - exitCenterMenuY;

    float startTextX = btnX + (btnWidth - startSize.x) / 2.0f;
    float exitTextX  = btnX + (btnWidth - exitSize.x)  / 2.0f;

    float startTextY = startCenterTextY - startSize.y / 2.0f;
    float exitTextY  = exitCenterTextY  - exitSize.y  / 2.0f;

    textRenderer.renderText(startLabel, startTextX, startTextY, textScale, glm::vec3(1.0f));
    textRenderer.renderText(exitLabel,  exitTextX,  exitTextY,  textScale, glm::vec3(1.0f));

    // Restore state for 3D rendering
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void Menu::processInput(GLFWwindow* window, GameState& gameState)
{
    auto wKey = glfwGetKey(window, GLFW_KEY_W);
    auto sKey = glfwGetKey(window, GLFW_KEY_S);
    auto enterKey = glfwGetKey(window, GLFW_KEY_ENTER);
    auto spaceKey = glfwGetKey(window, GLFW_KEY_SPACE);

    if (wKey == GLFW_PRESS && !wKeyPressed) {
        wKeyPressed = true;
        menuSelection = 0;
    } else if (wKey == GLFW_RELEASE) {
        wKeyPressed = false;
    }

    if (sKey == GLFW_PRESS && !sKeyPressed) {
        sKeyPressed = true;
        menuSelection = 1;
    } else if (sKey == GLFW_RELEASE) {
        sKeyPressed = false;
    }

    if (enterKey == GLFW_PRESS && !enterKeyPressed) {
        enterKeyPressed = true;
        if (menuSelection == 0) gameState = GameState::PLAY;
        else if (menuSelection == 1) gameState = GameState::EXIT;
    } else if (enterKey == GLFW_RELEASE) {
        enterKeyPressed = false;
    }

    if (spaceKey == GLFW_PRESS && !spaceKeyPressed) {
        spaceKeyPressed = true;
        if (menuSelection == 0) gameState = GameState::PLAY;
        else if (menuSelection == 1) gameState = GameState::EXIT;
    } else if (spaceKey == GLFW_RELEASE) {
        spaceKeyPressed = false;
    }
}


