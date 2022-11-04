#include "entities.h"

static void move(Entity* e);
static void push(Entity* e, float dx, float dy);
static void moveToWorld(Entity* e, float dx, float dy);
static void moveToEntities(Entity* e);
static void loadEnts(const char* filename);
static void addEntFromLine(char* line);

/*
 * Init entities from file
 */
void
initEntities(void) {
    int level = app.level; // Get the level from the app struct
                           // Switch on the level
    switch (level) {
        case 1:
            loadEnts("data/ents01.dat");
            break;
        case 2:
            loadEnts("data/ents02.dat");
            break;
        case 3:
            loadEnts("data/ents03.dat");
            break;
    }
}

/*
 * Do entities actions
 */
void
doEntities(void) {
    // Create a pointer to an entity
    Entity *e, *prev;

    // Set the previous entity to the head of the entity list
    prev = &stage.entityHead;

    // Loop through the entity linked list
    for (e = stage.entityHead.next; e != NULL; e = e->next) {
        self = e; // Set the self pointer to the current entity

        // If the entity has a tick function, call it
        if (e->tick) {
            e->tick();
        }

        // Move the entity
        move(e);

        // If the entity's health is less than or equal to 0
        if (e->health <= 0) {
            /* Remove the entity from the linked list */

            // If the entity is the tail of the list
            if (e == stage.entityTail) {
                stage.entityTail = prev; // Set the tail to the previous entity
            }

            // Set the previous entity's next pointer to the current entity's next pointer
            prev->next = e->next;
            // Free the current entity
            free(e);
            // Set the current entity to the previous entity
            e = prev;
        }
        // Set the previous entity to the current entity
        prev = e;
    }
}

/*
 * Move an entity
 */
static void
move(Entity* e) {

    // Change the entity's x and y position by the entity's dx and dy
    e->x += e->dx;
    push(e, e->dx, 0); // Push the entity horizontally

    // Change the entity's x and y position by the entity's dx and dy
    e->y += e->dy;
    push(e, 0, e->dy); // Push the entity vertically
}

/*
 * Push an entity
 * @param e The entity to push
 * @param dx The amount to push the entity horizontally
 * @param dy The amount to push the entity vertically
 */
static void
push(Entity* e, float dx, float dy) {
    // Move the entity to the world
    moveToWorld(e, dx, dy);
    // Move the entity to other entities to check for collisions
    moveToEntities(e);
}

/*
 * Move an entity to the world
 * @param e The entity to move
 * @param dx The amount to move the entity horizontally
 * @param dy The amount to move the entity vertically
 */
