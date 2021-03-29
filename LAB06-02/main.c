#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LP 50
#define nomefile "anag1.txt"

typedef struct {
    int giorno,mese,anno;
} data_s;

typedef struct {
    char *via, *citta, *cap;
} indirizzo_s;

typedef struct {
    char *codice, *nome, *cognome;
    data_s data_di_nascita;
    indirizzo_s indirizzo;
} ITEM;

typedef struct node_s *link;

struct node_s{
    ITEM val;
    link next;
};

typedef struct {    link head;
    int N;
}database;

typedef enum {false,true} boolean;

//funzioni per l'item
int DateITEMCompare(data_s d1,data_s d2);
int KeyITEMCompare(char *k1, char *k2);
data_s DateITEMGet(ITEM Item);
char *KeyITEMGet(ITEM *pItem);
void stampaITEM(ITEM *pItem,FILE *fp);

//funzioni per il nodo
link newNode(ITEM val, link next);
void freeNode(link nodep);

//funzioni per la lista
link inserimentoOrdinato(link h, ITEM val);
link ricercaByChiave(link h, char *k);
ITEM cancellazioneByChiave(link *h,char *k);
ITEM cancellazioneByDate(link *h, data_s d1, data_s d2);
void letturaDaFile(database *db, char *nomeFile);


//funzioni per il database
void letturaDaFileIniziale(database *db, char *nomeFile);
database* dbInit();
void dbFree(database *db);


//funzioni wrapper per il menù
void nuovoDaTastiera(database *db);
void nuovoDaFile(database *db);
ITEM* ricercaPerCodice(database *db);
ITEM cancellazionePerCodice(database *db);
void cancellazionePerDate(database *db);
void stampaLista(database *db);


int main() {
    int in;
    database *db;
    db=dbInit();

    //menù
    boolean continua=true;

    while(continua) {
        printf("Inserisci: \n"
               "-\"0\" per inserire un nuovo elemento da tastiera\n"
               "-\"1\" per una nuova acquisizione da file\n"
               "-\"2\" per ricerca con codice\n"
               "-\"3\" per cancellazione (con estrazione) di un elemento con ricerca per codice \n"
               "-\"4\" per cancellazione di tutti gli elementi compresi fra due date \n"
               "-\"5\" per stampare la lista su file o su schermo \n"
               "-\"6\" per terminare\n>:");
        scanf("%d",&in);

            switch (in) {
                case 0: {
                    printf("Inserimento di un nuovo elemento da tastiera.\n");
                    nuovoDaTastiera(db);
                } break;
                case 1: {
                    printf("Inserimento multiplo da nuovo file.\n");
                    nuovoDaFile(db);
                } break;
                case 2: {
                    ITEM *tmp;
                    printf("Ricerca elemento tramite codice.\n");
                    tmp=ricercaPerCodice(db);
                    if(tmp!=NULL)
                        stampaITEM(tmp,stdout);
                    else printf("Elemento non trovato!\n");
                } break;
                case 3: {
                    ITEM tmp;
                    printf("Cancellazione di un elemento tramite ricerca per codice.\n");
                    tmp=cancellazionePerCodice(db);
                    if(strcmp(KeyITEMGet(&tmp),"-1")!=0)
                        stampaITEM(&tmp,stdout);
                    else printf("Elemento non trovato!\n");
                } break;
                case 4: {
                    cancellazionePerDate(db);
                } break;
                case 5:{
                    printf("Stampa della lista di elementi su schermo o su file.\n");
                    stampaLista(db);
                } break;
                case 6:{
                    printf("Programma terminato!\n");
                    continua=false;
                } break;
                default:{
                    printf("Errore inserimento comando! Riprovare!\n");
                }
            }
    }


    dbFree(db);

    return 0;
}

//funzioni per l'item

int DateITEMCompare(data_s d1,data_s d2){
    if (d1.anno != d2.anno)
        return (d1.anno-d2.anno);
    else if (d1.mese != d2.mese)
        return (d1.mese-d2.mese);
    else if (d1.giorno != d2.giorno)
        return (d1.giorno-d2.giorno);
    else return 0;
}
int KeyITEMCompare(char *k1, char *k2){
    return strcmp(k1,k2);
}
char *KeyITEMGet(ITEM *pItem){
    return pItem->codice;
}

data_s DateITEMGet(ITEM Item){
    return Item.data_di_nascita;
}

