/******************************************************************************
 * Copyright (c) 2022.                                                        *
 *                                                                            *
 *                                                                            *
 * Game engine                            ______   _______      _______.      *
 * entities.h                            /      | /  _____|    /       |      *
 *                                      |  ,----'|  |  __     |   (----`      *
 * By: CorentinGS                       |  |     |  | |_ |     \   \          *
 * <c.giaufersaubert@outlook.com>       |  `----.|  |__| | .----)   |         *
 *                                       \______| \______| |_______/  (_/ -/  *
 * LICENCE: MIT                                                        /  /   *
 * Created: 2022/11/7 by CorentinGS                                           *
 *                                                                            *
 ******************************************************************************/

#include "common.h"

extern void blit(SDL_Texture* texture, int x, int y, int center);
extern int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
extern int f_get_rand(const int min, const int max);

extern void initPizza(char* line);
extern int isInsideMap(int x, int y);
extern char* readFile(const char* filename);
extern void writeScoreboard(const char* filename);

extern Entity* self;
extern Stage stage;
extern App app;
extern Entity* player;
