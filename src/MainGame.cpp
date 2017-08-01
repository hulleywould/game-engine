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

    initShaders();
}

void    MainGame::initShaders()
{
    colorProgram.compileShaders("src/shaders/colorShading.vert", "src/shaders/colorShading.frag");
    colorProgram.addAttribute("position");
    colorProgram.addAttribute("texCoord");
    colorProgram.addAttribute("normal");
    colorProgram.linkShaders();
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
        /*turned key_callback into a lambda function
        **the processInput function is now in one place
        **minimizing the extra function call.
        */
        /*glfwSetKeyCallback(window, [](GLFWwindow *win, int key, int scancodes, int action, int modes) {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            {
                glfwTerminate();
                exit(0);
            }
            else if(key == GLFW_KEY_UP && action == GLFW_PRESS) {
                
            }
        });*/
        auto EscKey = glfwGetKey(window, GLFW_KEY_ESCAPE);
        auto W = glfwGetKey(window, GLFW_KEY_W);
        auto S = glfwGetKey(window, GLFW_KEY_S);
        auto A = glfwGetKey(window, GLFW_KEY_A);
        auto D = glfwGetKey(window, GLFW_KEY_D);
        auto zoomIn = glfwGetKey(window, GLFW_KEY_Q);
        auto zoomOut = glfwGetKey(window, GLFW_KEY_E);
        if (EscKey == GLFW_PRESS)
        {
            glfwTerminate();
                exit(0);
        }
        else if (W == GLFW_PRESS)
        {
            camY += 0.01f;
            camera.camUpdate(glm::vec3(camX, camY, camZ));
        }
        else if (S == GLFW_PRESS)
        {
            camY -= 0.01f;
            camera.camUpdate(glm::vec3(camX, camY, camZ));
        }
        else if (A == GLFW_PRESS)
        {
            camX -= 0.01f;
            camera.camUpdate(glm::vec3(camX, camY, camZ));
        }
        else if (D == GLFW_PRESS)
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
    /*Vertex vertices[] = {   Vertex(glm::vec3(-0.5, -0.5, 0.0), glm::vec2(2.0, 0.0)),
                        Vertex(glm::vec3(0.0, 0.5, 0.0), glm::vec2(0.0, -2.0)),
                        Vertex(glm::vec3(0.5, -0.5, 0.0), glm::vec2(-0.5, 0.0)) };
    unsigned int indices[] = { 0, 1, 2 };*/
       
    Transform   transform;
    Texture texture("assets/wood.jpg");

    //Sprite sprite(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
    Sprite sprite2("assets/monkey3.obj");
    camY = 0.0f;
    camX = 0.0f;
    camZ = -3.0f;
    while (gameState != GameState::EXIT)
    {
    
        glClearDepth(1.0);
        GLuint transformUniform = colorProgram.getUniformLocation("transform");
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        float sinCounter = sinf(counter);
        float cosCounter = cosf(counter);
        
        
        transform.getRot().y = counter / 10;
        //transform.getRot().x = sinCounter;

        colorProgram.use();

        colorProgram.update(transform, camera);
        
        sprite2.draw();
        
        colorProgram.unuse();

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

