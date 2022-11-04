#include "text.h"

static SDL_Texture* fontTexture;
static char drawTextBuffer[MAX_LINE_LENGTH];

/*
 * Load the font texture
 */
void
initFonts(void) {
    fontTexture = loadTexture("gfx/font.png");
}

/*
 * Draw text
 * @param x The x coordinate
 * @param y The y coordinate
 * @param r The red component of the text's color
 * @param g The green component of the text's color
 * @param b The blue component of the text's color
 * @param format The text to draw
 */
void
drawText(int x, int y, int r, int g, int b, int align, char* format, ...) {
    int i, len, c;
    SDL_Rect rect; // The rectangle to draw
    va_list args;  // The list of arguments

    memset(&drawTextBuffer, '\0', sizeof(drawTextBuffer)); // Clear the buffer

    va_start(args, format);                 // Start the list
    vsprintf(drawTextBuffer, format, args); // Add the text to the buffer
    va_end(args);                           // End the list

    len = strlen(drawTextBuffer); // Get the length of the text

    switch (align) {
        case TEXT_RIGHT:
            x -= (len * GLYPH_WIDTH);
            break;

        case TEXT_CENTER:
            x -= (len * GLYPH_WIDTH) / 2;
            break;
    }

    rect.w = GLYPH_WIDTH;  // Set the width of the rectangle
    rect.h = GLYPH_HEIGHT; // Set the height of the rectangle
    rect.y = 0;            // Set the y coordinate of the rectangle

    SDL_SetTextureColorMod(fontTexture, r, g, b); // Set the color of the texture

    for (i = 0; i < len; ++i) {
        c = drawTextBuffer[i];

        if (c >= ' ' && c <= 'Z') {
            rect.x = (c - ' ') * GLYPH_WIDTH;

            blitRect(fontTexture, &rect, x, y);

            x += GLYPH_WIDTH;
        }
    }
}
