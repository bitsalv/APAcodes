#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXR 40
#define MAXED 5
#define MAXND 3

typedef enum {false,true} boolean;

typedef struct {
    char *nome;
    int tipologia, ingresso, uscita, precedenza, finale, difficolta;
    float punteggio;
}elemento;

typedef struct {
    elemento *elementiV;
    int nElementiV;
} elementi_s;

typedef struct {
    int *elementiD;
    int difficolta;
    float punteggio;
    int nE;
} diagonale_s;

typedef struct {
    diagonale_s *diagonaliD;
    int nDiag;
    int maxD;
    int difficolta_tot;
} diagonali_s;

void generaDiagonali(elementi_s *elementi, diagonali_s *diagonali,int DD);
void dispRipetute(elementi_s *elementi, diagonali_s *diagonali, int pos, int *sol, int n, int k, int DD);
int chechDR(elementi_s *elementi, int *sol, int DD, int pos);
void initDiag(diagonali_s *diagonali);
void generaProgramma(elementi_s *elementi, diagonali_s *diagonali, int DP);
void combRipetute(elementi_s *elementi, diagonali_s *diagonali, int DP, int pos, int *sol, int diff, int *bestSol, float *bestVal, int *bestbonus, int *numD, int start);
int checkValido(elementi_s *E, diagonali_s *D, int *prog, int nd, float *val, int *B);

int main() {
    char s[MAXR];
    FILE *f1;
    int nE;
    int DD=1,DP;
    elementi_s el;
    diagonali_s diagonali;
    printf("Inserisci nome file elementi:\n>:");
    scanf("%s",s);
    f1=fopen(s,"r");
    if(f1==NULL)
        exit(-1);
    fscanf(f1,"%d",&nE);

    el.elementiV=(elemento *) malloc(nE* sizeof(elemento));
    el.nElementiV=nE;

    for (int i = 0; i < nE; i++) {
        fscanf(f1,"%s %d %d %d %d %d %f %d",s,&el.elementiV[i].tipologia,&el.elementiV[i].ingresso,&el.elementiV[i].uscita,&el.elementiV[i].precedenza,&el.elementiV[i].finale,&el.elementiV[i].punteggio,&el.elementiV[i].difficolta);
        el.elementiV[i].nome=strdup(s);
    }


    while(DD) {
        printf("Inserisci valore DD (0 per terminare):\n>:");
        scanf("%d",&DD);
        printf("Inserisci valore DP:\n>:");
        scanf("%d",&DP);
        if(DD) {
            initDiag(&diagonali);
            generaDiagonali(&el, &diagonali, DD);
            generaProgramma(&el,&diagonali,DP);
        }
    }

    for (int i = 0; i < nE; i++) {
        free(el.elementiV[i].nome);
    }
    free(el.elementiV);
    return 0;
}

int chechDR(elementi_s *elementi, int *sol, int DD, int pos) {
    int sum = 0;
    for (int i = 0; i < pos; i++) {
        sum += elementi->elementiV[sol[i]].difficolta;
    }
    if (sum > DD)
        return 0;

    for (int i = 1; i < pos; i++){
        if (elementi->elementiV[sol[i]].ingresso != elementi->elementiV[sol[i - 1]].uscita)
            return 0;
    }
    if(elementi->elementiV[sol[0]].ingresso==0)
            return 0;
    return 1;
}

void dispRipetute(elementi_s *elementi, diagonali_s *diagonali, int pos, int *sol, int n, int k, int DD){
    if(pos>0){
        if(elementi->elementiV[sol[pos-1]].tipologia>0){
            if(diagonali->nDiag==diagonali->maxD){
                diagonali->maxD*=2;
                diagonali->diagonaliD=realloc(diagonali->diagonaliD,diagonali->maxD* sizeof(diagonale_s));
                if(diagonali->diagonaliD==NULL)
                    exit(-1);
            }
            diagonali->diagonaliD[diagonali->nDiag].difficolta=elementi->elementiV[sol[pos-1]].difficolta;
            diagonali->diagonaliD[diagonali->nDiag].nE=pos;
            diagonali->diagonaliD[diagonali->nDiag].elementiD=malloc(pos* sizeof(int));
            diagonali->diagonaliD[diagonali->nDiag].punteggio=0.0;
            for (int i = 0; i < pos; i++) {
                diagonali->diagonaliD[diagonali->nDiag].punteggio+=elementi->elementiV[sol[i]].punteggio;
                diagonali->diagonaliD[diagonali->nDiag].elementiD[i]=sol[i];
            }
            diagonali->nDiag++;
        }
    }
    if(pos>=MAXED || elementi->elementiV[sol[pos-1]].finale)
        return;

    for(int i=0; i<n; i++){
        if(chechDR(elementi,sol,DD,pos)) {
            sol[pos] = i;
            dispRipetute(elementi, diagonali, pos + 1, sol, n, k, DD);
        }
    }
}

