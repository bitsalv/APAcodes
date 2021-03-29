#include <stdio.h>
#include <stdlib.h>
#define MAXR 40
typedef enum {false,true} boolean;

typedef struct {
    int indice;
    char colore1; int valore1;
    char colore2; int valore2;
    int ruotato;
} tessera;

tessera *leggiTessereDaFile(FILE *fp,int N);
tessera **allocaMatrice(FILE *fp, tessera *tessere,int *mark,int R,int C,int N);
int calcolaPunteggio(tessera **scacchiera, int N, int R, int C);
int score(tessera **board, int R, int C, int nTiles);
void stampaTessera(tessera t, int j, int C);
void wrapper(tessera *tessere, tessera **scacchiera, int *mark, int N, int R, int C);
void risolviScacchiera(int pos, tessera *tessere, tessera **scacchiera, int *mark, int *best_punt, tessera **best_sol, int N, int R, int C);
void freeScacchiera(tessera **scacchiera, int R);


int main() {
    char s[MAXR];
    int N,R,C,*mark;
    FILE *fT, *fM;
    tessera *tessere;

    printf("Inserisci nome file tessere:\n >:");
    scanf("%s",s);

    fT=fopen(s,"r");
    if(fT==NULL){
        fprintf(stderr,"Errore apertura file tessere!");
        exit(-1);
    }

    fscanf(fT,"%d",&N);
    tessere=leggiTessereDaFile(fT,N);

    printf("Inserisci nome file scacchiera:\n>:");
    scanf("%s",s);

    fM=fopen(s,"r");
    if(fM==NULL){
        fprintf(stderr,"Errore apertura file matrice!");
        exit(-3);
    }

    mark=(int *) calloc(N, sizeof(int));
    fscanf(fM,"%d %d",&R,&C);
    tessera **scacchiera=allocaMatrice(fM,tessere,mark,R,C,N);

    wrapper(tessere,scacchiera,mark,N,R,C);

    free(mark);
    free(tessere);
    freeScacchiera(scacchiera,R);
    fclose(fT);
    fclose(fM);
    return 0;
}

tessera *leggiTessereDaFile(FILE *fp, int N){
    tessera *tessere= (tessera *) calloc(N, sizeof(tessera));
    if(tessere==NULL){
        fprintf(stderr,"Errore allocazione array di tessere");
        exit(-2);
    }
    for (int i = 0; i < N; i++) {
        fscanf(fp,"%c %d %c %d\n",&tessere[i].colore1,&tessere[i].valore1,&tessere[i].colore2,&tessere[i].valore2);
        tessere[i].indice=i;
    }
    return tessere;
}

tessera **allocaMatrice(FILE *fM,tessera *tessere,int *mark,int R,int C, int N){
    int i,j,indice,ruotato;
    tessera **scacchiera;

    scacchiera=(tessera **) calloc(R,sizeof(tessera *));
    for(i=0; i<R; i++)
        scacchiera[i]=(tessera *) calloc(C,sizeof(tessera));

    for (i=0; i<R ; i++) {
        for (j = 0; j < C; j++) {
            fscanf(fM, "%d/%d", &indice, &ruotato);
            if (indice>=0 && indice<N) {
                scacchiera[i][j] = tessere[indice];
                scacchiera[i][j].ruotato = ruotato;
                mark[indice] = 1;
            } else if(indice==-1){
                scacchiera[i][j].indice=-1;
            }
        }
    }
    return scacchiera;
}

void freeScacchiera(tessera **scacchiera,int R){
    for (int i = 0; i <R ; i++)
        free(scacchiera[i]);
    free(scacchiera);

}

void stampaTessera(tessera t, int j, int C){
    fprintf(stdout,"colore T1 %c valore T1 %d colore T2 %c valore T2 %d r %s %s", t.colore1, t.valore1,t.colore2, t.valore2, t.ruotato==1? "si":"no", j==(C-1)? "\n":",");
}



int calcolaPunteggio(tessera **scacchiera, int N, int R, int C){
    int somma=0, sommaR=0,sommaC=0,diverso=0,i,j;
    char init='\0';


    for(i=0;i<R;i++){
        scacchiera[i][0].ruotato==0 ? init= scacchiera[i][0].colore1 : scacchiera[i][0].colore2;
        for(j=0; j<C;j++){
            if( scacchiera[i][j].ruotato==0 && scacchiera[i][j].colore1==init)
                somma+=scacchiera[i][j].valore1;
            else if(scacchiera[i][j].ruotato==1 && scacchiera[i][j].colore2==init )
                somma+=scacchiera[i][j].valore2;
            else
                diverso=1;
        }
    }

    if(diverso==0)
        sommaR=somma;

    for(i=0;i<C;i++){
        scacchiera[0][i].ruotato==0 ? init= scacchiera[0][i].colore1 : scacchiera[0][i].colore2;
        for(j=0; j<R;j++){
            if( scacchiera[i][j].ruotato==0 && scacchiera[i][j].colore1==init)
                somma+=scacchiera[i][j].valore1;
            else if(scacchiera[i][j].ruotato==1 && scacchiera[i][j].colore2==init )
                somma+=scacchiera[i][j].valore2;
            else
                diverso=1;
        }
    }

    if(diverso==0)
        sommaC=somma;

    return sommaR+sommaC;
}

