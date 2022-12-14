/******************************************************************************
 * Copyright (c) 2022.                                                        *
 *                                                                            *
 *                                                                            *
 * Game engine                            ______   _______      _______.      *
 * util.c                                /      | /  _____|    /       |      *
 *                                      |  ,----'|  |  __     |   (----`      *
 * By: CorentinGS                       |  |     |  | |_ |     \   \          *
 * <c.giaufersaubert@outlook.com>       |  `----.|  |__| | .----)   |         *
 *                                       \______| \______| |_______/  (_/ -/  *
 * LICENCE: MIT                                                        /  /   *
 * Created: 2022/11/7 by CorentinGS                                           *
 *                                                                            *
 ******************************************************************************/

#include "util.h"

/*
 * Check for collision between two rectangles
 */
int
collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
    // Check if the two rectangles intersect
    return (MAX(x1, x2) < MIN(x1 + w1, x2 + w2)) && (MAX(y1, y2) < MIN(y1 + h1, y2 + h2));
}

void
calcSlope(int x1, int y1, int x2, int y2, float* dx, float* dy) {
    int steps = MAX(abs(x1 - x2), abs(y1 - y2));

    if (steps == 0) {
        *dx = *dy = 0;
        return;
    }

    *dx = (x1 - x2);
    *dx /= steps;

    *dy = (y1 - y2);
    *dy /= steps;
}

int
f_get_rand(const int min, const int max) {
    static int iflag;
    if (!iflag) {
        iflag = 1;
        srand((unsigned int)time(NULL));
    }
    return (min + (rand() % (max - min + 1)));
}