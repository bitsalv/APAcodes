#include <stdio.h>
#include <stdlib.h>
#include "inventario.h"
#include "personaggi.h"

#define MAXS 50
typedef enum {false,true} boolean;

int main() {
    int in;
    boolean continua=true;

    pInventario tabInv=initInventario();
    pTabPersonaggio tabPG=initTabPersonaggio();

    while(continua) {
        printf("Inserisci:\n-\"0\" per caricare da un file l'elenco dei personaggi\n-\"1\" per caricare da un file l'elenco di oggetti");
        printf("\n-\"2\" per aggiungere un nuovo personaggio\n-\"3\" per eliminare un personaggio");
        printf("\n-\"4\" per aggiungere/rimuovere un oggetto dall'equipaggiamento di un personaggio");
        printf("\n-\"5\" per calcolare le statistiche di un personaggio\n-\"6\" per terminare");
        scanf("%d",&in);
        switch (in){

            case 0:{
                char s[MAXS];
                printf("Inserisci nome file:\n>:");
                scanf("%s",s);
                FILE *fp=fopen(s,"r");
                if(fp==NULL)
                    exit(-1);
                caricamentoPgDaFile(fp,tabPG);
                stampaLista(tabPG);
            } break;

            case 1:{
                char s[MAXS];
                printf("Inserisci nome file:\n>:");
                scanf("%s",s);
                FILE *fp=fopen(s,"r");
                if(fp==NULL)
                    exit(-1);
                caricamentoOggettiDaFile(fp,tabInv);
                stampaInventario(tabInv);
            } break;

            case 2:{
                pPersonaggio PGtmp;
                printf("Inserisci dati nuovo personaggio:\n>:");
                printf("<codice(nella forma PGXXXX)> <nome> <classe> <hp> <mp> <atk> <def> <mag> <spr>");
                Pscanf(PGtmp);
                inserisciInCoda(tabPG,PGtmp);
                printf("Lista pg:\n"); stampaLista(tabPG);
            } break;

            case 3:{
                char s[7];
                printf("Inserisci codice personaggio:\n>:");
                scanf("%s",s);
                cancellaConRicerca(s,tabPG);
                printf("Lista pg:\n"); stampaLista(tabPG);
            } break;

            case 4:{
                int dec=0;
                char s[7];
                char ogg[MAXS];
                printf("Inserisci \"1\" per aggiungere l'oggetto.\nInserisci \"-1\" per rimuovere l'oggetto.");
                scanf("%d",&dec);
                printf("Inserisci codice personaggio:\n>:");
                scanf("%s",s);
                printf("Inserisci nome oggetto:\n>:");
                scanf("%s",ogg);
                modificaEquipaggiamento(tabInv,tabPG,dec,s,ogg);
            } break;

            case 5:{
                calcolaStatistiche(tabPG);
            } break;

            case 6:{
                printf("Fine programma.\n");
                freeAll(tabPG,tabInv);
                continua=false;
            } break;

            default:{
                printf("Errore inserimento valore! Riprova:\n>:");
            }
        }
    }
    return 0;
}