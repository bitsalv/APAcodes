//
// Created by salva on 11/02/2020.
//

#include "personaggi.h"
#define MAXS 50

#include <string.h>
#include <stdlib.h>
typedef enum {false,true} boolean;

typedef struct {
    int hp, mp, atk, def, mag, spr;
} stat_s;

typedef struct {
    boolean inUso;
    int nE, maxE;
    inv_t vettEq[8];
} tabEquip_t;

struct pg_t{
    char codice[7], nome[MAXS], classe[MAXS];
    tabEquip_t *equip;
    stat_s stat;
};

typedef struct node_s *link;

struct node_s {
    struct pg_t val;
    link next;
};

struct tabPg_t{
    link headPg;
    link tailPg;
    int nPg;
};

static link NewNode(struct pg_t val, link next){
    link x= (link) malloc(sizeof *x);
    if(x==NULL)
        return NULL;
    x->next=next;
    x->val=val;
    return x;
}

static void stampaPG(struct pg_t PGtmp){
    printf("codice:%s nome:%s classe:%s statistiche: %d %d %d %d %d %d\n",PGtmp.codice,PGtmp.nome,PGtmp.classe,PGtmp.stat.hp,PGtmp.stat.mp,PGtmp.stat.atk,PGtmp.stat.def,PGtmp.stat.mag,PGtmp.stat.spr);
}

void Pscanf(pPersonaggio PGtmp){
    scanf("%s %s %s %d %d %d %d %d %d",PGtmp->codice,PGtmp->nome,PGtmp->classe,&PGtmp->stat.hp,&PGtmp->stat.mp,&PGtmp->stat.atk,&PGtmp->stat.def,&PGtmp->stat.mag,&PGtmp->stat.spr);
}

static link listInsertInTails(pPersonaggio val, link *h, link t){
    link x=*h;
    if(x==NULL || t==NULL) {
        *h = NewNode(*val, NULL);
        return *h;
    }
    return t->next=NewNode(*val,NULL);
}

void inserisciInCoda(pTabPersonaggio tabPG, pPersonaggio PGtmp){
    tabPG->tailPg=listInsertInTails(PGtmp,&tabPG->headPg,tabPG->tailPg);
}

static void FreeNode(link node){
    free(node->val.equip);
    free(node);
}

static void FreeList(link h){
    link x,p;
    for (x=h->next, p=h; x!=NULL; p=x,x=x->next)
        FreeNode(p);
}

static link listDeleteBySearch(char *s,link h, link *t){
    link x,p;
    for(x=h,p=NULL; x!=NULL;p=x,x=x->next){
        if(strcmp(s,x->val.codice)==0){
            if(x==h)
                h=x->next;
            else if(x==*t)
                *t=p;
            else
                p->next=x->next;
            FreeNode(x);
            break;
        }
    }
    return h;
}

void cancellaConRicerca(char *s, pTabPersonaggio tabPG) {


}
void caricamentoPgDaFile(FILE *fp, pTabPersonaggio tabPG){
    struct pg_t PGtmp; tabPG->nPg=0; tabPG->headPg=tabPG->tailPg=NULL; PGtmp.equip=malloc(sizeof(tabEquip_t)); PGtmp.equip->maxE=8; PGtmp.equip->nE=0;
    while(fscanf(fp,"%s %s %s %d %d %d %d %d %d",PGtmp.codice,PGtmp.nome,PGtmp.classe,&PGtmp.stat.hp,&PGtmp.stat.mp,&PGtmp.stat.atk,&PGtmp.stat.def,&PGtmp.stat.mag,&PGtmp.stat.spr)==9){
        tabPG->tailPg=listInsertInTails(&PGtmp, &tabPG->headPg,tabPG->tailPg);
        tabPG->nPg++;
    }
}
void stampaLista(pTabPersonaggio pt){
    link h=pt->headPg;
    link x;
    for(x=h;x!=NULL;x=x->next)
        stampaPG(x->val);
}
void modificaEquipaggiamento(pInventario tabInv, pTabPersonaggio tabPG, int in, char *s, char *eq){
    boolean trovato=false;
    if(in!=1 && in!=-1)
        exit(-1);
    link x;
    for(x=tabPG->headPg;x!=NULL;x=x->next){
        if(strcmp(s,x->val.codice)==0) {
            if(in==1){
                for(int i=0; i<getNInv(tabInv);i++){
                    if(strcmp(eq,getNomeDiI(tabInv,i))==0){
                        if(x->val.equip->nE<x->val.equip->maxE){
                            trovato=true;
                            x->val.equip->vettEq[x->val.equip->nE++]=getVettInvdiI(tabInv,i);
                            break;
                        }
                    }
                }
                if(trovato==false)
                    printf("Oggetto non trovato");
            } else{
                for(int i=0; i<x->val.equip->nE; i++){
                    if(strcmp(eq,x->val.equip->vettEq[i].nome)==0){
                        x->val.equip->nE--;
                        trovato=true;
                        break;
                    }
                }
                if(trovato==false)
                    printf("oggetto non trovato");
            }
        }
    }
}
void calcolaStatistiche(pTabPersonaggio tabPG){
    char s[7];
    printf("Calcolo statistiche personaggio.\nInserisci codice personaggio:\n>:");
    scanf("%s",s);
    link x;


    for(x=tabPG->headPg;x!=NULL;x=x->next){
        if(strcmp(x->val.codice,s)==0){
            printf("Statistiche personaggio %s iniziali: %d %d %d %d %d %d\n",x->val.codice, x->val.stat.hp, x->val.stat.mp,x->val.stat.atk, x->val.stat.def, x->val.stat.mag, x->val.stat.spr);
            for(int i=0;i<x->val.equip->nE;i++) {
                x->val.stat.hp += x->val.equip->vettEq[i].stat.hp;
                x->val.stat.spr += x->val.equip->vettEq[i].stat.spr;
                x->val.stat.def += x->val.equip->vettEq[i].stat.def;
                x->val.stat.atk += x->val.equip->vettEq[i].stat.atk;
                x->val.stat.mag += x->val.equip->vettEq[i].stat.mag;
                x->val.stat.mp += x->val.equip->vettEq[i].stat.mp;
            }
            printf("Statistiche personaggio %s con equipaggiamento: %d %d %d %d %d %d\n",x->val.codice, x->val.stat.hp, x->val.stat.mp,x->val.stat.atk, x->val.stat.def, x->val.stat.mag, x->val.stat.spr);
        }
    }
}
void freeAll(pTabPersonaggio tabPG, pInventario tabInv){
    FreeList(tabPG->headPg);
    free(tabPG->tailPg);
    free(tabPG);
    free(getVettInv(tabInv));
    free(tabInv);
}
pTabPersonaggio initTabPersonaggio(){
    pTabPersonaggio puntatore=malloc(sizeof(struct tabPg_t));
    return puntatore;
}