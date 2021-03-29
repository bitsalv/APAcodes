#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXS 50

typedef enum {false,true} boolean;

typedef struct {
    int hp, mp, atk, def, mag, spr;
} stat_t;

typedef struct {
    char nome[MAXS], tipo[MAXS];
    stat_t stat;
} inv_t;

typedef struct {
    inv_t *vettInv;
    int nInv, maxInv;
}tabInv_t;

typedef struct {
    boolean inUso;
    int nE, maxE;
    inv_t vettEq[8];
} tabEquip_t;

typedef struct {
   char codice[7], nome[MAXS], classe[MAXS];
   tabEquip_t *equip;
   stat_t stat;
}pg_t;

typedef struct node_s *link; //ok

struct node_s {
    pg_t val;
    link next;
}; //ok

typedef struct {
  link headPg;
  link tailPg;
  int nPg;
} tabPg_t; //ok

link NewNode(pg_t val, link next); //interno
link listInsertInTails(pg_t val, link *h, link t); //ok
link listDeleteBySearch(char *s,link h, link *t); //ok
void caricamentoPgDaFile(FILE *fp, tabPg_t *tabPG);//ok
void caricamentoOggettiDaFile(FILE *fp, tabInv_t *tabInb); //ok
void stampaLista(link h); //ok
void stampaPG(pg_t PGtmp);//interno
void stampaInventario(tabInv_t *tabInv);//ok
void modificaEquipaggiamento(tabInv_t *tabInv, tabPg_t *tabPG, int in, char *s, char *eq);//ok
void calcolaStatistiche(tabPg_t *tabPG);//ok
void freeAll(tabPg_t *tabPG, tabInv_t *tabInv); //ok

int main() {

    int in;
    boolean continua=true;
    tabPg_t *tabPG=malloc(sizeof(tabPg_t));
    tabInv_t *tabInv=malloc(sizeof(tabInv_t));

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
                stampaLista(tabPG->headPg);
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
                pg_t PGtmp;
                printf("Inserisci dati nuovo personaggio:\n>:");
                printf("<codice(nella forma PGXXXX)> <nome> <classe> <hp> <mp> <atk> <def> <mag> <spr>");
                scanf("%s %s %s %d %d %d %d %d %d",PGtmp.codice,PGtmp.nome,PGtmp.classe,&PGtmp.stat.hp,&PGtmp.stat.mp,&PGtmp.stat.atk,&PGtmp.stat.def,&PGtmp.stat.mag,&PGtmp.stat.spr);
                tabPG->tailPg=listInsertInTails(PGtmp,&tabPG->headPg,tabPG->tailPg);
                printf("Lista pg:\n"); stampaLista(tabPG->headPg);
                } break;

            case 3:{
                char s[7];
                printf("Inserisci codice personaggio:\n>:");
                scanf("%s",s);
                tabPG->headPg=listDeleteBySearch(s,tabPG->headPg,&tabPG->tailPg);
                printf("Lista pg:\n"); stampaLista(tabPG->headPg);
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

void stampaPG(pg_t PGtmp){
    printf("codice:%s nome:%s classe:%s statistiche: %d %d %d %d %d %d\n",PGtmp.codice,PGtmp.nome,PGtmp.classe,PGtmp.stat.hp,PGtmp.stat.mp,PGtmp.stat.atk,PGtmp.stat.def,PGtmp.stat.mag,PGtmp.stat.spr);
}

void stampaLista(link h){
    link x;
    for(x=h;x!=NULL;x=x->next)
        stampaPG(x->val);
}

void stampaInventario(tabInv_t *tabInv){
    for (int i = 0; i <tabInv->nInv ; i++) {
        printf("nome: %s tipologia: %s statistiche: %d %d %d %d %d %d\n", tabInv->vettInv[i].nome,
                tabInv->vettInv[i].tipo, tabInv->vettInv[i].stat.hp,
                tabInv->vettInv[i].stat.mp, tabInv->vettInv[i].stat.atk,
                tabInv->vettInv[i].stat.def, tabInv->vettInv[i].stat.mag,
                tabInv->vettInv[i].stat.spr);
    }
}

link NewNode(pg_t val, link next){
    link x= (link) malloc(sizeof *x);
    if(x==NULL)
        return NULL;
    x->next=next;
    x->val=val;
    return x;
}

void FreeNode(link node){
    free(node->val.equip);
    free(node);
}

void FreeList(link h){
    link x,p;
    for (x=h->next, p=h; x!=NULL; p=x,x=x->next)
        FreeNode(p);
}

link listInsertInTails(pg_t val, link *h, link t){
    link x=*h;
    if(x==NULL || t==NULL) {
        *h = NewNode(val, NULL);
        return *h;
    }
    return t->next=NewNode(val,NULL);
}

link listDeleteBySearch(char *s,link h,link *t){
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

void caricamentoPgDaFile(FILE *fp, tabPg_t *tabPG){
    pg_t PGtmp; tabPG->nPg=0; tabPG->headPg=tabPG->tailPg=NULL; PGtmp.equip=malloc(sizeof(tabEquip_t)); PGtmp.equip->maxE=8; PGtmp.equip->nE=0;
    while(fscanf(fp,"%s %s %s %d %d %d %d %d %d",PGtmp.codice,PGtmp.nome,PGtmp.classe,&PGtmp.stat.hp,&PGtmp.stat.mp,&PGtmp.stat.atk,&PGtmp.stat.def,&PGtmp.stat.mag,&PGtmp.stat.spr)==9){
        tabPG->tailPg=listInsertInTails(PGtmp, &tabPG->headPg,tabPG->tailPg);
        tabPG->nPg++;
    }
}

void caricamentoOggettiDaFile(FILE *fp, tabInv_t *tabInv){
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

void modificaEquipaggiamento(tabInv_t *tabInv, tabPg_t *tabPG, int in, char *s, char *equ){
    boolean trovato=false;
    if(in!=1 && in!=-1)
        exit(-1);
    link x;
    for(x=tabPG->headPg;x!=NULL;x=x->next){
        if(strcmp(s,x->val.codice)==0) {
            if(in==1){
                for(int i=0; i<tabInv->nInv;i++){
                    if(strcmp(equ,tabInv->vettInv[i].nome)==0){
                        if(x->val.equip->nE<x->val.equip->maxE){
                            trovato=true;
                            x->val.equip->vettEq[x->val.equip->nE++]=tabInv->vettInv[i];
                            break;
                        }
                    }
                }
                if(trovato==false)
                    printf("Oggetto non trovato");
            } else{
                for(int i=0; i<x->val.equip->nE; i++){
                    if(strcmp(equ,x->val.equip->vettEq[i].nome)==0){
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

void calcolaStatistiche(tabPg_t *tabPG){
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

void freeAll(tabPg_t *tabPG, tabInv_t *tabInv){
    FreeList(tabPG->headPg);
    free(tabPG->tailPg);
    free(tabPG);
    free(tabInv->vettInv);
    free(tabInv);
}