void stampaITEM(ITEM *pItem,FILE *fp){
    fprintf(fp,"%s %s %s %d/%d/%d %s %s %s",pItem->codice,pItem->nome,pItem->cognome,pItem->data_di_nascita.giorno,pItem->data_di_nascita.mese,pItem->data_di_nascita.anno,pItem->indirizzo.via,pItem->indirizzo.citta,pItem->indirizzo.cap);
}

//funzioni per il nodo

link newNode(ITEM val, link next){
    link x= malloc(sizeof *x);
    if(x==NULL) return NULL;
    x->val=val;
    x->next=next;
    return x;
}

void freeNode(link nodep){
    free(nodep->val.codice); free(nodep->val.nome);free(nodep->val.cognome);
    free(nodep->val.indirizzo.via);free(nodep->val.indirizzo.citta);free(nodep->val.indirizzo.cap);
    free(nodep);
}

//funzioni per la lista
link inserimentoOrdinato(link h, ITEM val){
    link x,p;
    data_s d=DateITEMGet(val);

    //inserimento in testa
    if(h==NULL || DateITEMCompare(DateITEMGet(h->val),d)<=0)
        return newNode(val,h);

    //cerca posizione
    for(x=h->next,p=h;x!=NULL && DateITEMCompare(d,DateITEMGet(x->val))<=0;p=x, x=x->next);
    p->next=newNode(val,x);
    return h;
}

link ricercaByChiave(link h, char *k){
    link x;
    for(x=h; x!=NULL; x=x->next){
        if(KeyITEMCompare(KeyITEMGet(&x->val),k)==0)
            return x;
    }
    return NULL;
}

ITEM cancellazioneByChiave(link *h,char *k){
    ITEM tmp;
    link x,p;
    if(*h==NULL){
        tmp.codice=strdup("-1");
    }
    for(x=*h,p=NULL;x!=NULL && KeyITEMCompare(k,KeyITEMGet(&x->val))<=0;p=x,x=x->next){
        if(KeyITEMCompare(KeyITEMGet(&x->val),k)==0){
            if(x==*h)
                *h=x->next;
            else
                p->next=x->next;

            tmp=x->val;
            free(x);
            break;
        }
    }

    return tmp;
}

ITEM cancellazioneByDate(link* h, data_s d1, data_s d2){
    link x, p;
    ITEM tmp;
    tmp.codice=strdup("-1"); //ITEMSetVoid

    for(x = *h, p = NULL; x != NULL; p = x, x=x->next) {
        if (DateITEMCompare(d1, x->val.data_di_nascita) >= 0) {
            if (p == NULL) {
                *h = x->next;
            } else {
                p->next = x->next;
            }
            tmp = x->val;
            tmp.codice=strdup(x->val.codice);
            free(x);
            return tmp;
        }
    }
    return tmp;
}

//funzioni per il database

void letturaDaFile(database *db,char *nomeFile){
    char codice[LP],nome[LP],cognome[LP],via[LP],citta[LP],cap[LP]; //stringhe temporanee
    ITEM val; //item temporaneo
    FILE *fp=fopen(nomeFile,"r");


    //inserimento ordinato tramite funzione specifica
    while (fscanf(fp,"%s %s %s %d/%d/%d %s %s %s",codice,nome,cognome,&val.data_di_nascita.giorno,&val.data_di_nascita.mese,&val.data_di_nascita.anno,via,citta,cap)==9){
        val.codice=strdup(codice); val.nome=strdup(nome); val.cognome=strdup(cognome);
        val.indirizzo.via=strdup(via);val.indirizzo.citta=strdup(citta);val.indirizzo.cap=strdup(cap);
        db->head=inserimentoOrdinato(db->head,val);
        db->N+=1;
    }
}

void letturaDaFileIniziale(database *db,char *nomeFile){
    char codice[LP],nome[LP],cognome[LP],via[LP],citta[LP],cap[LP]; //stringhe temporanee
    ITEM val; //item temporaneo
    FILE *fp=fopen(nomeFile,"r");


    fscanf(fp,"%s %s %s %d/%d/%d %s %s %s",codice,nome,cognome,&val.data_di_nascita.giorno,&val.data_di_nascita.mese,&val.data_di_nascita.anno,via,citta,cap);
    val.codice=strdup(codice); val.nome=strdup(nome); val.cognome=strdup(cognome);
    val.indirizzo.via=strdup(via);val.indirizzo.citta=strdup(citta);val.indirizzo.cap=strdup(cap);
    db->head=newNode(val,NULL);


    //inserimento ordinato tramite funzione specifica
    while (fscanf(fp,"%s %s %s %d/%d/%d %s %s %s",codice,nome,cognome,&val.data_di_nascita.giorno,&val.data_di_nascita.mese,&val.data_di_nascita.anno,via,citta,cap)==9){
        val.codice=strdup(codice); val.nome=strdup(nome); val.cognome=strdup(cognome);
        val.indirizzo.via=strdup(via);val.indirizzo.citta=strdup(citta);val.indirizzo.cap=strdup(cap);
        db->head=inserimentoOrdinato(db->head,val);
        db->N+=1;
    }
}

