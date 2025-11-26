#include "MainGame.hpp"

double MainGame::xpos = 0;
double MainGame::ypos = 0;
bool MainGame::mouseButtonPressed = false;

MainGame::MainGame(void) :
    window(NULL),
    screenWidth(640),
    screenHeight(480),
    gameState(GameState::MENU),
    time(0.0f),
    counter(0.0f),
    camera(),
    pLight1(BaseLight(glm::vec3(0.4f, 0.2f, 1.0f), 0.8f), Attenuation(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 10.0f),
    pLight2(BaseLight(glm::vec3(0.0f, 0.5f, 1.0f), 0.8f), Attenuation(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 10.0f),
    sLight1(PointLight(BaseLight(glm::vec3(0.0f, 1.0f, 0.0f), 0.8f), Attenuation(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 10.0f),
    glm::vec3(7.0f, 2.0f, 1.0f), 0.7f),
    menuSelection(0),
    wKeyPressed(false),
    sKeyPressed(false),
    enterKeyPressed(false),
    spaceKeyPressed(false)
    
{
    
}

MainGame::~MainGame(void)
{

}

void    MainGame::run()
{
    initSystems();

    gameLoop();
}

void    MainGame::initSystems()
{
    initGL();
    /* GLFW_DOUBLEBUFFER allows us to have two buffers to work
    ** with. Buffer A will be written to while Buffer B clears,
    ** then Buffer B is written to while Buffer A clears.
    ** This reduces flicker
    */
    
    // Try OpenGL 3.3 first (more compatible with WSLg), fallback to 4.1 if needed
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    #ifdef __APPLE__
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #else
      // Linux/WSL: Use core profile for modern OpenGL
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      // Don't require forward compatibility on Linux (can cause issues with WSLg)
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);
    #endif

    glfwWindowHint(GLFW_DOUBLEBUFFER, 1);
    // Additional hints for better compatibility
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

    createWindow(screenWidth, screenHeight);
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    handleContext();

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // get version info
    std::cout << "Renderer:" << glGetString(GL_RENDERER) << '\n';
    std::cout << "OpenGL version supported " << glGetString(GL_VERSION) << "\n\n";

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_CLAMP);
    // glEnable(GL_TEXTURE_2D) removed - deprecated in OpenGL 3.1+, not needed in OpenGL 4.1
    // Textures are now managed through shaders and samplers

    shader.initializeShader();
    
    // Initialize menu shader
    std::cout << "Initializing menu shader..." << std::endl;
    menuShader.compileShaders("src/shaders/menu2D.vert", "src/shaders/menu2D.frag");
    menuShader.addAttribute("position");
    menuShader.linkShaders();
    menuShader.addUniform("screenSize");
    menuShader.addUniform("color");
    std::cout << "Menu shader initialized successfully." << std::endl;

    // Initialize text renderer with system DejaVuSans font (common on Ubuntu)
    // You can change this path to any .ttf you prefer.
    std::string fontPath = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
    if (!textRenderer.init(screenWidth, screenHeight, fontPath, 24)) {
        std::cout << "WARNING: TextRenderer failed to initialize. Menu text will not be shown." << std::endl;
    }
}

/* initialize GLFW*/
void   MainGame::initGL()
{
    if (!glfwInit()) {
      std::cout << "ERROR: could not start GLFW3\n";
      exit(0);
    }
}

void   MainGame::createWindow(int width, int height)
{
    // Try creating window with current hints
    window = glfwCreateWindow(getWidth(), getHeight(), "GameEngine", NULL, NULL);
    if (!window)
    {
        const char* description;
        int code = glfwGetError(&description);
        std::cout << "WARNING: Failed to create window with core profile. Error: " << description << "\n";
        
        // Try fallback: compatibility profile
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);
        
        window = glfwCreateWindow(getWidth(), getHeight(), "GameEngine", NULL, NULL);
        if (!window)
        {
            code = glfwGetError(&description);
            glfwTerminate();
            std::cout << "ERROR: could not open window with GLFW3\n";
            std::cout << "GLFW Error Code: " << code << "\n";
            if (description) {
                std::cout << "GLFW Error Description: " << description << "\n";
            }
            exit(0);
        }
        else
        {
            std::cout << "Successfully created window with compatibility profile\n";
        }
    }
}

