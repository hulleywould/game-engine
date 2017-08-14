#include <menu.hpp>

menu::menu() {}

menu::menu(GLFWwindow *win) {
    ctx = nk_glfw3_init(win, NK_GLFW3_INSTALL_CALLBACKS);
    {struct nk_font_atlas *atlas;
    nk_glfw3_font_stash_begin(&atlas);
    nk_glfw3_font_stash_end();}
}

menu::~menu() {
    nk_glfw3_shutdown();
}

int menu::draw_menu(GLFWwindow *win) {
    while (!glfwWindowShouldClose(win))
    {
        glfwPollEvents();
        nk_glfw3_new_frame();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (nk_begin(ctx, "Game Menu", nk_rect(325, 200, 550, 300),
            NK_WINDOW_BORDER|NK_WINDOW_TITLE))
        {
            nk_layout_row_static(ctx, 50, 523, 10);
            if (nk_button_label(ctx, "New Game"))
                fprintf(stdout, "new game\n");

            nk_layout_row_dynamic(ctx, 50, 1);
            if (nk_button_label(ctx, "Load Game"))
                fprintf(stdout, "load game\n");


            nk_layout_row_dynamic(ctx, 50, 1);
            if (nk_button_label(ctx, "Settings"))
                fprintf(stdout, "settings menu\n");
        }
        nk_end(ctx);

        nk_glfw3_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
        glfwSwapBuffers(win);
    }
    return 0;
}
