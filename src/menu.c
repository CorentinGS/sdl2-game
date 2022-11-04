#include "menu.h"

int
mainMenu(int* level) {
    int choice, tmp, lev;
    printf(" __________________________________________________________\n");
    printf("|                                                         |\n");
    printf("|                                                         |\n");
    printf("|     1. play                                             |\n");
    printf("|     2. level selection                                  |\n");
    printf("|     3. Top 10                                           |\n");
    printf("|     4. exit                                             |\n");
    printf("|                                                         |\n");
    printf("|_________________________________________________________|\n");

    scanf("%d", &choice);

    switch (choice) {
        case 1:
            tmp = 1;
            break;
        case 2:
            tmp = levelMenu(&lev);
            *level = lev;
            break;
        case 3:;
            Scoreboard array[10];
            readScoreboard("data/scoreboard.dat", array);

            printf("----------------    Top 10 !    ----------------\n");
            printf("  user               score               level  \n");
            printf("------------------------------------------------\n");
            for (int cpt = 0; cpt < 9; cpt++) {
                printf(" %s %d %d\n", array[cpt].playerName, array[cpt].score, array[cpt].level);
            }
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid command\n");
            break;
    }

    return tmp;
}

int
levelMenu(int* level) {
    int choix, tmp;

    printf(" __________________________________________________________\n");
    printf("|                                                         |\n");
    printf("|                                                         |\n");
    printf("|   1. level  1                                           |\n");
    printf("|   2. level 2                                            |\n");
    printf("|   3. level 3                                            |\n");
    printf("|   4. back                                               |\n");
    printf("|                                                         |\n");
    printf("|_________________________________________________________|\n");

    scanf("%d", &choix);

    switch (choix) {
        case 1:
            *level = 1;
            tmp = 1;
            break;
        case 2:
            *level = 2;
            tmp = 1;
            break;
        case 3:
            *level = 3;
            tmp = 1;
            break;
        case 4:
            break;
        default:
            printf("Invalid command\n");
            break;
    }
    return tmp;
}