static void
moveToWorld(Entity* e, float dx, float dy) {
    int mx, my, hit, adj;

    // If the entity is moving horizontally
    if (dx != 0) {
        // If the entity is moving right (dx > 0) then set the mx to the entity's right side
        mx = dx > 0 ? (e->x + e->w) : e->x;
        mx /= TILE_SIZE; // Divide the mx by the tile size to get the tile x position

        // Get the tile y position of the entity's top side
        my = (e->y / TILE_SIZE);

        hit = FLAG_NO_HIT; // Set the hit flag to 0 (no hit)

        // If the tile at the mx and my position is outside the map or is a solid tile (!= 0)
        if (!isInsideMap(mx, my) || (stage.map[mx][my] != 0)) {
            hit = FLAG_HIT; // Set the hit flag to 1 (hit)
        }

        // Get the tile y position of the entity's top side
        my = (e->y + e->h - 1) / TILE_SIZE;

        // If the tile at the mx and my position is outside the map or is a solid tile (!= 0)
        if (!isInsideMap(mx, my) || (stage.map[mx][my] != 0)) {
            hit = FLAG_HIT; // Set the hit flag to 1 (hit)
        }

        // If the hit flag is set to 1 (hit)
        if (FLAG_HIT == hit) {
            // If the entity is moving right (dx > 0) then set the adj to negative the entity's width (push the entity left)
            // otherwise set it to the entity's width (push the entity right)
            adj = dx > 0 ? -e->w : TILE_SIZE;

            e->x = (mx * TILE_SIZE) + adj; // Set the entity's x position to the tile x position plus the adj

            e->dx = 0; // Set the entity's dx to 0 (stop the entity)
        }
    }

    // If the entity is moving vertically
    if (dy != 0) {
        // If the entity is moving down (dy > 0) then set the my to the entity's bottom side
        my = dy > 0 ? (e->y + e->h) : e->y;
        my /= TILE_SIZE;

        // Get the tile x position of the entity's left side
        mx = e->x / TILE_SIZE;

        hit = FLAG_NO_HIT; // Set the hit flag to 0 (no hit)

        // If the tile at the mx and my position is outside the map or is a solid tile (!= 0)
        if (!isInsideMap(mx, my) || stage.map[mx][my] != 0) {
            hit = FLAG_HIT; // Set the hit flag to 1 (hit)
        }

        // Get the tile x position of the entity's right side
        mx = (e->x + e->w - 1) / TILE_SIZE;

        // If the tile at the mx and my position is outside the map or is a solid tile (!= 0)
        if (!isInsideMap(mx, my) || stage.map[mx][my] != 0) {
            hit = FLAG_HIT; // Set the hit flag to 1 (hit)
        }

        if (FLAG_HIT == hit) {
            // If the entity is moving down (dy > 0) then set the adj to negative the entity's height (push the entity up)
            // otherwise set it to the entity's height (push the entity down)
            adj = dy > 0 ? -e->h : TILE_SIZE;

            e->y = (my * TILE_SIZE) + adj; // Set the entity's y position to the tile y position plus the adj

            e->dy = 0; // Set the entity's dy to 0 (stop the entity)
        }
    }
}

/*
 * Move an entity to other entities to check for collisions
 * @param e The entity to move
 * @param dx The amount to move the entity horizontally
 * @param dy The amount to move the entity vertically
 */
static void
moveToEntities(Entity* e) {
    // Loop through the entities
    Entity* other;
    for (other = stage.entityHead.next; other != NULL; other = other->next) {
        // If the entity is not the other entity and the entities are colliding
        if (other != e && collision(e->x, e->y, e->w, e->h, other->x, other->y, other->w, other->h)) {
            // If the entity has a touch function
            if (e->touch) {
                // Call the entity's touch function
                e->touch(other);
            }
        }
    }
}

/*
 * Draw an entity
 * TODO: Don't draw entities that are off screen
 */
void
drawEntities(void) {
    // Loop through the entities
    Entity* e;
    for (e = stage.entityHead.next; e != NULL; e = e->next) {
        // Draw the entity
        blit(e->texture, e->x - stage.camera.x, e->y - stage.camera.y, 0);
    }
}

/*
 * Load stage entities
 * @param filename The filename of the entity's data
 */
static void
loadEnts(const char* filename) {
    char line[MAX_LINE_LENGTH];
    char *data, *p;
    int n;

    data = readFile(filename); // Read the file

    // If the data is NULL
    if (data == NULL) {
        // Show an error message
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Unable to load file '%s'", filename);
    }

    p = data; // Set p to the data

    n = 0;

    memset(line, '\0', MAX_LINE_LENGTH);

    /* Loop through the data
     * If the data is not a new line character
     * then add the data to the line
     * otherwise process the line
     */
    while (*p) {
        // If the current character is a new line
        if (*p == '\n') {
            // Add the entity
            addEntFromLine(line);

            // Reset the line
            memset(line, '\0', MAX_LINE_LENGTH);
            n = 0;
        } else {
            // Add the character to the line
            line[n++] = *p;
        }

        ++p; // Increment p
    }

    // Free the data from memory
    if (data) {
        free(data);
    }
}

/*
 * Add an entity from a line of data
 * @param line The line of data
 */
static void
addEntFromLine(char* line) {
    char name[MAX_NAME_LENGTH]; // The name of the entity

    sscanf(line, "%s", name); // Get the name of the entity from the line

    // If the name is "PIZZA"
    if (strcmp(name, "PIZZA") == 0) {
        initPizza(line); // Initialise the pizza
    } else {
        // Show a warning message
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "Unknown entity '%s'", line);
    }
}