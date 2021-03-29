#include <stdio.h>
#include <stdlib.h>
#define N 4

typedef enum {false,true} boolean;
int disp_ripet(int pos, int val, int *sol, int *numGemme, int * valGemme, int *usGemme, int *ripGemme, int maxlun, int prec, int *bestSol, int *bestval, int *bestlun, int maxrip);
void solve(char *gemme, int *numGemme, int *valGemme, int maxlun, int maxrip);

int main() {

    char filename[30];
    printf("Inserisci nome file.\n>:");
    scanf("%s", filename);
    int i, s, k, *sol, numGemme[N], valGemme[N], dispGemme[N], maxlun, maxrip, bestlun, numtestset;
    char gemme[N] = {'Z', 'R', 'T', 'S'};
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
        exit(-1);

    fscanf(fp, "%d", &numtestset);
    for (s = 0; s < numtestset; s++) {
        printf("Test set #%d\n", s + 1);
        maxlun = 0;
        for (i = 0; i < N; i++) {
            fscanf(fp, "%d", &numGemme[i]);
            maxlun += numGemme[i];
        }

        for (i = 0; i < N; i++) {
            fscanf(fp, "%d", &valGemme[i]);
            printf("%c = %d [%d], ", gemme[i], numGemme[i], valGemme[i]);
        }
        fscanf(fp, "%d", &maxrip);

        printf("TOT = %d {maxrip = %d}\n", maxlun, maxrip);
        solve(gemme, numGemme, valGemme, maxlun, maxrip);

        fclose(fp);

        return 0;


    }
}
int disp_ripet(int pos, int val, int *sol, int *numGemme, int * valGemme, int *usGemme, int *ripGemme, int maxlun, int prec, int *bestSol, int *bestval, int *bestlun, int maxrip) {
        int i,precrip=0;
        if (val > *bestval) {
            if (usGemme[0] <= usGemme[3]) {
                *bestval=val;
                *bestlun=pos;
                for(i=0;i<N;i++)
                    bestSol[i]=sol[i];
            }
        }
        if(pos>=maxlun)
            return 1;

        for (i = 0; i < N; i++) {
            if (numGemme[i]-usGemme[i]> 0) { //ancora gemme disponibili

                if (i != 0) {
                    if (((sol[i - 1] == 0) || (sol[i - 1] == 2)) && (sol[i] != 0) && (sol[i] != 1))
                        break;
                    if (((sol[i - 1] == 3) || (sol[i - 1] == 1)) && (sol[i] != 3) && (sol[i] != 2))
                        break;
                }
                if(prec==i){
                    if(ripGemme[i]+1>maxrip)
                        continue;
                }

                if(prec==-1)
                    ripGemme[i]=1;
                else
                    if(prec==i)
                        ripGemme[i]++;
                    else{
                        ripGemme[i]=1;
                        precrip=ripGemme[prec];
                        ripGemme[prec]=0;
                    }
                    usGemme[i]++;
                    sol[pos] = i;
                if (disp_ripet(pos+1, val+ valGemme[i], sol, numGemme,  valGemme, usGemme, ripGemme, maxlun, i, bestSol, bestval, bestlun, maxrip))
                    return 1;

                usGemme[i]--;
                if (prec == -1)
                    ripGemme[i] = 0;
                else
                if (prec == i)
                    ripGemme[i]--;
                else {
                    ripGemme[i] = 0;
                    ripGemme[prec] = precrip;
            }
        }
        return 0;
    }
}


void solve(char *gemme, int *numGemme, int *valGemme, int maxlun, int maxrip){
    int i, bestval=-1, bestlun=-1, *sol=calloc(maxlun, sizeof(int)), *bestSol=calloc(maxlun, sizeof(int)), *usGemme=calloc(maxlun, sizeof(int)),*ripGemme=calloc(maxlun, sizeof(int));
    disp_ripet(0, 0, sol, numGemme,  valGemme, usGemme, ripGemme, maxlun, -1, bestSol, &bestval, &bestlun, maxrip);
    printf("Soluzione ottima di valore %d usando %d gemma/e\n", bestval, bestlun);
    printf("Composizione collana: ");

    for (i=0; i<bestlun; i++)
        printf("%c", gemme[bestSol[i]]);
    printf("\n");
    free(usGemme);
    free(ripGemme);
    free(bestSol);
    free(sol);
    return;
}
