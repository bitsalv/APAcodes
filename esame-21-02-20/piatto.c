//
// Created by salva on 24/02/2020.
//

#include "piatto.h"
#include <stdlib.h>
#define NS 100

struct piatto_s{
    char nome[NS],tipo[NS],contenuto[NS];
    float prezzo;
    int ordine;
};

int caricaPiatti(PIATTO *p, FILE *fp){
    int nP, i;
    fscanf(fp,"%d",&nP);
    p=(PIATTO *) malloc(nP* sizeof(PIATTO));
    for (i=0; i<nP;i++) {
        p[i]->ordine=i;
        fscanf(fp,"%s%s%s %f",p[i]->nome,p[i]->tipo,p[i]->contenuto,&p[i]->prezzo);
    }
    return nP;
}

void piattoPrint(PIATTO p){
    printf("%s %s %s %f",p->nome,p->tipo,p->contenuto,p->prezzo);
}

float tornaPrezzo(PIATTO p){
    return p->prezzo;
}