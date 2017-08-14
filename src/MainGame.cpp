#include "MainGame.hpp"

double MainGame::xpos = 0;
double MainGame::ypos = 0;

MainGame::MainGame(void) :
    window(NULL),
    screenWidth(640),
    screenHeight(480),
    gameState(GameState::PLAY),
    time(0.0f),
    counter(0.0f),
    camera(),
    pLight1(BaseLight(glm::vec3(1.0f, 0.0f, 0.0f), 50.8f), Attenuation(0.0f, 0.0f, 1.0f), glm::vec3(-5.0f, 1.0f, -5.0f), 30.0f),
    pLight2(BaseLight(glm::vec3(0.0f, 0.5f, 1.0f), 50.8f), Attenuation(0.0f, 0.0f, 1.f), glm::vec3(-2.0f, 1.0f, -5.0f), 30.0f),
    sLight1(PointLight(BaseLight(glm::vec3(0.0f, 1.0f, 0.0f), 50.8f), Attenuation(0.0f, 0.0f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), 30.0f),
    glm::vec3(7.0f, 2.0f, 1.0f), 0.7f)
    
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
        auto mouseLeft = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        //glfwSetCursorEnterCallback(window, cursor_enter);
        
        if (EscKey == GLFW_PRESS)
        {
            glfwTerminate();
                exit(0);
        }
        else if (camUp == GLFW_PRESS)
        {
            camY -= 0.2f;
            camera.camUpdate(glm::vec3(camX, camY, camZ));
        }
        else if (camDown == GLFW_PRESS)
        {
            camY += 0.2f;
            camera.camUpdate(glm::vec3(camX, camY, camZ));
        }
        else if (camLeft == GLFW_PRESS)
        {
            camX -= 0.2f;
            camera.camUpdate(glm::vec3(camX, camY, camZ));
        }
        else if (camRight == GLFW_PRESS)
        {
            camX += 0.2f;
            camera.camUpdate(glm::vec3(camX, camY, camZ));
        }
        else if (zoomIn == GLFW_PRESS)
        {
            camZ += 0.2f;
            camera.camUpdate(glm::vec3(camX, camY, camZ));
        }
        else if (zoomOut == GLFW_PRESS)
        {
            camZ -= 0.2f;
            camera.camUpdate(glm::vec3(camX, camY, camZ));
        }
        else if (mouseLeft == GLFW_PRESS)
        {
            glfwGetCursorPos(window, &xpos, &ypos);
            camera.mouseUpdate(glm::vec2(xpos, ypos));
        }


    }
}

//might remove this if i cant get it working
void        MainGame::cursor_enter(GLFWwindow *window, int entered)
{
    if (entered)
    {
        glfwGetCursorPos(window, &xpos, &ypos);
    }
}

void        MainGame::gameLoop()
{
    Transform           transform;
    Transform          transform2;
    transform.setProjection(70.0f, (float)getWidth(), (float)getHeight(), 0.1f, 1000.0f);
    transform2.setProjection(70.0f, (float)getWidth(), (float)getHeight(), 0.1f, 1000.0f);

    Texture     texture("assets/wood.jpg");
    Material    material(texture, glm::vec3(0.0, 0.0, 0.0), 1, 8);
    Sprite sprite1("assets/monkey3.obj");
    Sprite sprite2("assets/testBoxNoUV.obj");
    
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
    
    camY = 0.0f;
    camX = 0.0f;
    camZ = -6.0f;
    camera.initCamera(glm::vec3(camX, camY, camZ), 70.0f, (float)getWidth() / (float)getHeight(), 0.01f, 1000.0f); 
    shader.setAmbientLight(glm::vec3(0.1f,0.1f,0.1f));
    transform.getRot().y = 3.15f;
    transform2.getRot().y = 3.15f;    
    transform2.getPos().x = 5.0f;
    
    while (gameState != GameState::EXIT)
    {
        float cosCounter = cosf(counter);
        float sinCounter = sinf(counter);

        glClearDepth(1.0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        transform.getPos().y = sinCounter / 10;
        
        material.getColor() = glm::vec3(0.6, 0.3, 0.0);
        
        shader.use();

        //moving spotlight
        sLightArray[0].setDirection(glm::vec3(sinCounter * 10, 2.0f, 1.0f));
        shader.setSpotLight(sLightArray);
    
        //mesh one
        shader.update(transform, camera, material);
        sprite2.draw();

        //mesh two
        shader.update(transform2, camera, material);
        sprite1.draw();
        
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