void generaDiagonali(elementi_s *elementi, diagonali_s *diagonali, int DD){
    int *sol=calloc(MAXED,sizeof(int));
    printf("Generazione diagonali\n");
    dispRipetute(elementi,diagonali,0,sol,elementi->nElementiV,MAXED,DD);
    free(sol);
}

void initDiag(diagonali_s *diagonali){
    diagonali->nDiag=0;
    diagonali->maxD=1;
    diagonali->difficolta_tot=0;
    diagonali->diagonaliD=calloc(1, sizeof(diagonale_s));
}


int checkValido(elementi_s *E, diagonali_s *D, int *prog, int nd, float *val, int *B) {
    int i, j, bonus = -1;
    int fwd = 0, bwd = 0, seq = 0;
    for(i=0;i<nd;i++) {
        int dseq = 0;
        for(j=0;j<D->diagonaliD[prog[i]].nE;j++) {
            if (E->elementiV[D->diagonaliD[prog[i]].elementiD[j]].tipologia == 2) {
                fwd = 1;
                dseq++;
            } else if (E->elementiV[D->diagonaliD[prog[i]].elementiD[j]].tipologia == 1) {
                bwd = 1;
                dseq++;
            } else {
                dseq = 0;
            }
            if (j==(D->diagonaliD[prog[i]].nE-1) && E->elementiV[D->diagonaliD[prog[i]].elementiD[j]].tipologia > 0 && E->elementiV[D->diagonaliD[prog[i]].elementiD[j]].difficolta > 7) {
                if (bonus == -1 || (D->diagonaliD[prog[bonus]].punteggio < D->diagonaliD[prog[i]].punteggio)) bonus = i;
            }
            if (dseq >= 2) seq = 1;
        }
    }
    if (fwd && bwd && seq) {
        for(i=0;i<nd;i++) {
            (*val) += D->diagonaliD[prog[i]].punteggio * ((i==bonus) ? 1.50 : 1.00);
        }
        *B = bonus;
        return 1;
    }
    return 0;
}

void combRipetute(elementi_s *elementi, diagonali_s *diagonali, int DP, int pos, int *sol, int diff, int *bestSol, float *bestVal, int *bestbonus, int *numD, int start){
    float tmpVal=0.0;
    int tmpBonus;
    if(pos>=MAXND){
        if(checkValido(elementi,diagonali,sol,pos,&tmpVal,&tmpBonus)){
            if(tmpVal>*bestVal){
                *numD=pos;
                *bestVal=tmpVal;
                *bestbonus=tmpBonus;
                memcpy(bestSol,sol,pos* sizeof(int));
            }

        }

    }

    for(int i=start; i<diagonali->nDiag; i++){
        if(diagonali->diagonaliD[i].difficolta+diff<=DP) {
            sol[pos] = i;
            combRipetute(elementi, diagonali, DP, pos+1, sol,diff+diagonali->diagonaliD[i].difficolta, bestSol, bestVal, bestbonus, numD, start);
            start++;
        }
    }

}

void generaProgramma(elementi_s *elementi, diagonali_s *diagonali, int DP){
    printf("Generazione programma");
    int i, j, bonus, d, numd = 0, *prog = malloc(MAXND * sizeof(int)), *bestprog = malloc(MAXND * sizeof(int));
    float bestval = -1.0;
    combRipetute(elementi, diagonali, DP, 0, prog, 0, bestprog, &bestval, &bonus, &numd, 0);
    if (numd > 0) {
        printf("TOT = %f\n", bestval);
        for(i=0;i<numd;i++) {
            d = bestprog[i];
            printf("DIAG %d > %.3f %s\n", d, diagonali->diagonaliD[d].punteggio, ((bonus == i) ? "* 1.5 (BONUS)" : ""));
            for(j=0;j<diagonali->diagonaliD[d].nE;j++) printf("%s ", elementi->elementiV[diagonali->diagonaliD[d].elementiD[j]].nome);
            printf("\n");
        }
    }
}

