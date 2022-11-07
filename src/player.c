/******************************************************************************
 * Copyright (c) 2022.                                                        *
 *                                                                            *
 *                                                                            *
 * Game engine                            ______   _______      _______.      *
 * player.c                              /      | /  _____|    /       |      *
 *                                      |  ,----'|  |  __     |   (----`      *
 * By: CorentinGS                       |  |     |  | |_ |     \   \          *
 * <c.giaufersaubert@outlook.com>       |  `----.|  |__| | .----)   |         *
 *                                       \______| \______| |_______/  (_/ -/  *
 * LICENCE: MIT                                                        /  /   *
 * Created: 2022/11/7 by CorentinGS                                           *
 *                                                                            *
 ******************************************************************************/

#include "player.h"

static SDL_Texture* mage[4];

/*
 * Initialize the player
 */
void
initPlayer(void) {
    player = malloc(sizeof(Entity));   // Allocate memory for the player
    memset(player, 0, sizeof(Entity)); // Clear the memory

    stage.entityTail->next = player; // Add the player to the end of the entity list
    stage.entityTail = player;       // Set the tail to the player

    int level = app.level; // Get the level from the app struct

    // Switch on the level to load the correct initial position
    switch (level) {
        case 1:
            player->x = 118;
            player->y = 76;
            player->health = 100;
            break;
        case 2:
            player->x = 1076;
            player->y = 873;
            player->health = 110;
            break;
        case 3:
            player->x = 790;
            player->y = 100;
            player->health = 120;
            break;
        case 0:
            player->x = 1000;
            player->y = 1000;
            break;
    }

    // Load the mage texture
    mage[0] = loadTexture("gfx/mage_gauche.png");
    mage[1] = loadTexture("gfx/mage_droite.png");
    mage[2] = loadTexture("gfx/mage.png");
    mage[3] = loadTexture("gfx/mage_dos.png");

    player->texture = mage[3]; // Set the player texture to the mage texture facing up
    player->flags = E_PLAYER;  // Set the flags to E_PLAYER (0)

    SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h); // Get the width and height of the texture
}

/*
 * Player action
 */
void
doPlayer(void) {
    // If the player is dead or the game is paused
    if ((player->health <= 0 && app.level > 0) || app.level > MAX_LEVEL) {
        writeScoreboard("data/scoreboard.dat"); // Write the scoreboard
        app.stored_level = app.level;           // Store the level
        app.level = 0;                          // Set the level to 0
    }

    player->dx = 0; // Set the x velocity to 0
    player->dy = 0; // Set the y velocity to 0

    // If "a" key is pressed
    if (app.keyboard[SDL_SCANCODE_A]) {
        player->dx = -PLAYER_MOVE_SPEED; // Set the x velocity to -PLAYER_MOVE_SPEED
        player->texture = mage[0];       // Set the texture to the mage texture facing left
        player->orientation = LEFT;      // Set the orientation to LEFT
    }

    // If "d" key is pressed
    if (app.keyboard[SDL_SCANCODE_D]) {
        player->dx = PLAYER_MOVE_SPEED; // Set the x velocity to PLAYER_MOVE_SPEED
        player->texture = mage[1];      // Set the texture to the mage texture facing right
        player->orientation = RIGHT;    // Set the orientation to DROITE
    }

    // If "w" key is pressed
    if (app.keyboard[SDL_SCANCODE_W]) {
        player->dy = -PLAYER_MOVE_SPEED; // Set the y velocity to -PLAYER_MOVE_SPEED
        player->texture = mage[3];       // Set the texture to the mage texture facing up
        player->orientation = UP;        // Set the orientation to UP
    }

    // If "s" key is pressed
    if (app.keyboard[SDL_SCANCODE_S]) {
        player->dy = PLAYER_MOVE_SPEED; // Set the y velocity to PLAYER_MOVE_SPEED
        player->texture = mage[2];      // Set the texture to the mage texture facing down
        player->orientation = DOWN;     // Set the orientation to DOWN
    }

    // If "q" key is pressed
    if (app.keyboard[SDL_SCANCODE_Q]) {
        // Debug mode (show the current position)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Position :  %f | %f", player->x,
                       player->y);
        app.keyboard[SDL_SCANCODE_Q] = 0; // Set the "q" key to 0
    }
}