int score(tessera **board, int R, int C, int nTiles) {
    int sum = 0, part = 0, i, j;
    char first = '\0';

    for (i=0; i<R; i++) { /* Per tutte le righe (check in orizzontale)  */
        part = 0;
        first = '\0';
        for (j=0; j<C; j++) { /* Per tutte le colonne  */
            if (board[i][j].indice < 0 || board[i][j].indice >= nTiles) /* Consistenza */
                return -1;
            if (j == 0) {
                /* Memorizza il colore della prima cella incontrata come riferimento */
                board[i][j].ruotato==0? first = board[i][j].colore1 : board[i][j].colore2;
                board[i][j].ruotato==0? part = board[i][j].valore1 : board[i][j].valore2;
            } else {
                if ((board[i][j].ruotato==0? board[i][j].colore1 : board[i][j].colore2)==first)
                    /* Se la sequenza di colori non è interrotta, incrementa il parziale */
                    part += board[i][j].ruotato==0? board[i][j].valore1 : board[i][j].valore2;

                else
                    break;
            }
        }
        if (j == C){
            /* Se la sequenza copre l'intera riga, aggiorna il punteggio */
            sum += part;
        }
    }




    for (i=0; i<C; i++) { /* Per tutte le colonne (check in orizzontale)  */
        part = 0;
        first = '\0';
        for (j=0; j<R; j++) { /* Per tutte le righe  */
            if (board[j][i].indice < 0 || board[j][i].indice >= nTiles) /* Consistenza */
                return -1;
            if (j == 0) {
                /* Memorizza il colore della prima cella incontrata come riferimento */
                board[j][i].ruotato==0? first = board[j][i].colore1 : board[j][i].colore2;
                board[j][i].ruotato==0? part = board[j][i].valore1 : board[j][i].valore2;
            } else {
                if ((board[j][i].ruotato==0? board[j][i].colore1 : board[j][i].colore2)==first)
                    part += board[j][i].ruotato==0? board[j][i].valore1 : board[j][i].valore2;                     /* Se la sequenza di colori non è interrotta, incrementa il parziale */
                else
                    break;
            }
        }
        if (j == R){
            /* Se la sequenza copre l'intera colonna, aggiorna il punteggio */
            sum += part;
        }
    }

    return sum;
}

void risolviScacchiera(int pos, tessera *tessere, tessera **scacchiera, int *mark, int *best_punt, tessera **best_sol, int N, int R, int C){
    int i,j,r,c, cur_punt=0;
    if(pos>=(R*C)){ //terminazione
        cur_punt=score(scacchiera,R,C,N);
        if(cur_punt>*best_punt){
            *best_punt=cur_punt;
            for(i=0;i<R;i++)
                for(j=0;j<C;j++)
                    best_sol[i][j]=scacchiera[i][j];
        }
        return;
    }

    r=pos/C;
    c=pos%C;

    if(scacchiera[r][c].indice==-1) {//cella vuota, agisco
        for (i= 0; i < N; i++) {
            if (mark[i] == 0) {
                mark[i] = 1;
                tessere[i].ruotato = 0;
                scacchiera[r][c] = tessere[i];
                risolviScacchiera(pos + 1, tessere, scacchiera, mark, best_punt, best_sol, N, R, C); //ricorro normale
                tessere[i].ruotato = 1;
                scacchiera[r][c] = tessere[i];
                risolviScacchiera(pos + 1, tessere, scacchiera, mark, best_punt, best_sol, N, R, C); //ricorro ruotando
                // backtrack
                scacchiera[r][c].indice = -1;
                mark[i]=0;
            }
        }
    }
    else //cella piena, ricorro sulla successiva
        risolviScacchiera(pos + 1, tessere, scacchiera, mark, best_punt, best_sol, N, R, C);
}

void wrapper(tessera *tessere, tessera **scacchiera, int *mark, int N, int R, int C){
    int i,j,best_punt=-1;
    tessera **best_sol;
    best_sol=(tessera **) calloc(R,sizeof(tessera *));
    for (i = 0; i < R; i++)
        best_sol[i] = (tessera *) calloc(C,sizeof(tessera));


    risolviScacchiera(0,tessere,scacchiera,mark,&best_punt,best_sol,N,R,C);
/*
    for(i=0; i<R; i++) {
        for (j = 0; j < C; j++)
            stampaTessera(scacchiera[i][j],j,C);
        fprintf(stdout,"\n");
    }
*/
    printf ("Soluzione ottima: %d\n", best_punt);
    for (i=0; i<R; i++) {
        for(j=0;j<C;j++)
            printf("%d/%d ", best_sol[i][j].indice, best_sol[i][j].ruotato);
        printf("\n");
    }
    printf("\n");

    for (i=0; i<R ; i++) {
        free(best_sol[i]);
    }
    free(best_sol);
}