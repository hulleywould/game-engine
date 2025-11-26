#include "TextRenderer.hpp"

#include <iostream>

TextRenderer::TextRenderer()
    : ftLibrary(nullptr),
      ftFace(nullptr),
      initialized(false),
      VAO(0),
      VBO(0)
{
}

TextRenderer::~TextRenderer()
{
    if (ftFace) {
        FT_Done_Face(ftFace);
    }
    if (ftLibrary) {
        FT_Done_FreeType(ftLibrary);
    }
}

bool TextRenderer::init(int width, int height, const std::string &fontPath, unsigned int fontSize)
{
    if (FT_Init_FreeType(&ftLibrary)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library\n";
        return false;
    }

    if (FT_New_Face(ftLibrary, fontPath.c_str(), 0, &ftFace)) {
        std::cout << "ERROR::FREETYPE: Failed to load font: " << fontPath << std::endl;
        return false;
    }

    FT_Set_Pixel_Sizes(ftFace, 0, fontSize);

    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load first 128 ASCII characters
    for (unsigned char c = 0; c < 128; c++) {
        if (FT_Load_Char(ftFace, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYPE: Failed to load Glyph for char " << c << std::endl;
            continue;
        }

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            ftFace->glyph->bitmap.width,
            ftFace->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            ftFace->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
            texture,
            glm::ivec2(ftFace->glyph->bitmap.width, ftFace->glyph->bitmap.rows),
            glm::ivec2(ftFace->glyph->bitmap_left, ftFace->glyph->bitmap_top),
            static_cast<GLuint>(ftFace->glyph->advance.x)
        };
        characters.insert(std::pair<char, Character>(c, character));
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    // Configure VAO/VBO for texture quads
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Setup shader
    textShader.compileShaders("src/shaders/text.vert", "src/shaders/text.frag");
    textShader.addAttribute("vertex");
    textShader.linkShaders();
    textShader.addUniform("textColor");
    textShader.addUniform("projection");

    projection = glm::ortho(0.0f, static_cast<float>(width),
                            0.0f, static_cast<float>(height));

    textShader.use();
    textShader.setUniform("projection", projection);
    textShader.unuse();

    initialized = true;
    return true;
}

void TextRenderer::renderText(const std::string &text, float x, float y, float scale, const glm::vec3 &color)
{
    if (!initialized) {
        return;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    textShader.use();
    textShader.setUniform("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // Render characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); ++c) {
        Character ch = characters[*c];

        float xpos = x + ch.bearing.x * scale;
        float ypos = y - (ch.size.y - ch.bearing.y) * scale;

        float w = ch.size.x * scale;
        float h = ch.size.y * scale;

        // 6 vertices per quad, 4 components per vertex (x, y, u, v)
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };

        glBindTexture(GL_TEXTURE_2D, ch.textureID);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Advance cursor for next glyph (note that advance is in 1/64 pixels)
        x += (ch.advance >> 6) * scale;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    textShader.unuse();
}

glm::vec2 TextRenderer::getTextSize(const std::string &text, float scale) const
{
    float width = 0.0f;
    float maxHeight = 0.0f;

    for (char c : text) {
        auto it = characters.find(c);
        if (it == characters.end()) {
            continue;
        }
        const Character &ch = it->second;
        // advance is in 1/64 pixels
        width += (ch.advance >> 6) * scale;
        float h = static_cast<float>(ch.size.y) * scale;
        if (h > maxHeight) {
            maxHeight = h;
        }
    }

    return glm::vec2(width, maxHeight);
}



