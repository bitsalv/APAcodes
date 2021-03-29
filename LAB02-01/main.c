#include <stdio.h>
#include <stdlib.h>

#define MAXM 51
#define NOMEFILE "matrice.txt"


typedef enum {FALSE,TRUE} boolean;
typedef enum {base,altezza,area} tipo;

typedef struct {
    int nrighe;
    int ncolonne;
    boolean letto;
} rix;

typedef struct {
    int base;
    int altezza;
    int area;
    int x;
    int y;
}str_rettangolo;

rix leggiMatrice(int m[][MAXM]);
void stampaRisultato(char s[],str_rettangolo rettangolo);
void trovaRettangoli(int m[][MAXM], int nr, int nc);



int main() {
    int matrice[MAXM][MAXM];
    rix risultatoLettura=leggiMatrice(matrice);

    for (int i = 0; i <=risultatoLettura.nrighe ; ++i) {
        for (int j = 0; j <=risultatoLettura.ncolonne ; ++j) {
            printf("%d", matrice[i][j]);
        }
        printf("\n");
    }

    if(!risultatoLettura.letto)
        exit(-1);

    trovaRettangoli(matrice,risultatoLettura.nrighe,risultatoLettura.ncolonne);

    return 0;
}

rix leggiMatrice(int m[][MAXM]){
    FILE *fp;
    rix risultato;
    fp=fopen(NOMEFILE,"r");
    if(fp==NULL)
        risultato.letto=FALSE;

    fscanf(fp,"%d%d", &risultato.nrighe, &risultato.ncolonne);


    //cornice di 0
    for (int i = 0; i <MAXM ; i++) {
        for (int j = 0; j <MAXM; j++) {
            m[i][j]=0;
        }
    }


    for (int i = 1; i <risultato.nrighe+1 ; ++i)
        for (int j = 1; j <risultato.ncolonne+1; ++j)
            fscanf(fp,"%d", &m[i][j]);

        risultato.letto=TRUE;
        fclose(fp);

    return risultato;
}

void trovaRettangoli(int m[][MAXM], int nr, int nc){
    str_rettangolo r;
    r.altezza=r.base=0;
    int b=0,h=0;
    str_rettangolo maxBase, maxAltezza, maxArea;
    maxBase.x=maxBase.y=maxAltezza.x=maxAltezza.y=maxArea.x=maxArea.y=-1;


    int tmp=0;

    for (int i = 1; i <=nr ; i++) {
        for (int j = 1; j <=nc ; j++) {

            if (m[i][j] != 1 || (i>0 && (m[i-1][j] == 1)) || (j>0 && (m[i][j-1] == 1))) {
                r.altezza=0;
                r.base=0;
                r.area=0;
                r.x=r.y=-1;
            } else {
                r.x=i;
                r.y=j;

                tmp=j;
                while(j<=nc && (m[i][j])==1 )
                    j++;
                b=j-tmp;
                j=tmp;

                tmp=i;
                while(i<=nr && (m[i][j])==1)
                    i++;
                h=i-tmp;
                i=tmp;

                r.base=b;
                r.altezza=h;
                r.area=r.base*r.altezza;
            }

            if(maxBase.x==-1 || maxBase.base<r.base) maxBase=r;
            if(maxArea.x==-1 || (maxArea.base*maxArea.altezza)<r.area) maxArea=r;
            if(maxAltezza.x==-1 || maxAltezza.altezza<r.altezza) maxAltezza=r;

        }

    }

    stampaRisultato("Base",maxBase);
    stampaRisultato("Area",maxArea);
    stampaRisultato("Altezza",maxAltezza);

}

void stampaRisultato(char s[],str_rettangolo rettangolo){
    fprintf(stdout,"Max %s: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d",s,rettangolo.x-1,rettangolo.y-1,rettangolo.base,rettangolo.altezza,rettangolo.area);
    fprintf(stdout,"\n");
}




