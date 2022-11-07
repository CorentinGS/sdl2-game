/******************************************************************************
 * Copyright (c) 2022.                                                        *
 *                                                                            *
 *                                                                            *
 * Game engine                            ______   _______      _______.      *
 * stage.c                               /      | /  _____|    /       |      *
 *                                      |  ,----'|  |  __     |   (----`      *
 * By: CorentinGS                       |  |     |  | |_ |     \   \          *
 * <c.giaufersaubert@outlook.com>       |  `----.|  |__| | .----)   |         *
 *                                       \______| \______| |_______/  (_/ -/  *
 * LICENCE: MIT                                                        /  /   *
 * Created: 2022/11/7 by CorentinGS                                           *
 *                                                                            *
 ******************************************************************************/

#include "stage.h"

static void logic(void);
static void draw(void);
static void drawHud(void);
static void drawScoreboard(void);

/*
 * Initialize the stage
 */
void
initStage(void) {
    app.delegate.logic = logic; // Set the logic function
    app.delegate.draw = draw;   // Set the draw function

    memset(&stage, 0, sizeof(Stage)); // Clear the stage

    // Entity linked lists
    stage.entityTail = &stage.entityHead;

    // Init the entities
    initEntities();

    // Init the player
    initPlayer();

    // Init the map
    initMap();
}

/*
 * Logic function
 */
static void
logic(void) {

    doPlayer(); // Player logic

    doEntities(); // Entity logic

    doCamera(); // Camera logic
}

/*
 * Draw function
 */
static void
draw(void) {

    SDL_SetRenderDrawColor(app.renderer, 128, 192, 255, 255); // Set the draw color
    SDL_RenderFillRect(app.renderer, NULL);                   // Draw a rectangle

    drawMap(); // Draw the map

    drawEntities(); // Draw the entities

    if (app.level == 0) {
        drawScoreboard(); // Draw the scoreboard
    } else {
        drawHud(); // Draw the HUD
    }
}

/*
 * Draw the HUD
 */
static void
drawHud(void) {
    SDL_Rect r; // Rectangle

    // Draw the HUD bar
    r.x = 0;
    r.y = 0;
    r.w = SCREEN_WIDTH;
    r.h = 35;

    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND); // Set the blend mode
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 196);            // Set the draw color
    SDL_RenderFillRect(app.renderer, &r);                          // Draw the rectangle
    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);  // Set the blend mode

    // Draw the hud
    drawText(SCREEN_WIDTH - 5, 5, 255, 255, 255, TEXT_RIGHT, "PLAYER: %s    LEVEL: %d    SCORE: %d    HEALTH: %d",
             app.playerName, app.level, app.score, player->health);
}

/*
 * Draw the scoreboard
 */
static void
drawScoreboard(void) {
    SDL_Rect r;
    int i, diff = 40;
    r.x = 0;
    r.y = 0;
    r.w = SCREEN_WIDTH;
    r.h = SCREEN_HEIGHT;

    Scoreboard tab[10];
    readScoreboard("data/scoreboard.dat", tab);

    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 196);
    SDL_RenderFillRect(app.renderer, &r);
    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
    for (i = 0; i < 10; i++) {
        drawText(SCREEN_WIDTH - 20, 30 + (diff * i), 255, 255, 255, TEXT_RIGHT,
                 "PLAYER: %s          LEVEL: %d          SCORE: %d", tab[i].playerName, tab[i].level, tab[i].score);
    }

    drawText(SCREEN_WIDTH - 20, 30 + (diff * 15), 255, 255, 255, TEXT_RIGHT,
             "VOTRE SCORE :          LEVEL: %d          SCORE: %d", app.stored_level, app.score);
}