void    MainGame::processInput()
{
    if (glfwWindowShouldClose(window)) {
        glfwTerminate();
        exit(0);
    }
    else {
        glfwPollEvents();
        
        if (gameState == GameState::MENU)
        {
            processMenuInput();
        }
        else if (gameState == GameState::PLAY)
        {
            auto EscKey = glfwGetKey(window, GLFW_KEY_ESCAPE);
            auto camUp = glfwGetKey(window, GLFW_KEY_W);
            auto camDown = glfwGetKey(window, GLFW_KEY_S);
            auto camLeft = glfwGetKey(window, GLFW_KEY_A);
            auto camRight = glfwGetKey(window, GLFW_KEY_D);
            auto zoomIn = glfwGetKey(window, GLFW_KEY_Q);
            auto zoomOut = glfwGetKey(window, GLFW_KEY_E);
            auto mouseLeft = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT); 
            if (EscKey == GLFW_PRESS)
            {
                gameState = GameState::MENU;
            }
            else if (camUp == GLFW_PRESS)
            {
                camY -= 0.005f;
                camera.camUpdate(glm::vec3(camX, camY, camZ));
            }
            else if (camDown == GLFW_PRESS)
            {
                camY += 0.005f;
                camera.camUpdate(glm::vec3(camX, camY, camZ));
            }
            else if (camLeft == GLFW_PRESS)
            {
                camX -= 0.005f;
                camera.camUpdate(glm::vec3(camX, camY, camZ));
            }
            else if (camRight == GLFW_PRESS)
            {
                camX += 0.005f;
                camera.camUpdate(glm::vec3(camX, camY, camZ));
            }
            else if (zoomIn == GLFW_PRESS)
            {
                camZ += 0.005f;
                camera.camUpdate(glm::vec3(camX, camY, camZ));
            }
            else if (zoomOut == GLFW_PRESS)
            {
                camZ -= 0.005f;
                camera.camUpdate(glm::vec3(camX, camY, camZ));
            }
            else if (mouseLeft == GLFW_PRESS)
            {
                glfwGetCursorPos(window, &xpos, &ypos);
                camera.mouseUpdate(glm::vec2(xpos, ypos));
            }
        }
    }
}

