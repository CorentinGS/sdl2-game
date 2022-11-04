#include "draw.h"

/*
 * Prepare the scene for drawing
 */
void
prepareScene(void) {
    // Set the color to clear the screen with
    SDL_SetRenderDrawColor(app.renderer, 46, 46, 46, 255);
    // Clear the screen
    SDL_RenderClear(app.renderer);
}

/*
 * Present the scene to the screen
 */
void
presentScene(void) {
    // Show the renderer on the screen
    SDL_RenderPresent(app.renderer);
}

/*
 * Draw a texture
 * @param texture The texture to draw
 * @param x The x coordinate to draw at
 * @param y The y coordinate to draw at
 * @param center Whether to center the texture
 */
void
blit(SDL_Texture* texture, int x, int y, int center) {
    // The destination rectangle
    SDL_Rect dest;

    // Set the x and y coordinates
    dest.x = x;
    dest.y = y;

    // Query the texture to get its width and height
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    // If we want to center the texture
    if (center) {
        dest.x -= dest.w / 2; // Move the x coordinate to the left by half the width
        dest.y -= dest.h / 2; // Move the y coordinate up by half the height
    }

    // Draw the texture
    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

/*
 * Draw a texture with a source rectangle and a destination rectangle
 * @param texture The texture to draw
 * @param src The source rectangle
 * @param x The x coordinate to draw at
 * @param y The y coordinate to draw at
 */
void
blitRect(SDL_Texture* texture, SDL_Rect* src, int x, int y) {
    // The destination rectangle
    SDL_Rect dest;

    // Set the x and y coordinates
    dest.x = x;
    dest.y = y;

    // Set the width and height to the width and height of the source rectangle
    dest.w = src->w;
    dest.h = src->h;

    // Draw the texture
    SDL_RenderCopy(app.renderer, texture, src, &dest);
}
