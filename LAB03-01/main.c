#include <stdio.h>
#include <stdlib.h>

#define MAXM 51
#define NOMEFILE "mat.txt"


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

boolean leggiMatrice(int m[][MAXM],int *nr, int *nc);
void stampaRisultato(int x, int y, int b, int h);
boolean riconosciRegione(int m[][MAXM], int nr, int nc, int ri, int co, int *b, int *h);



int main() {
    int matrice[MAXM][MAXM];
    int nr, nc, r=0, c=0;
    int b, h;
    boolean risultatoLettura=leggiMatrice(matrice,&nr,&nc);

    for (int i = 0; i <=nr ; ++i) {
        for (int j = 0; j <=nc; ++j) {
            printf("%d", matrice[i][j]);
        }
        printf("\n");
    }

    if(!risultatoLettura)
        exit(-1);

    if(riconosciRegione(matrice,nr,nc,r,c,&b,&h)){
        stampaRisultato(r,c,b,h);
    }

    return 0;
}

boolean leggiMatrice(int m[][MAXM], int *nr, int *nc){
    FILE *fp;
    boolean risultato;
    fp=fopen(NOMEFILE,"r");
    if(fp==NULL)
        risultato=FALSE;

    fscanf(fp,"%d%d", nr, nc);


    //cornice di 0
    for (int i = 0; i <MAXM ; i++) {
        for (int j = 0; j <MAXM; j++) {
            m[i][j]=0;
        }
    }


    for (int i = 1; i <*nr+1 ; ++i)
        for (int j = 1; j <*nc+1; ++j)
            fscanf(fp,"%d", &m[i][j]);

    risultato=TRUE;
    fclose(fp);

    return risultato;
}

boolean riconosciRegione(int m[][MAXM], int nr, int nc, int ri, int co, int *B, int *H){
    str_rettangolo r;
    boolean trovato=TRUE;
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
                trovato=FALSE;
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

    B=&r.base; H=&r.altezza; ri=r.x; co=r.y;

    return trovato;

}

void stampaRisultato(int x, int y, int b, int h){
    fprintf(stdout,"Regione trovata: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d",x-1,y-1,b,h,b*h);
    fprintf(stdout,"\n");
}




