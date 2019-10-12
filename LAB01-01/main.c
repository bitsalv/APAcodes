#include <stdio.h>
#include <stdlib.h>
#define nMAX 20
#define mMAX 30
#define NOMEFILE "matrice.txt"

typedef enum {FALSE,TRUE} boolean;

typedef struct {
    int esiti[mMAX];
    int posIniziale; //nomeSquadra

} squadra;

typedef struct {
    int nr;
    int nc;
    boolean caricamento;
} esitoCaricaM;



esitoCaricaM caricaMatrice(int m[][mMAX]);
void caricaSquadre(squadra sq[], int m[][mMAX], int nr, int nc);
void cercaCapolista(squadra squadre[],int nr, int nc);

int main() {

    int m[nMAX][mMAX];
    int nr,nc;

    esitoCaricaM CM=caricaMatrice(m);
    if(!CM.caricamento)
        exit(-1);

    nr=CM.nr;
    nc=CM.nc;

    squadra squadre[nr];
    caricaSquadre(squadre,m,nr,nc);
    cercaCapolista(squadre,nr,nc);

    return 0;
}





void caricaSquadre(squadra sq[], int m[][mMAX], int nr, int nc){

    for (int i = 0; i <nr ; ++i) {
        for (int j = 0; j <nc ; ++j) {
            sq[i].posIniziale = i;
            sq[i].esiti[j] = m[i][j];
        }
    }

    //sommo i punti
    for (int k = 0; k <nr ; ++k) {
        for (int l = 0; l <nc-1 ; ++l) {
            sq[k].esiti[l+1]+=sq[k].esiti[l];
        }
    }
}

esitoCaricaM caricaMatrice(int m[][mMAX]){
   FILE *fp=fopen(NOMEFILE,"r");
   esitoCaricaM CM;

   if(fp==NULL){
       CM.caricamento=FALSE;
       return CM;
   }

   fscanf(fp,"%d%d",&CM.nr, &CM.nc);
    for (int i = 0; i <CM.nr ; ++i) {
        for (int j = 0; j <CM.nc ; ++j) {
            fscanf(fp,"%d", &m[i][j]);
        }

    }
    CM.caricamento=TRUE;
    fclose(fp);
    return CM;
}

void cercaCapolista(squadra squadre[],int nr, int nc){

    int max=0;
    squadra capolista;


    for (int i = 0; i <nr ; ++i) {
        for (int j = 0; j <nc ; ++j) {
            if(squadre[j].esiti[i]>max) {
                capolista = squadre[j];
                max=squadre[j].esiti[i];
            }
        }
        fprintf(stdout,"\nLa capolista nella giornata %d e' la squadra %d, con punti: %d\n",i+1,capolista.posIniziale+1,capolista.esiti[i]);
        max=0;
    }

}