void        MainGame::gameLoop()
{
    //segFaults if transform is made global. WTF??
    Transform           transform;
    Transform          transform2;
    transform.setProjection(70.0f, (float)getWidth(), (float)getHeight(), 0.1f, 1000.0f);
    transform2.setProjection(70.0f, (float)getWidth(), (float)getHeight(), 0.1f, 1000.0f);

    Texture     texture2("assets/wood.jpg");
    Texture     texture("assets/difuso_flip_oscuro.jpg");
    Material    material(texture, glm::vec3(0.0, 0.0, 0.0), 1, 8);
    Material    material2(texture2, glm::vec3(0.0, 0.0, 0.0), 1, 8);
    // Allocate on heap to avoid stack issues with large models
    Sprite* sprite1 = new Sprite("assets/monkey3.obj");
    Sprite* sprite2 = new Sprite("assets/monkey3.obj");
    
    //directional light
    DirectionalLight light(BaseLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.5f), glm::vec3(1.0f, 1.0f, 1.0f));
    shader.setDirectionalLight(light);

    //point light thing
    std::vector<PointLight> pLightArray;
    pLightArray.push_back(pLight1);
    pLightArray.push_back(pLight2);
    shader.setPointLight(pLightArray);

    std::vector<SpotLight> sLightArray;
    sLightArray.push_back(sLight1);
    
    camY = 0.0f;
    camX = 0.0f;
    camZ = -6.0f;
    camera.initCamera(glm::vec3(camX, camY, camZ), 70.0f, (float)getWidth() / (float)getHeight(), 0.01f, 1000.0f); 
    shader.setAmbientLight(glm::vec3(0.1f,0.1f,0.1f));
    transform.getRot().y = 3.15f;
    transform2.getRot().y = 3.15f;    
    transform2.getPos().x = 2.0f;
    
    while (gameState != GameState::EXIT)
    {
        if (gameState == GameState::PLAY)
        {
            float cosCounter = cosf(counter);
            float sinCounter = sinf(counter);

            glClearDepth(1.0);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            transform.getPos().y = sinCounter / 10;
            
            shader.use();

            //moving spotlight
            sLightArray[0].setDirection(glm::vec3(sinCounter * 10, 2.0f, 1.0f));
            shader.setSpotLight(sLightArray);
        
            //mesh one
            texture.useTexture();
            material.getColor() = glm::vec3(0.6, 0.3, 0.0);
            shader.update(transform, camera, material);
            sprite1->draw();

            //mesh two
            texture2.useTexture();
            material2.getColor() = glm::vec3(1.0, 1.0, 1.0);
            shader.update(transform2, camera, material);
            sprite2->draw();
            
            shader.unuse();

            glfwSwapBuffers(window);

            processInput();
            counter += 0.05f;
        }
        else if (gameState == GameState::MENU)
        {
            // Clear with dark background for menu
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
            glClearDepth(1.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            renderMenu();
            
            glfwSwapBuffers(window);
            processInput();
        }
    }
}

void MainGame::handleContext()
{
    glewExperimental = GL_TRUE;
    GLenum error = glewInit();
    if (GLEW_OK != error)
        std::cout << glewGetErrorString(error) << std::endl;

}

//getters and setters
int&        MainGame::getWidth()
{
    return screenWidth;
}

int&        MainGame::getHeight()
{
    return screenHeight;
}

void        MainGame::setWidth(const int &w)
{
    screenWidth = w;
}

void        MainGame::setHeight(const int &h)
{
    screenHeight = h;
}

