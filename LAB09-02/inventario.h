//
// Created by salva on 11/02/2020.
//

#ifndef LAB08_03_INVENTARIO_H
#define LAB08_03_INVENTARIO_H
#define MAXS 50
#include <stdio.h>

typedef struct tabInv_t *pInventario;
typedef struct {
    int hp, mp, atk, def, mag, spr;
} stat_t;
typedef struct {
    char nome[MAXS], tipo[MAXS];
    stat_t stat;
} inv_t;
void caricamentoOggettiDaFile(FILE *fp, pInventario tabInb);
void stampaInventario(pInventario tabInv);
pInventario initInventario();
int getNInv(pInventario pI);
char *getNomeDiI(pInventario pI, int i);
inv_t getVettInvdiI(pInventario pI,int i);
inv_t* getVettInv(pInventario pI) ;

#endif //LAB08_03_INVENTARIO_H
