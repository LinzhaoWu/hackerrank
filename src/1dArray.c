#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    char *s;
    s = malloc(1024 * sizeof(char));
    scanf("%[^\n]", s);
    s = realloc(s, strlen(s) + 1);

    char* delimiters = " ,.";
    char* token = strtok(s, delimiters);
    while (token)
    {
        printf("%s\r\n", token);
        token = strtok(NULL, delimiters);
    }
    
    return 0;
}