//
// Created by salva on 11/02/2020.
//

#include "inventario.h"
#define MAXS 50

#include <stdlib.h>


struct tabInv_t {
    inv_t *vettInv;
    int nInv, maxInv;
};

int getNInv(pInventario pI){
    return pI->nInv;
}

char *getNomeDiI(pInventario pI, int i){
    return pI->vettInv[i].nome;
}

inv_t getVettInvdiI(pInventario pI,int i){
    return pI->vettInv[i];
}

inv_t* getVettInv(pInventario pI) {
    return pI->vettInv;
}

pInventario initInventario(){
    pInventario puntatore=malloc(sizeof(struct tabInv_t));
    return puntatore;
}

void caricamentoOggettiDaFile(FILE *fp, pInventario tabInv){
    tabInv->nInv=0;
    int i=0;
    fscanf(fp,"%d",&tabInv->maxInv);
    tabInv->vettInv=malloc(sizeof(inv_t)*tabInv->maxInv);
    for(i=0;i<tabInv->maxInv;i++) {
        fscanf(fp, "%s %s %d %d %d %d %d %d", tabInv->vettInv[i].nome,
               tabInv->vettInv[i].tipo, &tabInv->vettInv[i].stat.hp,
               &tabInv->vettInv[i].stat.mp, &tabInv->vettInv[i].stat.atk,
               &tabInv->vettInv[i].stat.def, &tabInv->vettInv[i].stat.mag,
               &tabInv->vettInv[i].stat.spr);
    }
    tabInv->nInv=i;
}
void stampaInventario(pInventario tabInv){
    for (int i = 0; i <tabInv->nInv ; i++) {
        printf("nome: %s tipologia: %s statistiche: %d %d %d %d %d %d\n", tabInv->vettInv[i].nome,
               tabInv->vettInv[i].tipo, tabInv->vettInv[i].stat.hp,
               tabInv->vettInv[i].stat.mp, tabInv->vettInv[i].stat.atk,
               tabInv->vettInv[i].stat.def, tabInv->vettInv[i].stat.mag,
               tabInv->vettInv[i].stat.spr);
    }
}