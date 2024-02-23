#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    char *s;
    s = (char*)malloc(1024 * sizeof(char));
    scanf("%[^\n]", s);
    s = (char*)realloc(s, strlen(s) + 1);

    char arr[10] = {0};
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            arr[s[i] - '0']++;
        }
    }

    for (int i = 0; i < 10; i++) {
        printf("%d ",arr[i]);
    }

    return 0;
}