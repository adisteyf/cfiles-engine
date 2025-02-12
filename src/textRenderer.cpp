#include "textRenderer.h"

void TextRenderer::init(Shader &shader, std::string font_path)
{
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(WINDOW_WIDTH), 0.0f, static_cast<float>(WINDOW_HEIGHT));
    shader.bind();
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        felogerr("(FreeType 2): Couldn't init FreeType lib.");
        fe_panic();
    }

    if (font_path.empty()) {
        felogerr("(FreeType 2): Failed to load font.");
        fe_panic();
    }

    FT_Face face;
    if (FT_New_Face(ft, font_path.c_str(), 0, &face)) {
        felogerr("(FreeType 2): Failed to load font.");
        fe_panic();
    }

    FT_Set_Pixel_Sizes(face, 0, 100);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned int i=0; i<128; i++) {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            felogerr("(FreeType 2): Failed to load glyph.");
            continue;
        }


        //stbi_write_jpg("fe_glyph.jpg", face->glyph->bitmap.width, face->glyph->bitmap.rows, 3, face->glyph->bitmap.buffer, 100);

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D
        (
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_INT,
            face->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D,   GL_TEXTURE_WRAP_S,       GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D,   GL_TEXTURE_WRAP_T,       GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D,   GL_TEXTURE_MIN_FILTER,   GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,   GL_TEXTURE_MAG_FILTER,   GL_LINEAR);

        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        Glyph glyph =
        {
            texture,
            glm::ivec2(face->glyph->bitmap.width,   face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left,    face->glyph->bitmap_top),
            static_cast<unsigned int>(face->glyph->advance.x)
        };

        glyphs.insert(std::pair<char, Glyph>(i, glyph));
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    printf("TXTRENDER: Killing FT...\n");
    FT_Done_Face(face);
    printf("TXTRENDER: next is FT_Done_FreeType(ft);\n");
    FT_Done_FreeType(ft);
    printf("TXTRENDER: next is vao.bind()\n");

    vao.bind(); // <<
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    printf("TXTRENDER: next is glVertexAttribPointer\n");

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    printf("TXTRENDER: next is glBindBuffer\n");
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    printf("TXTRENDER: next is vao.unbind()\n");
    vao.unbind();
}

void TextRenderer::RenderText(Shader &shader, std::string text, float x, float y, float scale, glm::vec3 color)
{
    shader.bind();
    glUniform3f(glGetUniformLocation(shader.getProgram(), "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    vao.bind();

    std::string::const_iterator g;
    for (g = text.begin(); g != text.end(); g++) {
        Glyph glyph = glyphs[*g];

        float xpos = x + glyph.Bearing.x * scale;
        float ypos = y - (glyph.Size.y - glyph.Bearing.y) * scale;

        float w    = glyph.Size.x * scale;
        float h    = glyph.Size.y * scale;

        float vertices[6][4] =
        {
            /* XVERT    YVERT         UV   */
            { xpos,    ypos+h,    0.f, 0.f },
            { xpos,    ypos,      0.f, 1.f },
            { xpos+w,  ypos,      1.f, 1.f },

            { xpos,    ypos+h,    0.f, 0.f },
            { xpos+w,  ypos,      1.f, 1.f },
            { xpos+w,  ypos+h,    1.f, 0.f },
        };

        glBindTexture(GL_TEXTURE_2D, glyph.TextureID);
        //vao.bind();
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += (glyph.Advance >> 6) * scale;
    }

    vao.unbind();
    glBindTexture(GL_TEXTURE_2D, 0);
}
