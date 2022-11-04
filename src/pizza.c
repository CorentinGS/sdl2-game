#include "pizza.h"

static void tick(void);
static void touch(Entity* other);

/*
 * Load the pizza
 */
void
initPizza(char* line) {
    Entity* e; // Entity pointer

    e = malloc(sizeof(Entity)); // Allocate memory for the entity
    memset(e, 0, sizeof(Entity));

    stage.entityTail->next = e; // Add the entity to the end of the entity list
    stage.entityTail = e;       // Set the tail to the new entity

    sscanf(line, "%*s %f %f", &e->x, &e->y); // Get the x and y position from the line

    e->health = 1;            // Set the health to 1
    e->flags = E_CONSUMMABLE; // Set the flags to E_CONSUMMABLE

    e->texture = loadTexture("gfx/pizza.png"); // Load the texture
                                               //TODO: Use caching to load the texture only once
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);

    e->tick = tick;   // Set the tick function
    e->touch = touch; // Set the touch function
}

/*
 * Entity tick function
 * Called every frame
 */
static void
tick(void) {
    self->value += 0.1; // Increment the value by 0.1

    self->y += sin(self->value); // Move the entity up and down by the sine of the value
}

/*
 * Entity touch function
 * Called when the entity is touched by another entity
 * @param other The entity that touched this entity
 */
static void
touch(Entity* other) {
    if (self->health > 0 && other == player) // If the entity is alive and the other entity is the player
    {
        self->health = 0; // Kill the entity

        other->health += 5; // Increase the player's health by 5

        app.score += 10; // Increase the score by 10

        // playSound(SND_PIZZA, CH_PIZZA); // Play the pizza sound effect
    }
}
