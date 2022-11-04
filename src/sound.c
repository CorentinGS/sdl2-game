#include "sound.h"

static void loadSounds(void);

static Mix_Chunk* sounds[SND_MAX];
static Mix_Music* music;

/*
 * Load the sounds
 */
void
initSounds(void) {
    memset(sounds, 0, sizeof(Mix_Chunk*) * SND_MAX); // Clear the sounds

    music = NULL;

    loadSounds(); // Load the sounds
}

/*
 * Load the music
 * @param filename The filename of the music
 */
void
loadMusic(char* filename) {
    // If the music is not NULL
    if (music != NULL) {
        Mix_HaltMusic();      // Stop the music
        Mix_FreeMusic(music); // Free the music
        music = NULL;         // Set the music to NULL
    }

    music = Mix_LoadMUS(filename); // Load the music
}

/*
 * Play the music
 * @param loop Whether to loop the music
 */
void
playMusic(int loop) {
    Mix_PlayMusic(music, (loop) ? -1 : 0); // Play the music
}

/*
 * Play a sound
 */
void
playSound(int id, int channel) {
    Mix_PlayChannel(channel, sounds[id], 0); // Play the sound
}

/*
 * Load the sounds
 */
static void
loadSounds(void) {
    sounds[SND_PIZZA] = Mix_LoadWAV("sound/90134__pierrecartoons1979__found-item.ogg"); // Load the pizza sound
}
