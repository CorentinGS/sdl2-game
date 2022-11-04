#include "io.h"

#define MAX_PLAYER_SCOREBOARD 10

void sortArray(Scoreboard array[]);
void readScoreboard(const char* filename, Scoreboard array[]);
void writeScoreboard(const char* filename);

/*
 * Read a file and return its content as a string
 * @param filename The file to read
 * @return The file's content as a string
 */
char*
readFile(const char* filename) {
    char* buffer = 0;     // The buffer
    unsigned long length; // The length of the file

    FILE* file = fopen(filename, "rb"); // Open the file in binary mode

    // If the file is not NULL
    if (file) {
        // Get the length of the file
        fseek(file, 0, SEEK_END); // Seek to the end of the file
        length = ftell(file);     // Get the current byte offset in the file
        fseek(file, 0, SEEK_SET); // Seek back to the beginning of the file

        buffer = malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator

        memset(buffer, 0, length + 1);

        // Fill the buffer with the file's content
        fread(buffer, 1, length, file);

        fclose(file); // Close the file

        buffer[length] = '\0'; // Null terminator
    }

    return buffer;
}

/*
 * Read the scoreboard from a file
 * @param filename The file to read
 * @param tab The scoreboard table to fill
 */
void
readScoreboard(const char* filename, Scoreboard array[]) {
    char* buffer = 0;
    char line[MAX_LINE_LENGTH];
    char* p;
    int n = 0, i = 0;
    unsigned long length;

    FILE* file = fopen(filename, "rb"); // Open the file in binary mode

    // If the file is not NULL
    if (file) {
        // Get the length of the file
        fseek(file, 0, SEEK_END);
        length = ftell(file);
        fseek(file, 0, SEEK_SET);

        // Allocate a buffer for the entire length of the file and a null terminator
        buffer = malloc(length + 1);
        memset(buffer, 0, length + 1);

        // Fill the buffer with the file's content
        fread(buffer, 1, length, file);

        fclose(file); // Close the file

        buffer[length] = '\0'; // Null terminator
    }
    p = buffer; // Set p to the data

    memset(line, '\0', MAX_LINE_LENGTH); // Reset the line

    /* Loop through the data and fill the scoreboard table
     * Check if p is not null
     * If the data is not a new line character
     * then add the data to the line
     * otherwise process the line
     */
    if (p) {
        while (*p && i < 10) {
            if (*p == '\n') {
                sscanf(line, "%s %d %d", array[i].playerName, &array[i].score, &array[i].level);
                memset(line, '\0', MAX_LINE_LENGTH);
                n = 0;
                ++i;
            } else {
                line[n++] = *p;
            }

            ++p;
        }
    }

    // Free the data from memory
    if (buffer) {
        free(buffer);
    }
}

/*
 * Sort the scoreboard array by score and level
 * It will sort the array in descending order using the bubble sort algorithm as data are small & almost sorted
 * @param array The array to sort
 */
void
sortArray(Scoreboard array[]) {
    int i, j;
    Scoreboard tmp;

    // Sort the array
    for (i = 0; i < MAX_PLAYER_SCOREBOARD - 1; i++) {
        for (j = 0; j < MAX_PLAYER_SCOREBOARD - i - 1; j++) {
            if (array[j].score < array[j + 1].score) {
                tmp.score = array[j].score;
                array[j].score = array[j + 1].score;
                array[j + 1].score = tmp.score;

                strcpy(tmp.playerName, array[j].playerName);
                strcpy(array[j].playerName, array[j + 1].playerName);
                strcpy(array[j + 1].playerName, tmp.playerName);

                tmp.level = array[j].level;
                array[j].level = array[j + 1].level;
                array[j + 1].level = tmp.level;
            }
        }
    }
}

/*
 * Write the scoreboard to a file
 * @param filename The file to write to
 */
void
writeScoreboard(const char* filename) {
    Scoreboard array[10];
    int i;

    readScoreboard(filename, array); // Read the scoreboard from the file

    sortArray(array); // Sort the array

    // if the player's score is higher than the lowest score in the scoreboard
    if (app.score > array[MAX_PLAYER_SCOREBOARD - 1].score) {
        char name[MAX_NAME_LENGTH];
        strcpy(name, app.playerName); // Copy the player's name

        // Insert the player's score in the scoreboard array at the right position
        array[MAX_PLAYER_SCOREBOARD - 1].score = app.score;
        array[MAX_PLAYER_SCOREBOARD - 1].level = app.level;
        strcpy(array[MAX_PLAYER_SCOREBOARD - 1].playerName, app.playerName);
        array[MAX_PLAYER_SCOREBOARD - 1].playerName[strcspn(array[MAX_PLAYER_SCOREBOARD - 1].playerName, "\n")] = 0;

        sortArray(array); // Sort the array
    }

    FILE* fptr = fopen(filename, "w"); // Open the file in write mode

    // If the file is not NULL
    if (fptr) {
        // Write the scoreboard to the file
        for (i = 0; i < MAX_PLAYER_SCOREBOARD; ++i) {
            fprintf(fptr, "%s %d %d\n", array[i].playerName, array[i].score, array[i].level);
        }
    }

    fclose(fptr); // Close the file
}
