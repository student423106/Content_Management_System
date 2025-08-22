#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"

#define USER_FILE "data/users.txt"

int login(char *username){
    char fileUser[50],filePass[50]; //username and password
    char inputUser[50],inputPass[50];
    FILE *fp = fopen(USER_FILE,"r");

    if(!fp){
        printf("User file not found!\n");
        return 0;
    }
    printf("Username: ");
    scanf("%s", inputUser);
    printf("Password: ");
    scanf("%s", inputPass);

    while (fscanf(fp, "%49[^|]|%49s\n", fileUser, filePass) == 2) {
        if (strcmp(inputUser, fileUser) == 0 && strcmp(inputPass, filePass) == 0) {
            strcpy(username, inputUser);
            fclose(fp);
            printf("Login successful!\n");
            return 1;
        }
    }
    fclose(fp);
    printf("Login failed!\n");
    return 0;

}
void signup(){
    char username[50],password[50];
    FILE *fp = fopen(USER_FILE,"a");
    if(!fp){
        printf("User file not found!\n");
        return;
    }
    printf("Choose username: ");
    scanf("%s", username);
    printf("Choose password: ");
    scanf("%s", password);

    fprintf(fp, "%s|%s\n", username, password);
    fclose(fp);
    printf("Signup successful!\n");
}