//
// Created by salva on 24/02/2020.
//

#ifndef ESAME_21_02_12_MENU_H
#define ESAME_21_02_12_MENU_H

#include "piatto.h"

typedef struct {
    int *piatti, nP;
    float totPrezzo;
} menu, *pMenu;

int menuCompare(pMenu m1, pMenu m2);
void menuPrint(pMenu m1, PIATTO *piatti);
pMenu ITEMsetNull();

#endif //ESAME_21_02_12_MENU_H
