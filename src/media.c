#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "media.h"

#define MEDIA_FILE "data/media.txt"

void mediaMenu(char *username) {
    int choice;
    while (1) {
        printf("\n===== MEDIA MENU =====\n");
        printf("1. Add Media Reference\n");
        printf("2. List Media\n");
        printf("3. Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addMedia(); break;
            case 2: listMedia(); break;
            case 3: return;
            default: printf("Invalid choice.\n");
        }
    }
}

void addMedia(){
    FILE *fp = fopen(MEDIA_FILE, "a+");
    int id = 1;
    char filename[100];

    if (!fp) {
        printf("Error: cannot open media file.\n");
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), fp)) id++;

    printf("Enter filename: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;

    fprintf(fp, "%d|%s\n", id, filename);
    fclose(fp);
    printf("Media added (ID: %d)\n", id);
}

void listMedia() {
    FILE *fp = fopen(MEDIA_FILE, "r");
    if (!fp) {
        printf("No media found.\n");
        return;
    }
    char id[10], filename[100];
    printf("\n--- Media List ---\n");
    while (fscanf(fp, "%9[^|]|%99[^\n]\n", id, filename) == 2) {
        printf("[%s] %s\n", id, filename);
    }
    fclose(fp);
}
