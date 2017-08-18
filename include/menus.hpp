#ifndef MENUS_HPP
# define MENUS_HPP

#include <nanogui/nanogui.h>
#include <iostream>

class menus {
private:


public:
    menus ();
    menus (GLFWwindow* window);
    ~menus();
    void   init_start_menu();
    int    render_menu();
};

#endif
