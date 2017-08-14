#ifndef MENU_HPP
# define MENU_HPP

#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

class menu {
    private:
        struct nk_context   *ctx;
        GLFWwindow          *window;

    public:
        menu();
        menu(GLFWwindow *win);
        ~menu();
        int draw_menu();
};

#endif
