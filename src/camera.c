/******************************************************************************
 * Copyright (c) 2022.                                                        *
 *                                                                            *
 *                                                                            *
 * Game engine                            ______   _______      _______.      *
 * camera.c                              /      | /  _____|    /       |      *
 *                                      |  ,----'|  |  __     |   (----`      *
 * By: CorentinGS                       |  |     |  | |_ |     \   \          *
 * <c.giaufersaubert@outlook.com>       |  `----.|  |__| | .----)   |         *
 *                                       \______| \______| |_______/  (_/ -/  *
 * LICENCE: MIT                                                        /  /   *
 * Created: 2022/11/7 by CorentinGS                                           *
 *                                                                            *
 ******************************************************************************/

#include "camera.h"

/*
 * Move the camera to the player position
 */
void
doCamera(void) {

    stage.camera.x = (int)player->x + (player->w / 2);
    stage.camera.y = (int)player->y + (player->h / 2);

    stage.camera.x -= (SCREEN_WIDTH / 2);
    stage.camera.y -= (SCREEN_HEIGHT / 2);

    stage.camera.x = MIN(MAX(stage.camera.x, 0), (MAP_WIDTH * TILE_SIZE) - SCREEN_WIDTH);
    stage.camera.y = MIN(MAX(stage.camera.y, 0), (MAP_HEIGHT * TILE_SIZE) - SCREEN_HEIGHT);
}
