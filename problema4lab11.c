#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFMAX 1009
struct cod //folosim o structura pentru a retine tabela de codare mai eficient
{
    char s;
    char c;
};
//desi era usor de observat ca fiecare caracter se inclocuieste cu +1 in ASCII dar totusi voi respecta enuntul 
void transf(char **a, struct cod v[], int star, int linii)
{
    // for (int i=0; i<star; i++)
    //  printf("%c %c\n",v[i].c, v[i].s);
    for (int i = 0; i < linii; i++) //luam fiecare linie in parte
    {
        for (int j = 0; j < strlen(a[i]); j++) //acum si pe coloane deci fiecare caracter in parte
        {
            if (a[i][j] >= 65 && a[i][j] <= 90) //A-Z
            {
                a[i][j] += 32; //A-Z -> a-z
                for (int k = 0; k < star; k++) //ne aflam in tabela
                {
                    if (a[i][j] == v[k].c) //am gasit corespondenta 
                    {
                        a[i][j] = v[k].s; //deci codam caracterul conf tabelei
                        break;
                    }
                }
                a[i][j] -= 32;//a-z -> A-Z
                //  printf("*%c ", a[i][j]);
            }
            else
            {
                if (a[i][j] >= 97 && a[i][j] <= 122) //a-z
                {
                    for (int k = 0; k < star; k++)
                    {
                        if (a[i][j] == v[k].c)
                        {
                            a[i][j] = v[k].s;
                            break;
                        }
                    }
                    // printf("%c ", a[i][j]);
                }
            }
        }
    }
}
int main(int argc, char *argv[])
{
    FILE *f = fopen(argv[1], "r");
    FILE *g = fopen(argv[2], "r");
    FILE *h = fopen(argv[3], "w");
    char s[255];
    char c; //var cu care det nr de linii din fisierul cu textul cerintei
    int linii = 1;
    struct cod d[2100];
    int star = 0;
    while ((c = fgetc(g)) != EOF) //eficient sa stim liniile pentru matrice inainte de a o declara
    {
        if (c == '\n')
            linii++;
    }
    //acum file position indicator (fpi) este la finalul fisierului (-1 sau SEEK_END)
    //pentru a folosi acelasi fisier din nou se repozitioneaza fpi
    rewind(g);
    //functie smechera, mai legal ar fi fost cu fseek(f,0,SEEK_SET)
    // char matrice[linii+1][255];
    char **matrice = malloc((linii + 1) * sizeof(char *));
    for (int i = 0; i <= linii; i++)
        matrice[i] = malloc(255 * sizeof(char));

    // printf("%d\n",linii);

    while (!feof(f))
    {
        fscanf(f, "%c %c\n", &d[star].c, &d[star].s);

        // printf("%c %c\n", d[i].c,d[i].s);
        star++;//aflam si cate elemente sunt in d
    }
    fclose(f); 
    int l = 0; //var pt linii
    while (!feof(g))
    {
        fgets(s, 255, g);
        // printf("**%s",s);
        strcpy(matrice[l], s); //e mai usor de lucrat cu o matrice de stringuri
        // printf("%s", matrice[l]);
        l++;
    }
    int i, j;
    transf(matrice, d, star, linii);
    for (i = 0; i < linii; ++i)
    {
        for (j = 0; j < strlen(matrice[i]); ++j)
            fprintf(h, "%c", matrice[i][j]);
    }
    // printf("\n");
    for (i = 0; i <= linii; i++)
        free(matrice[i]);
    free(matrice);
    return 0;
}
// Avem o problema la L -- in exemplul vostru l/L ->c/C dar in tabela se duce in m/M