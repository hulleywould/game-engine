#include "MainGame.hpp"


MainGame::MainGame(void) :
    window(NULL),
    screenWidth(640),
    screenHeight(480),
    gameState(GameState::PLAY),
    time(0.0f)
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
    glfwWindowHint(GLFW_DOUBLEBUFFER, 1);

    createWindow(screenWidth, screenHeight);
    glfwMakeContextCurrent(window);
    handleContext();

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    initShaders();
}

void    MainGame::initShaders()
{
    colorProgram.compileShaders("src/shaders/colorShading.vert", "src/shaders/colorShading.frag");
    colorProgram.addAttribute("vertexPosition");
    colorProgram.addAttribute("vertexColor");
    colorProgram.linkShaders();
}

/* initialize GLFW*/
int     MainGame::initGL()
{
    if (!glfwInit())
        return -1;  
}

int     MainGame::createWindow(int width, int height)
{
    window = glfwCreateWindow(width, height, "GameEngine", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    
    return (0);
}

void        MainGame::processInput()
{
    if (glfwWindowShouldClose(window)) {
        glfwTerminate();
        exit(0);
    }
    else {
        glfwPollEvents();
        /*turned key_callback into a lambda function
        **the processInput function is now in one place
        **minimizing the extra function call.
        */
        glfwSetKeyCallback(window, [](GLFWwindow *win, int key, int scancodes, int action, int modes) {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            {
                glfwTerminate();
                exit(0);
            }
        });
    } 
}

void        MainGame::gameLoop() 
{
    while (gameState != GameState::EXIT)
    {
        time += 0.1f;
        std::cout << "time is " << time << std::endl;
        drawGame();
        processInput();
    }
}

void MainGame::handleContext()
{
    glewExperimental = GL_TRUE;
    GLenum error = glewInit();
    if (GLEW_OK != error)
        std::cout << glewGetErrorString(error) << std::endl;
}

void MainGame::drawGame()
{
    glClearDepth(1.0);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    colorProgram.use();

    GLuint  timeLocation = colorProgram.getUniformLocation("time");
    glUniform1f(timeLocation, time);

    Vertex vertices[3];

    vertices[0].position = glm::vec3(-0.5, -0.5, 0);
    vertices[1].position = glm::vec3(0, 0.5, 0);
    vertices[3].position = glm::vec3(0.5, -0.5, 0);

    sprite.init2(vertices, sizeof(vertices) / sizeof(vertices[0]));

    sprite.draw();

    colorProgram.unuse();

    glfwSwapBuffers(window);

    

}

