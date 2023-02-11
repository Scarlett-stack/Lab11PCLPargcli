#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define BUFF 1025
int main(int argc, char *argv[])
{
    // printf("%s",argv[0]);
    char *string = malloc(1025 * sizeof(char));
    FILE *f = fopen("input.txt", "r");
    // long int q=ftell(f);
    // printf("%ld\n",q);
    //  rewind(f);
    while (!feof(f)) //aici e simplu doar verificam fiecare linie din fisier
    {
        fgets(string, strlen(string), f);
        // printf("%s", string);
        if (strstr(string, argv[2]))
            printf("%s", string);
    }
    return 0;

    free(string);
}