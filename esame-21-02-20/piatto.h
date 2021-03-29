//
// Created by salva on 24/02/2020.
//

#ifndef ESAME_21_02_12_PIATTO_H
#define ESAME_21_02_12_PIATTO_H
#include <stdio.h>


typedef struct piatto_s * PIATTO;
int caricaPiatti(PIATTO *p, FILE *fp);
void piattoPrint(PIATTO p);
float tornaPrezzo(PIATTO p);
#endif //ESAME_21_02_12_PIATTO_H
