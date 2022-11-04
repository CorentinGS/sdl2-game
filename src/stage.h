#include "common.h"

extern void doCamera(void);
extern void doEntities(void);
extern void doPlayer(void);
extern void drawEntities(void);
extern void drawMap(void);
extern void initEntities(void);
extern void initMap(void);
extern void initPlayer(void);
extern void readScoreboard(const char* filename, Scoreboard tab[]);

extern void drawText(int x, int y, int r, int g, int b, int align, char* format, ...);

extern App app;
extern Stage stage;
extern Entity* player;
