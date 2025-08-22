#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "content.h"

#define CONTENT_FILE "data/contents.txt"

void contentMenu(char *username){
    int choice;
    while (1) {
        printf("\n------ CONTENT MENU ------\n");
        printf("1. Add Content\n");
        printf("2. List Content\n");
        printf("3. Edit Content\n");
        printf("4. Delete Content\n");
        printf("5. Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch(choice){
            case 1: addContent(username);break;
            case 2: listContent();break;
            case 3: editContent();break;
            case 4: deleteContent();break;
            case 5: return;
            default: printf("Invalid choice\n");
        }
    }
}
void addContent(char *username){
    FILE *fp = fopen(CONTENT_FILE,"a+");
    int id = 1;
    char title[100],body[500],slug[120];
    if (!fp) {
        printf("Error: cannot open contents file.\n");
        return;
    }
    char line[700];
    while (fgets(line, sizeof(line), fp)) id++;
    printf("Title: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = 0;

    printf("Body: ");
    fgets(body, sizeof(body), stdin);
    body[strcspn(body, "\n")] = 0;

    generateSlug(title, slug);

    fprintf(fp, "%d|%s|%s|draft|%s\n", id, title, body, slug);
    fclose(fp);
    printf("Content added (ID: %d)\n", id);
}

void listContent() {
    FILE *fp = fopen(CONTENT_FILE, "r");
    if (!fp) {
        printf("No content found.\n");
        return;
    }

    char id[10], title[100], body[500], status[20], slug[120];
    printf("\n--- Content List ---\n");
    while (fscanf(fp, "%9[^|]|%99[^|]|%499[^|]|%19[^|]|%119[^\n]\n",
                  id, title, body, status, slug) == 5) {
        printf("\nID: %s\n", id);
        printf("Title: %s\n", title);
        printf("Body: %s\n", body);
        printf("Status: %s\n", status);
        printf("Slug: %s\n", slug);
        printf("-----------------------------\n");
    }
    fclose(fp);
}


void editContent(){
    int id, found = 0;
    printf("Enter content ID to edit: ");
    scanf("%d", &id);
    getchar();

    FILE *fp = fopen(CONTENT_FILE,"r");
    FILE *temp = fopen("data/temp.txt", "w");
    if (!fp || !temp) {
        printf("Error: cannot edit.\n");
        return;
    }
    char cid[10], title[100], body[500], status[20], slug[120];
    while (fscanf(fp, "%9[^|]|%99[^|]|%499[^|]|%19[^|]|%119[^\n]\n", cid, title, body, status, slug) == 5) {
        if (atoi(cid) == id) {
            found = 1;
            printf("Editing [%s] %s\n", cid, title);
            printf("New Title: ");
            fgets(title, sizeof(title), stdin);
            title[strcspn(title, "\n")] = 0;
            printf("New Body: ");
            fgets(body, sizeof(body), stdin);
            body[strcspn(body, "\n")] = 0;
            generateSlug(title, slug);
            fprintf(temp, "%s|%s|%s|draft|%s\n", cid, title, body, slug);
        } 
        else {
            fprintf(temp, "%s|%s|%s|%s|%s\n", cid, title, body, status, slug);
        }
    }
    fclose(fp);
    fclose(temp);
    remove(CONTENT_FILE);
    rename("data/temp.txt", CONTENT_FILE);

    if (found) printf("Content updated!\n");
    else printf("Content ID not found.\n");
}
void deleteContent() {
    int id, found = 0;
    printf("Enter content ID to delete: ");
    scanf("%d", &id);
    getchar();

    FILE *fp = fopen(CONTENT_FILE, "r");
    FILE *temp = fopen("data/temp.txt", "w");
    if (!fp || !temp) {
        printf("Error: cannot delete.\n");
        return;
    }

    char cid[10], title[100], body[500], status[20], slug[120];
    while (fscanf(fp, "%9[^|]|%99[^|]|%499[^|]|%19[^|]|%119[^\n]\n",
                  cid, title, body, status, slug) == 5) {
        if (atoi(cid) == id) {
            found = 1;
            continue; // skip writing (delete)
        } else {
            fprintf(temp, "%s|%s|%s|%s|%s\n", cid, title, body, status, slug);
        }
    }
    fclose(fp);
    fclose(temp);
    remove(CONTENT_FILE);
    rename("data/temp.txt", CONTENT_FILE);

    if (found) printf("Content deleted!\n");
    else printf("Content ID not found.\n");
}

