#include "MainGame.hpp"


MainGame::MainGame(void) :
    window(NULL),
    screenWidth(640),
    screenHeight(480),
    gameState(GameState::PLAY),
    time(0.0f),
    counter(0.0f),
    camera(),
    pLight1(BaseLight(glm::vec3(0.0f, 0.0f, 1.0f), 0.8f), Attenuation(0.0f, 0.0f, 1.0f), glm::vec3(-5.0f, 0.0f, 1.0f), 30.0f),
    pLight2(BaseLight(glm::vec3(0.0f, 1.0f, 1.0f), 0.8f), Attenuation(0.0f, 0.0f, 1.0f), glm::vec3(5.0f, 0.0f, 2.0f), 30.0f),
    sLight1(PointLight(BaseLight(glm::vec3(0.0f, 1.0f, 0.0f), 100.0f), Attenuation(0.0f, 0.0f, 0.1f), glm::vec3(-5.0f, 0.0f, 1.0f), 30.0f),
    glm::vec3(1.0f, 1.0f, 1.0f), 0.7f)
    
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

    #ifdef __APPLE__
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    glfwWindowHint(GLFW_DOUBLEBUFFER, 1);

    createWindow(screenWidth, screenHeight);
    glfwMakeContextCurrent(window);
    handleContext();

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // get version info
    std::cout << "Renderer:" << glGetString(GL_RENDERER) << '\n';
    std::cout << "OpenGL version supported " << glGetString(GL_VERSION) << "\n\n";

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_CLAMP);
    glEnable(GL_TEXTURE_2D);

    shader.initializeShader();
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
    window = glfwCreateWindow(getWidth(), getHeight(), "GameEngine", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        std::cout << "ERROR: could not open window with GLFW3\n";
        exit(0);
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
            camY -= 1.0f;
            camera.camUpdate(glm::vec3(camX, camY, camZ));
        }
        else if (camDown == GLFW_PRESS)
        {
            camY += 1.0f;
            camera.camUpdate(glm::vec3(camX, camY, camZ));
        }
        else if (camLeft == GLFW_PRESS)
        {
            camX -= 1.0f;
            camera.camUpdate(glm::vec3(camX, camY, camZ));
        }
        else if (camRight == GLFW_PRESS)
        {
            camX += 1.0f;
            camera.camUpdate(glm::vec3(camX, camY, camZ));
        }
        else if (zoomIn == GLFW_PRESS)
        {
            camZ += 1.0f;
            camera.camUpdate(glm::vec3(camX, camY, camZ));
        }
        else if (zoomOut == GLFW_PRESS)
        {
            camZ -= 1.00f;
            camera.camUpdate(glm::vec3(camX, camY, camZ));
        }

    }
}

void        MainGame::gameLoop()
{
    Transform           transform;
    Texture     texture("assets/wood.jpg");
    Material    material(texture, glm::vec3(0.0, 0.0, 0.0), 1, 8);
    Sprite sprite2("assets/monkey3.obj");
    
    //directional light
    DirectionalLight light(BaseLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.5f), glm::vec3(1.0f, 1.0f, 1.0f));
    shader.setDirectionalLight(light);

    //point light thing
    std::vector<PointLight> pLightArray;
    pLightArray.push_back(pLight1);
    pLightArray.push_back(pLight2);
    //segfaults if this line is removed. WTF??
    shader.setPointLight(pLightArray);

    std::vector<SpotLight> sLightArray;
    sLightArray.push_back(sLight1);
    //sLightArray.push_back(sLight2);
    shader.setSpotLight(sLightArray);
    
    camY = 0.0f;
    camX = 0.0f;
    camZ = -30.0f;
    camera.initCamera(glm::vec3(camX, camY, camZ), 70.0f, (float)getWidth() / (float)getHeight(), 0.01f, 1000.0f); 
    shader.setAmbientLight(glm::vec3(0.1f,0.1f,0.1f));
    transform.getRot().y = 3.15f;
    transform.getScale().x = 10.0f;
    transform.getScale().y = 10.0f;
    transform.getScale().z = 10.0f;

    while (gameState != GameState::EXIT)
    {
        glClearDepth(1.0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float sinCounter = sinf(counter);
        float cosCounter = cosf(counter);
        
        transform.getPos().y = sinCounter / 10;
        //transform.getRot().y = counter / 10;
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
