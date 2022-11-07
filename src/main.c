/******************************************************************************
 * Copyright (c) 2022.                                                        *
 *                                                                            *
 *                                                                            *
 * Game engine                            ______   _______      _______.      *
 * main.c                                /      | /  _____|    /       |      *
 *                                      |  ,----'|  |  __     |   (----`      *
 * By: CorentinGS                       |  |     |  | |_ |     \   \          *
 * <c.giaufersaubert@outlook.com>       |  `----.|  |__| | .----)   |         *
 *                                       \______| \______| |_______/  (_/ -/  *
 * LICENCE: MIT                                                        /  /   *
 * Created: 2022/11/7 by CorentinGS                                           *
 *                                                                            *
 ******************************************************************************/

#include "main.h"

static void capFrameRate(long* then, float* remainder);

/*
 * Main function
 */
int
main(int argc, char* argv[]) {

    int level = 1, score = 0; // Set the level and score to 1

    memset(&app, 0, sizeof(App));

    char name[MAX_NAME_LENGTH];
    printf("Enter your name ! (only MAJ)      "); // Ask the player to enter his name
    fgets(name, sizeof(name), stdin);             // Get the player's name

    strcpy(app.playerName, name); // Copy the player's name

    while (mainMenu(&level) != 1) { // While the player doesn't want to quit or play the game
        ;
    }

    app.textureTail = &app.textureHead; // Set the textureTail to the textureHead
    app.level = level;                  // Set the level to the level chosen by the player
    app.score = score;                  // Set the score to default value (1)

    // Initialize SDL
    initSDL();

    // Cleanup SDL when the program exits
    atexit(cleanup);

    // Load the game
    initGame();

    // Run the game loop
    startLevel();

    return 0;
}

/*
 * Start the game loop
 */
void
startLevel(void) {
    long then;
    float remainder;
    int level = app.level;
    uint time1, time2 = 0;

    // Init the stage
    initStage();

    // Set the time
    then = SDL_GetTicks();

    remainder = 0; // Set the remainder to 0

    // Run the game loop
    forever {
        // Prepare the scene
        prepareScene();

        // Input
        doInput();

        // Logic
        app.delegate.logic();

        // Get the time
        time1 = SDL_GetTicks();

        // If the time is greater than 2000 ms (2 seconds)
        if (time1 - time2 > 2000) {
            // Decrease player health
            player->health = player->health - 1;
            time2 = time1;
        }

        // Draw
        app.delegate.draw();

        // Present the scene
        presentScene();

        // Cap the frame rate
        capFrameRate(&then, &remainder);
        if (level != app.level) {
            break;
        }
    }
    // startLevel();
}

/*
 * Cap the frame rate
 * @param then The time
 * @param remainder The remainder
 */
static void
capFrameRate(long* then, float* remainder) {
    long wait, frameTime;

    wait = 16 + *remainder;

    *remainder -= (int)*remainder;

    frameTime = SDL_GetTicks() - *then;

    wait -= frameTime;

    if (wait < 1) {
        wait = 1;
    }

    SDL_Delay(wait);

    *remainder += 0.667;

    *then = SDL_GetTicks();
}
