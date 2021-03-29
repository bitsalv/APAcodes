#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NR 255

typedef struct {
    char *proposte[NR];
    int nCanzoni;
} canzoni_proposte;



canzoni_proposte * leggiFILE(FILE *fp,int *np);
int principioMoltiplicazione(int pos, canzoni_proposte *val, int *sol, int nV, int count);
void creaPlaylist(canzoni_proposte *proposte, int nPersone);
void libera(canzoni_proposte *proposte,int nPersone){
    for (int i = 0; i <nPersone ; i++) {
        free(proposte[i].proposte);
    }
    free(proposte);
}

int main() {
    char riga[NR];
    int nPersone;
    canzoni_proposte *proposteSt;
    printf("Inserisci nome file:\n>:");
    scanf("%s",riga);
    FILE *fp=fopen(riga,"r");
    if(fp==NULL)
        exit(-1);
    proposteSt=leggiFILE(fp,&nPersone);
    creaPlaylist(proposteSt,nPersone);
    libera(proposteSt,nPersone);
    fclose(fp);
    return 0;
}

canzoni_proposte * leggiFILE(FILE *fp, int *nP){
    int nPersone;
    char riga[NR];

    fscanf(fp,"%d",&nPersone);
    canzoni_proposte *proposteSt=(canzoni_proposte *) malloc(nPersone* sizeof(canzoni_proposte));

    for(int i=0; i<nPersone; i++) {
        fscanf(fp, "%d", &proposteSt[i].nCanzoni);
        for (int j = 0; j < proposteSt[i].nCanzoni; j++) {
            fscanf(fp, "%s", riga);
            proposteSt[i].proposte[j] = strdup(riga);
        }
    }

    for (int k = 0; k <nPersone ; ++k) {
        for (int i = 0; i < proposteSt[k].nCanzoni; ++i) {
            printf("%s\n",proposteSt[k].proposte[i]);
        }
        printf("\n\n");
    }

    *nP=nPersone;
    return proposteSt;
}

int principioMoltiplicazione(int pos, canzoni_proposte *val, int *sol, int nV, int count){
    int i;
    if(pos>=nV){
        printf("Playlist #%d\n",count+1);
        for(i=0;i<pos;i++)
            printf("%s ", val[i].proposte[sol[i]]);
        printf("\n");
        return count+1;
    }
    for(i=0;i<val[pos].nCanzoni;i++){
        sol[pos]=i;
        count=principioMoltiplicazione(pos+1,val,sol,nV,count);
    }
    return count;
}

void creaPlaylist(canzoni_proposte *proposte, int nPersone){

    int *sol;
    sol=(int *) calloc(nPersone,sizeof(int));
    principioMoltiplicazione(0,proposte,sol,nPersone,0);
    free(sol);
}