database* dbInit(){
    database *db;
    db=malloc(sizeof(database));
    db->N=0;
    if(db==NULL){
        printf("Errore allocazione database");
        exit(-1);
    }
    letturaDaFileIniziale(db,nomefile);
    return db;
}
void dbFree(database *db){
    link x,p;
    for(x=db->head,p=NULL;x!=NULL;p=x,x=x->next) {
        p->next=x->next;
        freeNode(x);
    }
    free(db);
}


//funzioni wrapper per il menù
void nuovoDaTastiera(database *db){
    char codice[LP],nome[LP],cognome[LP],via[LP],citta[LP],cap[LP]; //stringhe temporanee
    ITEM val; //item temporaneo
    printf("Inserisci i seguenti dati:\n>:<codice> <nome> <cognome> <data_di_nascita> <via> <citta'> <cap>\n(codice:AXXXX dove X=cifra tra 0-9, data_di_nascita nel formato: gg/mm/aaaa)\n");
    scanf("%s %s %s %d/%d/%d %s %s %s",codice,nome,cognome,&val.data_di_nascita.giorno,&val.data_di_nascita.mese,&val.data_di_nascita.anno,via,citta,cap);
        val.codice=strdup(codice); val.nome=strdup(nome); val.cognome=strdup(cognome);
        val.indirizzo.via=strdup(via);val.indirizzo.citta=strdup(citta); val.indirizzo.cap=strdup(cap);
        inserimentoOrdinato(db->head,val);
        db->N++;
}
void nuovoDaFile(database *db){
    char riga[LP];
    printf("Inserisci nome file (compreso di \".txt\")\n>:");
    scanf("%s",riga);
    letturaDaFile(db,riga);
}
ITEM* ricercaPerCodice(database *db){
    char chiave[LP];
    ITEM *pItem;
    link tmp;
    printf("Inserire codice dell'elemento da cercare:\n>:");
    scanf("%s",chiave);
    tmp=ricercaByChiave(db->head,chiave);
    if(tmp!=NULL)
        pItem= &(tmp->val);
    else
        pItem=NULL;
}
ITEM cancellazionePerCodice(database *db){
    char chiave[LP];
    printf("Inserire codice dell'elemento da cancellare:\n>:");
    scanf("%s",chiave);
    return cancellazioneByChiave(&(db->head),chiave);
}

void cancellazionePerDate(database *db){
    ITEM tmp;
    printf("Cancellazione di tutti gli elementi compresi fra due date.\n");
    data_s d1, d2;
    printf("Inserire la prima data (nel formato gg/mm/aaaa).\n>:");
    scanf("%d/%d/%d",&d1.giorno,&d1.mese,&d1.anno);
    printf("Inserire la seconda data (nel formato gg/mm/aaaa).\n>:");
    scanf("%d/%d/%d",&d2.giorno,&d2.mese,&d2.anno);
    tmp=cancellazioneByDate(&db->head,d1,d2);
    while(strcmp(KeyITEMGet(&tmp),"-1")!=0) {
        tmp = cancellazioneByDate(&db->head, d1, d2);
        stampaITEM(&tmp,stdout);
    }
}
void stampaLista(database *db){
    link x;
    char riga[LP];
    FILE *fp;
    printf("Dove vuoi stampare la lista? Inserisci il nome del file (compreso di \".txt\" per stampare su file oppure \"schermo\" per stampare su schermo");
    scanf("%s",riga);
    if(strcmp(riga,"schermo")==0)
        fp=stdout;
    else
        fp=fopen(riga,"w");

    for(x=db->head;x!=NULL;x=x->next) {
        stampaITEM(&x->val,fp);
        printf("\n");
    }

    if(strcmp(riga,"schermo")!=0)
        fclose(fp);
}