void        MainGame::renderMenu()
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
    
    // Button dimensions - make them larger and more visible
    float btnWidth = 250.0f;
    float btnHeight = 80.0f;
    float btnX = (screenWidth - btnWidth) / 2.0f;
    float startBtnY = screenHeight / 2.0f - 60.0f;
    float exitBtnY = screenHeight / 2.0f + 60.0f;
    
    // Draw background (dark gray)
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
    // Draw as two triangles
    unsigned int bgIndices[] = {0, 1, 2, 0, 2, 3};
    GLuint bgEBO;
    glGenBuffers(1, &bgEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bgEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bgIndices), bgIndices, GL_STATIC_DRAW);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDeleteBuffers(1, &bgEBO);
    
    // Draw "Start Game" button (green)
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
    
    // Draw "Start Game" button - highlight if selected
    if (menuSelection == 0) {
        menuShader.setUniform("color", glm::vec3(0.0f, 1.0f, 0.0f)); // Bright green when selected
    } else {
        menuShader.setUniform("color", glm::vec3(0.0f, 0.6f, 0.0f)); // Darker green when not selected
    }
    unsigned int startBtnIndices[] = {0, 1, 2, 0, 2, 3};
    GLuint startBtnEBO;
    glGenBuffers(1, &startBtnEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, startBtnEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(startBtnIndices), startBtnIndices, GL_STATIC_DRAW);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDeleteBuffers(1, &startBtnEBO);
    
    // Draw "Exit" button (red)
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
    
    // Draw "Exit" button - highlight if selected
    if (menuSelection == 1) {
        menuShader.setUniform("color", glm::vec3(1.0f, 0.0f, 0.0f)); // Bright red when selected
    } else {
        menuShader.setUniform("color", glm::vec3(0.6f, 0.0f, 0.0f)); // Darker red when not selected
    }
    unsigned int exitBtnIndices[] = {0, 1, 2, 0, 2, 3};
    GLuint exitBtnEBO;
    glGenBuffers(1, &exitBtnEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, exitBtnEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(exitBtnIndices), exitBtnIndices, GL_STATIC_DRAW);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDeleteBuffers(1, &exitBtnEBO);
    
    // Cleanup
    glDeleteVertexArrays(1, &bgVAO);
    glDeleteBuffers(1, &bgVBO);
    glDeleteVertexArrays(1, &startBtnVAO);
    glDeleteBuffers(1, &startBtnVBO);
    glDeleteVertexArrays(1, &exitBtnVAO);
    glDeleteBuffers(1, &exitBtnVBO);
    
    menuShader.unuse();

    // Render text labels centered inside the buttons
    float textScale = 1.0f;
    std::string startLabel = "START GAME";
    std::string exitLabel  = "EXIT";

    glm::vec2 startSize = textRenderer.getTextSize(startLabel, textScale);
    glm::vec2 exitSize  = textRenderer.getTextSize(exitLabel,  textScale);

    // 1) Button centers in menu-space (Y=0 at top because of menu2D.vert)
    float startCenterMenuY = startBtnY + btnHeight / 2.0f;
    float exitCenterMenuY  = exitBtnY  + btnHeight / 2.0f;

    // 2) Convert to text-space (Y=0 at bottom, used by TextRenderer)
    float startCenterTextY = screenHeight - startCenterMenuY;
    float exitCenterTextY  = screenHeight - exitCenterMenuY;

    // 3) Center horizontally
    float startTextX = btnX + (btnWidth - startSize.x) / 2.0f;
    float exitTextX  = btnX + (btnWidth - exitSize.x)  / 2.0f;

    // 4) Center vertically around the button center
    float startTextY = startCenterTextY - startSize.y / 2.0f;
    float exitTextY  = exitCenterTextY  - exitSize.y  / 2.0f;

    textRenderer.renderText(startLabel, startTextX, startTextY, textScale, glm::vec3(1.0f, 1.0f, 1.0f));
    textRenderer.renderText(exitLabel,  exitTextX,  exitTextY,  textScale, glm::vec3(1.0f, 1.0f, 1.0f));
    
    // Re-enable depth testing and face culling
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    // Restore clear color to white for game rendering
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void        MainGame::processMenuInput()
{
    auto wKey = glfwGetKey(window, GLFW_KEY_W);
    auto sKey = glfwGetKey(window, GLFW_KEY_S);
    auto enterKey = glfwGetKey(window, GLFW_KEY_ENTER);
    auto spaceKey = glfwGetKey(window, GLFW_KEY_SPACE);
    
    // Navigate menu with W (up) and S (down)
    if (wKey == GLFW_PRESS && !wKeyPressed)
    {
        wKeyPressed = true;
        menuSelection = 0; // Move to Start Game
    }
    else if (wKey == GLFW_RELEASE)
    {
        wKeyPressed = false;
    }
    
    if (sKey == GLFW_PRESS && !sKeyPressed)
    {
        sKeyPressed = true;
        menuSelection = 1; // Move to Exit
    }
    else if (sKey == GLFW_RELEASE)
    {
        sKeyPressed = false;
    }
    
    // Select with Enter or Space
    if (enterKey == GLFW_PRESS && !enterKeyPressed)
    {
        enterKeyPressed = true;
        if (menuSelection == 0)
        {
            gameState = GameState::PLAY;
        }
        else if (menuSelection == 1)
        {
            gameState = GameState::EXIT;
        }
    }
    else if (enterKey == GLFW_RELEASE)
    {
        enterKeyPressed = false;
    }
    
    if (spaceKey == GLFW_PRESS && !spaceKeyPressed)
    {
        spaceKeyPressed = true;
        if (menuSelection == 0)
        {
            gameState = GameState::PLAY;
        }
        else if (menuSelection == 1)
        {
            gameState = GameState::EXIT;
        }
    }
    else if (spaceKey == GLFW_RELEASE)
    {
        spaceKeyPressed = false;
    }
}
