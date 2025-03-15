#ifndef TEXTRENDERER_FE_H
#define TEXTRENDERER_FE_H


/* ## OpenGL ## */
#include <glad/glad.h>

/* ## GLMath ## */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* ## FreeType ## */
#include <ft2build.h>
#include FT_FREETYPE_H

/* ## stb ## */
#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

/* ## FE-headers ## */
#include "shader.h"
#include "VAO.h"
#include "VBO.h"
#include "fe-settings.h"

/* ## standart lib ## */
#include <string>
#include <map>
#include <iostream>
#include <cstdio>

struct Glyph {
    unsigned int TextureID;
    glm::ivec2   Size;
    glm::ivec2   Bearing;
    unsigned int Advance;
};


class TextRenderer
{
    public:
        std::map<GLchar, Glyph> glyphs;
        VAO vao;
        unsigned int vbo;

        TextRenderer(Shader &shader, std::string font_path, int font_size);
        void RenderText
        (
             Shader &shader,
             std::string text,
             float x, 
             float y, 
             float scale, 
             glm::vec3 color
        );
};

#endif
