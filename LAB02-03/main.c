#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXSEQ 20
#define MAXLSEQ 5
#define MAXR 201
#define  MAXP 26
#define SEQUENZE "sequenze.txt"
#define TESTO "testo.txt"

typedef enum {FALSE,TRUE} boolean;

boolean trovaOccorrenze(FILE *fp, char *sequenze);
void stampaOutput(char *testo, int indice);

int main(int argc, char *argv[]) {

    char sequenza[MAXLSEQ];
    int nSequenze;
    boolean trovato;
    FILE *fS=fopen(SEQUENZE,"r");
    if(fS==NULL){
        printf("Errore apertura file sequenze!\n");
        exit(-1);
    }

    FILE *fT=fopen(TESTO,"r");
    if(fT==NULL){
        printf("Errore apertura file testo!\n");
        exit(-2);
    }

    int i=0;
    fscanf(fS,"%d",&nSequenze);
    if(nSequenze>MAXSEQ)
        exit(-2);

    while(fscanf(fS,"%s",sequenza)!=EOF && i<nSequenze) {
            trovato=trovaOccorrenze(fT, sequenza);
            if(!trovato)
                printf("Sequenza non trovata!");
            i++;
            rewind(fT);
            printf("\n");
    }

    fclose(fS);
    fclose(fT);
    return 0;
}

void stampaOutput(char *porzioneTesto, int indice){
    printf("\"%s\" (parola in posizione %d)", porzioneTesto, indice);
}




void toLowerS(char *s){
    int i=0;
    while (s[i]!='\0'){
        s[i]=tolower(s[i]);
        i++;
        }

}

boolean trovaOccorrenze(FILE *fp, char *sequenza){

    int i=0;
    char parola[MAXP];
    char tmp[MAXP];
    char *pParola;
    char riga[MAXR];
    int contatore=0;
    boolean trovato=FALSE;
    printf("\nLa sequenza: \"%s\" e' contenuta in:", sequenza);

    while(fscanf(fp,"%s",riga)!=EOF){
        pParola=riga;
        while(sscanf(pParola,"%s%n",parola,&i)==1){
            strcpy(tmp,parola);
            toLowerS(tmp);
            toLowerS(sequenza);

            if(strstr(tmp,sequenza)!=NULL) {
                stampaOutput(parola, contatore + 1);
                trovato=TRUE;
            }
            contatore++;
            pParola=pParola+i;
        }
    }

    return trovato;
}



