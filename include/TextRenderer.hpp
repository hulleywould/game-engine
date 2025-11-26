#ifndef TEXTRENDERER_HPP
#define TEXTRENDERER_HPP

#include <map>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "GlslProgram.hpp"

struct Character {
    GLuint     textureID;  // ID handle of the glyph texture
    glm::ivec2 size;       // Size of glyph
    glm::ivec2 bearing;    // Offset from baseline to left/top of glyph
    GLuint     advance;    // Offset to advance to next glyph
};

class TextRenderer {
public:
    TextRenderer();
    ~TextRenderer();

    // Initialize FreeType and load font. width/height are the screen size in pixels.
    bool init(int width, int height, const std::string &fontPath, unsigned int fontSize = 24);

    // Render text at pixel position (x, y) from bottom-left corner.
    void renderText(const std::string &text, float x, float y, float scale, const glm::vec3 &color);

    // Measure text width/height in pixels at given scale.
    glm::vec2 getTextSize(const std::string &text, float scale) const;

private:
    FT_Library ftLibrary;
    FT_Face    ftFace;
    bool       initialized;

    std::map<char, Character> characters;

    GLuint      VAO;
    GLuint      VBO;
    GlslProgram textShader;
    glm::mat4   projection;
};

#endif


