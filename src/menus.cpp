#include <menus.hpp>
nanogui::Screen *screen = nullptr;

menus::menus() {
    nanogui::init();
}

menus::menus(GLFWwindow* window) {
    nanogui::init();
    screen = new nanogui::Screen();
    std::cout << "here" << "\n";
    screen->initialize(window, true);
    glfwSetCursorPosCallback(window,
            [](GLFWwindow *, double x, double y) {
            screen->cursorPosCallbackEvent(x, y);
        }
    );

    glfwSetMouseButtonCallback(window,
        [](GLFWwindow *, int button, int action, int modifiers) {
            screen->mouseButtonCallbackEvent(button, action, modifiers);
        }
    );

    glfwSetKeyCallback(window,
        [](GLFWwindow *, int key, int scancode, int action, int mods) {
            screen->keyCallbackEvent(key, scancode, action, mods);
        }
    );

    glfwSetCharCallback(window,
        [](GLFWwindow *, unsigned int codepoint) {
            screen->charCallbackEvent(codepoint);
        }
    );

    glfwSetDropCallback(window,
        [](GLFWwindow *, int count, const char **filenames) {
            screen->dropCallbackEvent(count, filenames);
        }
    );

    glfwSetScrollCallback(window,
        [](GLFWwindow *, double x, double y) {
            screen->scrollCallbackEvent(x, y);
       }
    );

    glfwSetFramebufferSizeCallback(window,
        [](GLFWwindow *, int width, int height) {
            screen->resizeCallbackEvent(width, height);
        }
    );
}

menus::~menus() {
    nanogui::shutdown();
}

void menus::init_start_menu() {
    nanogui::FormHelper *gui = new nanogui::FormHelper(screen);
    nanogui::ref<nanogui::Window> nanoguiWindow = gui->addWindow(Eigen::Vector2i(10, 10), "Bomberman");

    gui->addGroup("");
    gui->addButton("Start Game", []() {
        std::cout << "Start Game" << "\n"; return 1;
    })->setTooltip("Start a new gae");
    gui->addButton("Load Game", []() {
        std::cout << "Load Game" << "\n"; return 2;
    })->setTooltip("Load your game");

    gui->addGroup("");
    gui->addButton("Settings", []() {
        std::cout << "settings" << "\n"; return 3;
    })->setTooltip("Change your wonderful settings");

    screen->setVisible(true);
    screen->performLayout();
    nanoguiWindow->center();
}

int menus::render_menu() {
    screen->drawContents();
    screen->drawWidgets();
    return 0;
}
