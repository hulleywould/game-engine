#include "MainGame.hpp"


MainGame::MainGame(void) :
    window(NULL),
    screenWidth(640),
    screenHeight(480),
    gameState(GameState::PLAY),
    time(0.0f),
    counter(0.0f),
    camera()
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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_DOUBLEBUFFER, 1);

    createWindow(screenWidth, screenHeight);
    glfwMakeContextCurrent(window);
    handleContext();

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    glClearColor(0.0f, 0.0f, 0.5f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    shader.initializeShader();
}

/* initialize GLFW*/
int     MainGame::initGL()
{
    if (!glfwInit())
        return -1;  
    return 0;
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
        auto EscKey = glfwGetKey(window, GLFW_KEY_ESCAPE);
        auto camUp = glfwGetKey(window, GLFW_KEY_W);
        auto camDown = glfwGetKey(window, GLFW_KEY_S);
        auto camLeft = glfwGetKey(window, GLFW_KEY_A);
        auto camRight = glfwGetKey(window, GLFW_KEY_D);
        auto zoomIn = glfwGetKey(window, GLFW_KEY_Q);
        auto zoomOut = glfwGetKey(window, GLFW_KEY_E);
        if (EscKey == GLFW_PRESS)
        {
            glfwTerminate();
                exit(0);
        }
        else if (camUp == GLFW_PRESS)
        {
            camY += 0.01f;
            camera.camUpdate(glm::vec3(camX, camY, camZ));
        }
        else if (camDown == GLFW_PRESS)
        {
            camY -= 0.01f;
            camera.camUpdate(glm::vec3(camX, camY, camZ));
        }
        else if (camLeft == GLFW_PRESS)
        {
            camX -= 0.01f;
            camera.camUpdate(glm::vec3(camX, camY, camZ));
        }
        else if (camRight == GLFW_PRESS)
        {
            camX += 0.01f;
            camera.camUpdate(glm::vec3(camX, camY, camZ));
        }
        else if (zoomIn == GLFW_PRESS)
        {
            camZ += 0.01f;
            camera.camUpdate(glm::vec3(camX, camY, camZ));
        }
        else if (zoomOut == GLFW_PRESS)
        {
            camZ -= 0.01f;
            camera.camUpdate(glm::vec3(camX, camY, camZ));
        }

    } 
}

void        MainGame::gameLoop() 
{
    camera.initCamera(glm::vec3(0.0, 0.0, -3.0), 70.0f, (float)getWidth() / (float)getHeight(), 0.01f, 1000.0f);
    Transform   transform;
    Texture     texture("assets/wood.jpg");
    Material    material(texture, glm::vec3(0.0, 0.0, 0.0));
    Sprite sprite2("assets/monkey3.obj");
    camY = 0.0f;
    camX = 0.0f;
    camZ = -3.0f;
    while (gameState != GameState::EXIT)
    {
        glClearDepth(1.0);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        float sinCounter = sinf(counter);
        float cosCounter = cosf(counter);
        
        transform.getRot().y = counter / 10;

        material.getColor() = glm::vec3(0.6, 0.3, 0.0);
        shader.use();

        shader.update(transform, camera, material);
        
        sprite2.draw();
        
        shader.unuse();

        glfwSwapBuffers(window);

        processInput();
        counter += 0.05f;
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

