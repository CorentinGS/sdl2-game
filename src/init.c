#include "init.h"

/*
 * Init the SDL library and create the window and renderer.
 */
void
initSDL(void) {
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED;

    windowFlags = 0;

    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Couldn't init SDL: %s\n", SDL_GetError());
        exit(1);
    }

    // Init SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        printf("Couldn't init Mixer\n");
        exit(1);
    }

    Mix_AllocateChannels(MAX_SND_CHANNELS); // Allocate channels for sounds

    // Create the window
    app.window = SDL_CreateWindow(GAME_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, windowFlags);

    // Set the renderer to use linear interpolation
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    // Create the renderer
    app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

    // Init SDL_image
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    // Hide the cursor
    SDL_ShowCursor(SDL_DISABLE);
}

/*
 * Init the game
 */
void
initGame(void) {
    // Load the fonts
    initFonts();

    // Load the sounds
    initSounds();

    // Load the music
    // loadMusic("music/intro.mp3");

    // Play the music
    playMusic(1);
}

// Clean SDL
void
cleanup(void) {
    // Destroy the renderer
    SDL_DestroyRenderer(app.renderer);

    // Destroy the window
    SDL_DestroyWindow(app.window);

    // Quit SDL
    SDL_Quit();
}
