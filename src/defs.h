/******************************************************************************
 * Copyright (c) 2022.                                                        *
 *                                                                            *
 *                                                                            *
 * Game engine                            ______   _______      _______.      *
 * defs.h                                /      | /  _____|    /       |      *
 *                                      |  ,----'|  |  __     |   (----`      *
 * By: CorentinGS                       |  |     |  | |_ |     \   \          *
 * <c.giaufersaubert@outlook.com>       |  `----.|  |__| | .----)   |         *
 *                                       \______| \______| |_______/  (_/ -/  *
 * LICENCE: MIT                                                        /  /   *
 * Created: 2022/11/7 by CorentinGS                                           *
 *                                                                            *
 ******************************************************************************/

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define STRNCPY(dest, src, n)                                                                                          \
    strncpy(dest, src, n);                                                                                             \
    dest[n - 1] = '\0'

#define SCREEN_WIDTH        1280
#define SCREEN_HEIGHT       720

#define MAX_TILES           8

#define TILE_SIZE           64

#define MAP_WIDTH           33
#define MAP_HEIGHT          30

#define MAP_RENDER_WIDTH    20
#define MAP_RENDER_HEIGHT   12

#define PLAYER_MOVE_SPEED   6

#define MAX_NAME_LENGTH     32
#define MAX_LINE_LENGTH     2048
#define MAX_FILENAME_LENGTH 1024

#define MAX_KEYBOARD_KEYS   350

#define MAX_SND_CHANNELS    16

#define GLYPH_WIDTH         18
#define GLYPH_HEIGHT        29

#define MAX_MONSTER_SPAWNER 3
#define MAX_LEVEL           3

#define GAME_NAME           "The Legend of Zelda"

enum { TEXT_LEFT, TEXT_CENTER, TEXT_RIGHT };

enum { SND_PIZZA, SND_MAX };

enum {
    E_PLAYER,
    E_CONSUMMABLE,
};

enum { FLAG_NO_HIT, FLAG_HIT };

enum { CH_PLAYER, CH_PIZZA };

enum { TRUE, FALSE };

enum { UP, DOWN, RIGHT, LEFT };

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_BLUE    "\x1b[34m"