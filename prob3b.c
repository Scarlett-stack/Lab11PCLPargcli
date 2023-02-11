#define _GNU_SOURCE // am folosit directiva asta pt a avea acces la functia strcasestr
#include <stdio.h>  //care e non-standard. Se poate sa nu fie portabila si pe alte editoare
#include <stdlib.h>
#include <string.h>
#define BUFFMAX 1025
int main(int argc, char *argv[])
{
    int *fr = calloc(3, sizeof(int));
    char *string = malloc(1025 * sizeof(char));
    FILE *f = fopen("input.txt", "r");
    int i, c = 0, n = 0;
    // printf("%s",argv[argc-1]);

    for (i = 1; i < argc; i++) //verific ce flag-uri am si le pun intr-un vector 
    {
        if (strcmp(argv[i], "c") == 0)
            fr[0]++;
        else if (strcmp(argv[i], "i") == 0)
            fr[1]++;
        else if (strcmp(argv[i], "n") == 0)
            fr[2]++;
        else
            break;
    }
    if (fr[1] != 0)
    { // adica ignore
        while (!feof(f))
        {
            n++;//aci se tine cont de numarul de linie
            fgets(string, BUFFMAX, f);

            if (strcasestr(string, argv[argc - 1]))
            { // if(fr[0]!=0) //c
                c++; //aci se tine cont de nr total de linii care contin ultimul argument din CLI
                if (fr[2] != 0)
                    printf("[%d]%s", n, string);
                else if (fr[2] == 0)  //if in plus --pentru claritate
                    printf("%s", string);
            }
        }
        if (fr[0] != 0)
            printf("Numar total de linii:%d\n", c);
    }
    else if (fr[1] == 0) //cam acelasi lucru si in cazul in care nu am ignore la case sensitive
    {
        while (!feof(f))
        {
            n++;
            fgets(string, BUFFMAX, f);
            if (strstr(string, argv[argc - 1]))
            {
                c++;
                if (fr[2] != 0)
                    printf("[%d]%s", n, string);
                else if (fr[2] == 0)
                    printf("%s", string);
            }
        }
        if (fr[0] != 0)
            printf("Numar total de linii:%d\n", c);
    }

    return 0;
}