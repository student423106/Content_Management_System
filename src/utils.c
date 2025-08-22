#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

void generateSlug(char *title, char *slug) {
    int i, j = 0;
    for (i = 0; title[i] != '\0'; i++) {
        if (isspace(title[i])) {
            slug[j++] = '-';
        } else if (isalnum(title[i])) {
            slug[j++] = tolower(title[i]);
        }
    }
    slug[j] = '\0';
}
