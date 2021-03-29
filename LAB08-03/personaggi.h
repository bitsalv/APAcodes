//
// Created by salva on 11/02/2020.
//

#ifndef LAB08_03_PERSONAGGI_H
#define LAB08_03_PERSONAGGI_H
#include "inventario.h"

typedef struct tabPg_t *pTabPersonaggio;
typedef struct pg_t *pPersonaggio;


void caricamentoPgDaFile(FILE *fp, pTabPersonaggio tabPG);
void stampaLista(pTabPersonaggio tabPG);
void modificaEquipaggiamento(pInventario tabInv, pTabPersonaggio tabPG, int in, char *s, char *eq);
void calcolaStatistiche(pTabPersonaggio tabPG);
void freeAll(pTabPersonaggio tabPG, pInventario tabInv);
pTabPersonaggio initTabPersonaggio();
void Pscanf(pPersonaggio PGtmp);
void inserisciInCoda(pTabPersonaggio tabPG, pPersonaggio PGtmp);
void cancellaConRicerca(char *s, pTabPersonaggio tabPG);
#endif //LAB08_03_PERSONAGGI_H
