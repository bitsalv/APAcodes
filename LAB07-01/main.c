#include <stdio.h>
#include <stdlib.h>
#define N 4

typedef enum {false,true} boolean;
int disp_ripet(int pos, int *dispGemme, int *sol, int n, int k, int prec);
int verifica(int *sol, int*dispGemme, int k);
int verificaComposizione(int *sol, int k);
int verificaDisponibilita(int *sol, int*dispGemme, int k);

int main() {

    char filename[30];
    printf("Inserisci nome file.\n>:");
    scanf("%s",filename);
    int i, s, k, *sol, numGemme[N], dispGemme[N], maxlun, bestlun, numtestset;
    char gemme[N]={'Z','R','T','S'};
    FILE *fp=fopen(filename,"r");
    if(fp==NULL)
        exit(-1);

    fscanf(fp,"%d",&numtestset);
    for (s=0; s<numtestset; s++) {
        printf("Test set #%d\n",s+1);
        maxlun=0;
        for(i=0; i<N; i++){
            fscanf(fp,"%d", &numGemme[i]);
            maxlun+=numGemme[i];
        }
        sol=malloc((maxlun)* sizeof(int));

        for(k=1;k<=maxlun;k++){
            for(i=0;i<N;i++)
                dispGemme[i]=numGemme[i];
            if(disp_ripet(0,dispGemme,sol,N,k,-1)){
                bestlun=k;
            }
        }
        printf("Una soluzione a lunghezza massima %d, e': ",bestlun);
        for(i=0;i<bestlun;i++)
            printf("%c", gemme[sol[i]]);
        printf("\n");
        free(sol);
    }
    fclose(fp);

    return 0;


}

int disp_ripet(int pos, int *dispGemme, int *sol, int n, int k, int prec) {
    int i;
    if (pos >= k) {
           return 1;
    }

        for (i = 0; i < n; i++) {
                if (dispGemme[i] > 0) {
                    dispGemme[i]--;
                    if(i!=0) {
                        if (((sol[i - 1] == 0) || (sol[i - 1] == 2)) && (sol[i] != 0) && (sol[i] != 1))
                            break;
                        if (((sol[i - 1] == 3) || (sol[i - 1] == 1)) && (sol[i] != 3) && (sol[i] != 2))
                            break;
                    }
                        sol[pos] = i;
                        if (disp_ripet(pos + 1, dispGemme, sol, n, k, pos))
                            return 1;
                        dispGemme[i]++;
                }
            }
    return 0;
}

/*
int verifica(int *sol, int*dispGemme, int k){
    return (verificaDisponibilita(sol,dispGemme,k) * verificaComposizione(sol,k));
}

int verificaDisponibilita(int *sol, int*dispGemme, int k){
    int i, usGemme[N]={0};

    for(i=0;i<k;i++) {
        usGemme[sol[i]]++;
        if (usGemme[sol[i]] > dispGemme[sol[i]])
            return 0;
    }
    return 1;
}

int verificaComposizione(int *sol, int k){

    for(int i=1;i<k;i++){
            if(((sol[i-1]==0) || (sol[i-1]==2)) && (sol[i]!=0) && (sol[i]!=1))
                return 0;
            if(((sol[i-1]==3) || (sol[i-1]==1)) && (sol[i]!=3) && (sol[i]!=2))
                return 0;
        }
    return 1;
}
 */