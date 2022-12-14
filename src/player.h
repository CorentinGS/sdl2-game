/******************************************************************************
 * Copyright (c) 2022.                                                        *
 *                                                                            *
 *                                                                            *
 * Game engine                            ______   _______      _______.      *
 * player.h                              /      | /  _____|    /       |      *
 *                                      |  ,----'|  |  __     |   (----`      *
 * By: CorentinGS                       |  |     |  | |_ |     \   \          *
 * <c.giaufersaubert@outlook.com>       |  `----.|  |__| | .----)   |         *
 *                                       \______| \______| |_______/  (_/ -/  *
 * LICENCE: MIT                                                        /  /   *
 * Created: 2022/11/7 by CorentinGS                                           *
 *                                                                            *
 ******************************************************************************/

#include "common.h"

extern SDL_Texture* loadTexture(char* filename);
extern void playSound(int id, int channel);
extern void writeScoreboard(const char* filename);
extern int f_get_rand(const int min, const int max);

extern int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

extern App app;
extern Entity* player;
extern Entity* fire;
extern Entity* monster;
extern Stage stage;
