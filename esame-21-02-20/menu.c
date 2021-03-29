//
// Created by salva on 24/02/2020.
//
#include <stdlib.h>
#include "menu.h"
#include <stdio.h>
#include <limits.h>
#include "piatto.h"

int menuCompare(pMenu m1, pMenu m2){
    int i;
    if(m1->totPrezzo<m2->totPrezzo)
        return 1;
    if(m1->totPrezzo>m2->totPrezzo)
        return -1;
    if(m1->totPrezzo==m2->totPrezzo){
        for (i = 0; i < m1->nP; i++) {
            if(m1->piatti[i]>m2->piatti[i])
                return -1;
            else
                return 1;
        }
    }
    return 0;
}

void menuPrint(pMenu m1, PIATTO *piatti){
    printf("Menu");
    for (int i = 0; i < m1->nP; i++)
        piattoPrint(piatti[m1->piatti[i]]);
}

//serve in BST.c
pMenu ITEMsetNull(){
    pMenu m= malloc(sizeof (pMenu));
    m->totPrezzo=INT_MAX;
    m->piatti=NULL;
    m->nP=-1;
    return m;
}