/******************************************************************************
 * Copyright (c) 2022.                                                        *
 *                                                                            *
 *                                                                            *
 * Game engine                            ______   _______      _______.      *
 * textures.c                            /      | /  _____|    /       |      *
 *                                      |  ,----'|  |  __     |   (----`      *
 * By: CorentinGS                       |  |     |  | |_ |     \   \          *
 * <c.giaufersaubert@outlook.com>       |  `----.|  |__| | .----)   |         *
 *                                       \______| \______| |_______/  (_/ -/  *
 * LICENCE: MIT                                                        /  /   *
 * Created: 2022/11/7 by CorentinGS                                           *
 *                                                                            *
 ******************************************************************************/

#include "textures.h"

/*
 * Load a texture from cache
 * @param name The name of the texture
 */
static SDL_Texture*
getTexture(char* name) {
    Texture* t; // The texture to return

    // Loop through the texture cache
    for (t = app.textureHead.next; t != NULL; t = t->next) {
        // If the texture is found, return it
        if (strcmp(t->name, name) == 0) {
            return t->texture; // Return the texture
        }
    }

    return NULL;
}

/*
 * Add a texture to the cache
 * @param name The name of the texture
 * @param texture The texture to add
 */
static void
addTextureToCache(char* name, SDL_Texture* sdlTexture) {
    Texture* texture;

    texture = malloc(sizeof(Texture)); // Allocate memory for the texture
    memset(texture, 0, sizeof(Texture));

    app.textureTail->next = texture; // Add the texture to the end of the texture list
    app.textureTail = texture;       // Set the tail to the new texture

    strncpy(texture->name, name, MAX_NAME_LENGTH); // Copy the name to the texture
    texture->name[MAX_NAME_LENGTH - 1] = '\0';     // Make sure the name is null terminated
    texture->texture = sdlTexture;                 // Set the texture
}

/*
 * Load a texture
 * @param filename The filename of the texture
 */
SDL_Texture*
loadTexture(char* filename) {
    SDL_Texture* texture;

    texture = getTexture(filename); // Get the texture from the cache

    // If the texture is not in the cache
    if (texture == NULL) {

        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s ...", filename);
        texture = IMG_LoadTexture(app.renderer, filename); // Load the texture from the file
        addTextureToCache(filename, texture);              // Add the texture to the cache
    }

    return texture;
}
