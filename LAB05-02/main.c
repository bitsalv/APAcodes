#include <stdio.h>
#include <stdlib.h>
#define NR 25

typedef struct {
    int nr;
    int nc;
    int **mat;
} matrice_s;

void separa(matrice_s *matrS,int **bianche, int  **nere, int *nB,int *nN); //matrice come una scacchiera
void malloc2dR(FILE *fp, matrice_s *matrS);
void free2D(matrice_s *mS);
void stampa (int *v, int n);

int main() {

    char riga[NR];
    matrice_s mS;
    int nB,nN, *bianche, *nere;
    printf("Inserisci nome file.\n>:");
    scanf("%s",riga);
    FILE *fp=fopen(riga,"r");
    if(fp==NULL)
        exit(-1);

    malloc2dR(fp,&mS);

    for(int i=0; i<mS.nr; i++) {
        for (int j = 0; j < mS.nc; j++)
            printf("%d",mS.mat[i][j]);
        printf("\n");
    }



    separa(&mS,&bianche,&nere,&nB,&nN);

    printf("Pedine bianche: ");
    stampa(bianche,nB);

    printf("\nPedine nere: ");
    stampa(nere,nN);

    free2D(&mS);
    free(bianche);
    free(nere);

    return 0;
}


void malloc2dR(FILE *fp,matrice_s *matS){

    fscanf(fp,"%d%d",&matS->nr,&matS->nc);
    matS->mat= (int **) malloc(matS->nr* sizeof(int *));
    if(matS->mat==NULL)
        exit(-2);

    for(int i=0;i<matS->nr;i++){
        matS->mat[i]=(int *) malloc(matS->nc* sizeof(int));
        if(matS->mat[i]==NULL)
            exit(-3);
        for (int j=0;j<matS->nc;j++)
            fscanf(fp,"%d",&(matS->mat[i][j]));
    }

}

void free2D(matrice_s *mS){
    for (int i=0;i<mS->nr;i++)
        free(mS->mat[i]);
    free(mS->mat);
}

void separa(matrice_s *matrS,int **bianche, int **nere, int *nB, int *nN){
    //matrice come una scacchiera: le caselle bianche e nere si equivalgono con matrice quadrata di indice pari, le caselle nere sono una in meno con indice dispari.
    //assumo matrice sempre quadrata, essendo una scacchiera
    int cntB=0, cntN=0;
    *nB=(matrS->nr*matrS->nc)/2 + (matrS->nr*matrS->nc)%2;
    *nN=(matrS->nr*matrS->nc)/2;


    (*bianche)=(int *) calloc((*nB),sizeof(int));
    (*nere)=(int *) calloc((*nN),sizeof(int));

    for(int i=0; i<matrS->nr; i++)
        for (int j=0; j<matrS->nc; j++) {
            if(i%2==0){ //riga pari
                if(j%2==0) (*bianche)[cntB++]=matrS->mat[i][j]; //colonna pari
                else (*nere)[cntN++]=matrS->mat[i][j];  //colonna dispari
            }
            else { //riga dispari
                if(j%2==0) (*nere)[cntN++]=matrS->mat[i][j];  //colonna pari
                else  (*bianche)[cntB++]=matrS->mat[i][j]; //colonna dispari
            }
        }
}

void stampa(int *v, int n) {

    for(int i=0;i<n;i++)
        printf("%d ", v[i]);
    printf("\n");
}