#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *s = "mama";
    int i = 0;
    char *word = malloc(1);
    while (strncmp(s + i, "\n", 1) != 0) {
        word = realloc(word, i + 1);
        memcpy(word + i, s + i, 1);
        i++;
    }
    printf("%s", word);
    return 0;
}