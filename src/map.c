/******************************************************************************
 * Copyright (c) 2022.                                                        *
 *                                                                            *
 *                                                                            *
 * Game engine                            ______   _______      _______.      *
 * map.c                                 /      | /  _____|    /       |      *
 *                                      |  ,----'|  |  __     |   (----`      *
 * By: CorentinGS                       |  |     |  | |_ |     \   \          *
 * <c.giaufersaubert@outlook.com>       |  `----.|  |__| | .----)   |         *
 *                                       \______| \______| |_______/  (_/ -/  *
 * LICENCE: MIT                                                        /  /   *
 * Created: 2022/11/7 by CorentinGS                                           *
 *                                                                            *
 ******************************************************************************/

#include "map.h"

static void loadTiles(void);
static void loadMap(const char* filename);
int isInsideMap(int x, int y);

static SDL_Texture* tiles[MAX_TILES];

/*
 * Init the map
 */
void
initMap(void) {
    memset(&stage.map, 0, sizeof(int) * MAP_WIDTH * MAP_HEIGHT);
    loadTiles(); // Load the tiles

    int level = app.level; // Get the level
    switch (level) {
        case 1:
            loadMap("data/map01.dat");
            break;
        case 2:
            loadMap("data/map02.dat");
            break;
        case 3:
            loadMap("data/map03.dat");
            break;
        default:
            loadMap("data/map00.dat");
    }
}

/*
 * Draw the map
 */
void
drawMap(void) {
    int x, y, n, x1, x2, y1, y2, mx, my;

    // Get the map offset (the map is bigger than the screen)
    x1 = (stage.camera.x % TILE_SIZE) * -1;
    x2 = x1 + MAP_RENDER_WIDTH * TILE_SIZE + (x1 == 0 ? 0 : TILE_SIZE);

    y1 = (stage.camera.y % TILE_SIZE) * -1;
    y2 = y1 + MAP_RENDER_HEIGHT * TILE_SIZE + (y1 == 0 ? 0 : TILE_SIZE);

    // Get the map coordinates
    mx = stage.camera.x / TILE_SIZE;
    my = stage.camera.y / TILE_SIZE;

    // Loop through the map
    for (y = y1; y < y2; y += TILE_SIZE) {
        for (x = x1; x < x2; x += TILE_SIZE) {
            if (isInsideMap(mx, my)) {
                // Get the tile number
                n = stage.map[mx][my];

                // Draw the tile
                // TODO: Prevent n from being out of bounds
                blit(tiles[n], x, y, 0);
            }

            ++mx;
        }

        mx = stage.camera.x / TILE_SIZE; // Reset the x coordinate

        ++my;
    }
}

/*
 * Load the tiles
 */
static void
loadTiles(void) {
    int i;
    char filename[MAX_FILENAME_LENGTH];

    for (i = 0; i < MAX_TILES; i++) {
        sprintf(filename, "gfx/tile%d.png", i);

        tiles[i] = loadTexture(filename); // Load the tile texture
    }
}

/*
 * Load the map
 * @param filename The filename of the map's data
 */
static void
loadMap(const char* filename) {
    char *data, *p;
    int x, y;

    data = readFile(filename); // Read the file

    p = data;

    // Loop through the map
    for (y = 0; y < MAP_HEIGHT; y++) {
        for (x = 0; x < MAP_WIDTH; x++) {
            // Set the tile number
            sscanf(p, "%d", &stage.map[x][y]);

            do {
                ++p;                           // Increment the pointer
            } while (*p != ' ' && *p != '\n'); // While the pointer is not a space or a new line
        }
    }

    // Free the data
    if (data != NULL) {
        free(data);
    }
}

/*
 * Check if the coordinates are inside the map
 * @param x The x coordinate
 * @param y The y coordinate
 * @return 1 if the coordinates are inside the map, 0 otherwise
 */
int
isInsideMap(int x, int y) {
    return x >= 0 && y >= 0 && x < MAP_WIDTH && y < MAP_HEIGHT;
}
