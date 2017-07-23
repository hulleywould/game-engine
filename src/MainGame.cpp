#include "MainGame.hpp"


MainGame::MainGame(void) :
    window(NULL),
    screenWidth(640),
    screenHeight(480),
    gameState(GameState::PLAY),
    time(0.0f),
    counter(0.0f),
    camera(),
    meshData()
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

    glClearColor(0.5f, 0.7f, 0.0f, 1.0f);
    camera.initCamera(glm::vec3(0.0, 0.0, -2.0), 70.0f, (float)getWidth() / (float)getHeight(), 0.01f, 1000.0f);

    initShaders();
}

void    MainGame::initShaders()
{
    colorProgram.compileShaders("src/shaders/colorShading.vert", "src/shaders/colorShading.frag");
    colorProgram.addAttribute("position");
    colorProgram.addAttribute("texCoord");
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
    window = glfwCreateWindow(getWidth(), getHeight(), "GameEngine", NULL, NULL);
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
            else if(key == GLFW_KEY_UP && action == GLFW_PRESS) {
                
            }
        });
    } 
}

void        MainGame::gameLoop() 
{
    while (gameState != GameState::EXIT)
    {
        //time += 0.1f;
        //std::cout << "counter is " << counter << std::endl;
        drawGame();
        processInput();
        counter += 0.001f;
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

    float sinCounter = sinf(counter);
    float cosCounter = cosf(counter);
    
    Transform   transform;
    transform.getPos().x = sinCounter;
    transform.getPos().z = cosCounter;
    transform.getRot().x = counter * 50;
    transform.getRot().y = counter * 50;
    transform.getRot().z = counter * 50;

    colorProgram.use();

    GLuint transformUniform = colorProgram.getUniformLocation("transform");
    Texture texture("assets/cat.jpg");
    
    colorProgram.update(transform, camera);
    
    meshData.handleMesh();
    
    colorProgram.unuse();

    glfwSwapBuffers(window);

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

