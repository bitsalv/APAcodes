#include <stdio.h>
#include <string.h>
#define MAXP 50
#define MAXD 30
#define MAXRIGA 201
#define FIN "sorgente.txt"
#define FOUT "ricodificato.txt"
#define FDIZ "dizionario.txt"

typedef enum {FALSE,TRUE} boolean;
typedef struct{
    char par[MAXP];
    char cod[MAXP];
} entry;

int caricaDiz(entry diz[], char nomeFileDizionario[]);
boolean confronta(char riga[],int i, char parola[], int l);
void codifica(char riga[],entry dizionario[],int nd,FILE *destinazione);
//void stampa(FILE *fp);

int main(void) {

    FILE *fin;
    FILE *fout;
    entry dizionario[MAXD];
    int nD;
    char riga[MAXRIGA];

    fin=fopen(FIN,"r");
    fout=fopen(FOUT,"w");

    nD=caricaDiz(dizionario,FDIZ);

    if(fin==NULL || nD==0 || fout==NULL){
        fprintf(stderr,"Errore apertura file!");
        return -1;
    }



    while(fgets(riga,MAXRIGA,fin)!=NULL) {
        codifica(riga, dizionario, nD, fout);
    }

    //fprintf(stdout,"Testo originale:\n");
   // stampa(fin);
   // fprintf(stdout,"Testo codificato:\n");
   //(fout);

    fclose(fin);
    fclose(fout);



    return 0;
}

int caricaDiz(entry diz[], char nomeFileDizionario[]){

    FILE *fpD =fopen(nomeFileDizionario,"r");
    if(fpD==NULL) return 0;

    int nd;
    fscanf(fpD,"%d", &nd);
    for (int i = 0; i <nd ; ++i) {
        fscanf(fpD,"%s %s", diz[i].cod, diz[i].par);
    }
    fclose(fpD);
    return nd;
}




boolean confronta(char riga[], int i ,char parola[], int l){
    for (int j = 0; j <l ; ++j) {
        if(riga[i+j]!=parola[j])
            return FALSE;
    }
    return TRUE;
}

void codifica(char riga[],entry dizionario[],int nd,FILE *destinazione){

    boolean trovato;
    int lunghezza, i, j;
    int l=strlen(riga);
    for (i=0; i<l; i++) {
        trovato=FALSE;
        for (j = 0; j <nd ; j++) {
            lunghezza=strlen(dizionario[j].par);
            if(confronta(riga,i,dizionario[j].par,lunghezza)){
                trovato=TRUE;
                break;
            }
        }
        if(trovato){
            fprintf(destinazione,"%s", dizionario[j].cod);
            i+=(lunghezza-1);
        } else{
            fprintf(destinazione,"%c",riga[i]);
        }
    }
}
/*
void stampa(FILE *fp){
    const int maxRiga=200+1;
    char riga[maxRiga];

    while(fgets(riga,MAXRIGA,fp)!=NULL) {
        fprintf(stdout,"%s", riga);
    }
}
 */
