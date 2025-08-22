#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"
#include "content.h"
#include "media.h"

void mainMenu(char *username)
{
    int choice;
    while(1){
        printf("\n===== CMS MENU =====\n");
        printf("1. Manage Content\n");
        printf("2. Manage Media\n");
        printf("3. Logout\n");
        printf("Enter choice: ");
        scanf("%d",&choice);
        getchar(); // clear newline

        switch(choice){
            case 1: contentMenu(username); break;
            case 2: mediaMenu(username); break;
            case 3: return;
            default: printf("Invalid choice\n");
        }
    }


}

int main(){
    int choice;
    char username[50];

    while(1){
        printf("\nWelcome to CMS\n");
        printf("1. Login\n");
        printf("2. Signup\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch(choice){
            case 1: 
                if(login(username)){
                    mainMenu(username);
                }
                break;

            case 2:
                signup();
                break;
            case 3:
                printf("Exiting CMS..\n");
                exit(0);
            default: printf("Invalid choice\n");

        }
    }
}