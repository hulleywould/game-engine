#include <menu.hpp>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION

#include <nuklear.h>
#include <nuklear_glfw_gl3.h>

menu::menu() {}

menu::menu(GLFWwindow *win) {
    window = win;
    ctx = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS);
    {struct nk_font_atlas *atlas;
    nk_glfw3_font_stash_begin(&atlas);
    nk_glfw3_font_stash_end();}
}

menu::~menu() {
    nk_glfw3_shutdown();
}

int menu::draw_menu() {
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        nk_glfw3_new_frame();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (nk_begin(ctx, "Bomberman", nk_rect(125, 100, 400, 300),
            NK_WINDOW_BORDER|NK_WINDOW_TITLE))
        {
            nk_layout_row_dynamic(ctx, 50, 1);
            if (nk_button_label(ctx, "New Game"))
                return 1;

            nk_layout_row_dynamic(ctx, 50, 1);
            if (nk_button_label(ctx, "Load Game"))
                return 2;


            nk_layout_row_dynamic(ctx, 50, 1);
            if (nk_button_label(ctx, "Settings"))
                return 3;
        }
        nk_end(ctx);

        nk_glfw3_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
        glfwSwapBuffers(window);
    }
    return 0;
}
