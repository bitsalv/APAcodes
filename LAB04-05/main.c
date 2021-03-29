#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NR 31
#define MAXR 1000

typedef struct {
    int anno;
    int mese;
    int giorno;
} dataS;

typedef struct {
    int ora;
    int minuto;
    int secondi;
} tempo;

typedef struct {
    char *codice_tratta;
    char *partenza;
    char *destinazione;
    char *dataS;
    tempo ora_partenza;
    tempo ora_arrivo;
    dataS data;
    int ritardo;
} tratta_s;

typedef enum {data,codice_tratta,partenza,arrivo,nessuno} e_ordinamento;
typedef enum {stampaN,stampaD,stampaCT,stampaA,stampaP,ricercaC,ricercaP,fine} e_comandi;
typedef enum {false,true} boolean;

typedef struct {
    tratta_s tratte[MAXR];
    tratta_s *trattaD[MAXR], *trattaCT[MAXR], *trattaP[MAXR], *trattaA[MAXR], *trattaN[MAXR];
    int numeroTratte;
} DB;



DB* leggiFile(char *nomeFile);
e_comandi leggiComando();
void eseguiComando(DB *pDB);
void stampaTratte(tratta_s *tratte[], int n);
void ordina(DB *pDB,e_ordinamento chiave);
void ricercaDaPartenzaDicotomica(tratta_s *tratte[], int numeroTratte, char *partenza, int nCharConfronto);
int ricercaDaCodiceDicotomica(tratta_s *tratte[], int numeroTratte, char *codice);
int ricercaDCR(tratta_s *tratte[],int l, int r, char *codice);
void insertionSort(tratta_s *ptratte[], int l, int r,e_ordinamento chiave);
int confrontaTratte(tratta_s *trattaA, tratta_s *trattaB, e_ordinamento chiave);

int comparaOra(tempo o1, tempo o2) {
    if (o1.ora != o2.ora)
        return (o1.ora-o2.ora);
    else if (o1.minuto != o2.minuto)
        return (o1.minuto-o2.minuto);
    else if (o1.secondi != o2.secondi)
        return (o1.secondi-o2.secondi);
    else return 0;
}

int main() {
    DB *pDB;
    char fin[30];
    printf("Inserisci il nome del file (completo di .txt): ");
    scanf("%s",fin);
    pDB=leggiFile(fin);
    if(pDB==NULL)
        exit(-1);

    eseguiComando(pDB);

    return 0;
}



DB* leggiFile(char *nomeFile){
    DB database;
    DB *Pdatabase=&database;

    FILE *fp=fopen(nomeFile,"r");
    char codicetratta[NR],partenzaS[NR],destinazioneS[NR],dataS[NR];

    if(fp==NULL){
        printf("Errore apertura file!");
        return NULL;
    }

    fscanf(fp,"%d",&Pdatabase->numeroTratte);



    for (int i = 0; i <Pdatabase->numeroTratte ; i++) {
        fscanf(fp,"%s %s %s %s %d:%d:%d %d:%d:%d %d",codicetratta,partenzaS,destinazioneS,dataS,&Pdatabase->tratte[i].ora_partenza.ora,&Pdatabase->tratte[i].ora_partenza.minuto,&Pdatabase->tratte[i].ora_partenza.secondi,&Pdatabase->tratte[i].ora_arrivo.ora,&Pdatabase->tratte[i].ora_arrivo.minuto,&Pdatabase->tratte[i].ora_arrivo.secondi,&Pdatabase->tratte[i].ritardo);
        Pdatabase->tratte[i].codice_tratta=strdup(codicetratta);
        Pdatabase->tratte[i].partenza=strdup(partenzaS);
        Pdatabase->tratte[i].destinazione=strdup(destinazioneS);
        Pdatabase->tratte[i].dataS=strdup(dataS);
    }

    for (int j = 0; j <Pdatabase->numeroTratte ; j++) {
        Pdatabase->trattaCT[j]=&Pdatabase->tratte[j];
        Pdatabase->trattaA[j]=&Pdatabase->tratte[j];
        Pdatabase->trattaD[j]=&Pdatabase->tratte[j];
        Pdatabase->trattaP[j]=&Pdatabase->tratte[j];
        Pdatabase->trattaN[j]=&Pdatabase->tratte[j];
    }


    ordina(Pdatabase,codice_tratta);
    ordina(Pdatabase,arrivo);
    ordina(Pdatabase,partenza);
    ordina(Pdatabase,data);

    fclose(fp);

    return Pdatabase;
}

e_comandi leggiComando() {
    char riga[NR];
    fprintf(stdout,"Inserisci un comando: \n-\"stampaN\" per stampa non ordinata\n-\"stampaD\" per stampa ordinata per data\n-\"stampaCT\" per stampa ordinata per codice tratta\n-\"stampaA\" per stampa ordinata per arrivo\n-\"stampaP\" per stampa ordinata per partenza\n-\"ricercaC\" per ricercare una tratta tramite il codice_tratta\n\"ricercaP\" per ricercare una tratta tramite stazione di partenza\n-\"fine\" per teminare\n>:");
    fscanf(stdin, "%s", riga);
    char cmd[][NR] = {"stampaN","stampaD","stampaCT","stampaA","stampaP","ricercaC","ricercaP","fine"};

    for (int i = 0; i < 8; i++)
        if (strcmp(riga, cmd[i]) == 0)
            return i;
}


void stampaTratte(tratta_s *tratte[], int numeroTratte){

    FILE *fp;
    char riga[NR];
    boolean daFile=false;

    printf("Dove vuoi stampare il file? Scrivi \"schermo\" per stampare a schermo.\nScrivi il nome del file (compreso di \".txt\") per scrivere in un nuovo file.\n>");
    scanf("%s",riga);

    if(strcmp(riga,"schermo")==0)
        fp=stdout;
    else {
        fp = fopen(riga, "w");
        daFile=true;
    }
    for (int i = 0; i <numeroTratte ; i++)
        fprintf(fp,"Tratta [%s] da %s a %s del %s (dalle %d:%d:%d alle %d:%d:%d, con ritardo di %d minut%c)\n", tratte[i]->codice_tratta , tratte[i]->partenza, tratte[i]->destinazione, tratte[i]->dataS,tratte[i]->ora_arrivo.ora,tratte[i]->ora_arrivo.minuto,tratte[i]->ora_arrivo.secondi, tratte[i]->ora_partenza.ora,tratte[i]->ora_partenza.minuto,tratte[i]->ora_partenza.secondi, tratte[i]->ritardo, ((tratte[i]->ritardo == 1) ? 'o' : 'i'));
        fprintf(fp,"\n");

    if(daFile==true)
        fclose(fp);

}

int confrontaTratte(tratta_s *trattaA, tratta_s *trattaB,e_ordinamento chiave){

    switch (chiave){
        case data: {
            int cmp=strcmp(trattaA->dataS,trattaB->dataS);
            if(cmp==0) return comparaOra(trattaA->ora_partenza,trattaB->ora_partenza);
            return cmp;
        }
        case codice_tratta:{
            return strcmp(trattaA->codice_tratta,trattaB->codice_tratta);
        }
        case partenza: {
            return strcmp(trattaA->partenza, trattaB->partenza);
        }
        case arrivo: {
            return strcmp(trattaA->destinazione, trattaB->destinazione);
        }
        default: {
            break;
        }
    }
    return 0;
}

void insertionSort(tratta_s *tratte[],int l, int r,e_ordinamento chiave){
    int i,j;
    tratta_s *x;
    for (i=l+1; i<=r ; i++) {
        x=tratte[i];
        j=i-1;
        while (j>=l && confrontaTratte(x,tratte[j],chiave)<0){
            tratte[j+1]=tratte[j];
            j--;
        }
        tratte[j+1]=x;
    }

}

void ordina(DB *db, e_ordinamento chiave) {
    int l = 0, r = db->numeroTratte - 1;
    switch (chiave) {
        case data: insertionSort(db->trattaD, l, r, chiave); break;
        case codice_tratta: insertionSort(db->trattaCT,l,r,chiave); break;
        case partenza:insertionSort(db->trattaP,l,r,chiave); break;
        case arrivo: insertionSort(db->trattaA,l,r,chiave); break;
        case nessuno: break;
        default: printf("Errore inserimento chiave");
    }
}

int ricercaDCR(tratta_s *tratte[],int l, int r, char *codice) {
    int medio=(l+r)/2;
    if(l>r)
        return -1;
    else if(strcmp(tratte[medio]->codice_tratta,codice)==0)
        return medio;
    else if(strcmp(tratte[medio]->codice_tratta,codice)>0)
        ricercaDCR(tratte,l,medio-1,codice);
    else
        ricercaDCR(tratte,medio+1,r,codice);
}

int ricercaDaCodiceDicotomica(tratta_s *tratte[], int numeroTratte, char *codice){
    int l=0, r=numeroTratte-1;
    return ricercaDCR(tratte,l,r,codice);
}

void ricercaDPR(tratta_s *tratte[],int l,int r, char *partenza, int nCharConfronto){
    int medio=(l+r)/2;
    if(l>r)
        printf("Elemento non trovato!\n");
    else if(strncmp(tratte[medio]->partenza,partenza,nCharConfronto)==0)
        printf("Elemento trovato!\nTratta [%s] da %s a %s del %s (dalle %d:%d:%d alle %d:%d:%d, con ritardo di %d minut%c)\n", tratte[medio]->codice_tratta , tratte[medio]->partenza, tratte[medio]->destinazione, tratte[medio]->dataS,tratte[medio]->ora_arrivo.ora,tratte[medio]->ora_arrivo.minuto,tratte[medio]->ora_arrivo.secondi, tratte[medio]->ora_partenza.ora,tratte[medio]->ora_partenza.minuto,tratte[medio]->ora_partenza.secondi, tratte[medio]->ritardo, ((tratte[medio]->ritardo == 1) ? 'o' : 'i'));
    else if(strncmp(tratte[medio]->partenza,partenza,nCharConfronto)>0)
        ricercaDPR(tratte,l,medio-1,partenza,nCharConfronto);
    else
        ricercaDPR(tratte,medio+1,r,partenza,nCharConfronto);
}

void ricercaDaPartenzaDicotomica(tratta_s *tratte[], int numeroTratte, char *partenza, int nCharConfronto){
   // int l=0,r=numeroTratte-1;
  //  ricercaDPR(tratte,l,r,partenza,nCharConfronto);
  //ricercaDicotomicaIterativa
    int iniziale = 0, finale =numeroTratte-1, medio, i, j, cmp;
    boolean trovato = 0;

    while(iniziale <= finale && !trovato) {
        medio = (iniziale + finale) / 2;
        cmp = strncmp(tratte[medio]->partenza, partenza, nCharConfronto);
        if(cmp == 0) {
            trovato = 1;
        } else {
            if(cmp < 0)
                iniziale = medio + 1;
            else
                finale = medio - 1;
        }
    }

    if(trovato) {
        i = medio;
        j = medio -1;
        while(i < numeroTratte && strncmp(tratte[i]->partenza, partenza, nCharConfronto) == 0) {
            printf("Elemento trovato!\nTratta [%s] da %s a %s del %s (dalle %d:%d:%d alle %d:%d:%d, con ritardo di %d minut%c)\n", tratte[i]->codice_tratta , tratte[i]->partenza, tratte[i]->destinazione, tratte[i]->dataS,tratte[i]->ora_arrivo.ora,tratte[i]->ora_arrivo.minuto,tratte[i]->ora_arrivo.secondi, tratte[i]->ora_partenza.ora,tratte[i]->ora_partenza.minuto,tratte[i]->ora_partenza.secondi, tratte[i]->ritardo, ((tratte[i]->ritardo == 1) ? 'o' : 'i'));
            i++;
        }
        while(j>=0 && strncmp(tratte[j]->partenza, partenza, nCharConfronto) == 0) {
            printf("Elemento trovato!\nTratta [%s] da %s a %s del %s (dalle %d:%d:%d alle %d:%d:%d, con ritardo di %d minut%c)\n", tratte[j]->codice_tratta , tratte[j]->partenza, tratte[j]->destinazione, tratte[j]->dataS,tratte[j]->ora_arrivo.ora,tratte[j]->ora_arrivo.minuto,tratte[j]->ora_arrivo.secondi, tratte[j]->ora_partenza.ora,tratte[j]->ora_partenza.minuto,tratte[j]->ora_partenza.secondi, tratte[j]->ritardo, ((tratte[j]->ritardo == 1) ? 'o' : 'i'));
            j--;
        }
    } else
        printf("Voce non trovata");
}

void eseguiComando(DB *pDB){
    boolean continua=true;
    int numeroTratte=pDB->numeroTratte;
    while (continua){
        switch (leggiComando()){
            case stampaN: printf("Elenco non ordinato.\n");  stampaTratte(pDB->trattaN,numeroTratte);  break;
            case stampaA: printf("Elenco ordinato per stazione d'arrivo.\n"); stampaTratte(pDB->trattaA,numeroTratte);  break;
            case stampaD: printf("Elenco ordinato per data.\n"); stampaTratte(pDB->trattaD,numeroTratte);  break;
            case stampaP: printf("Elenco ordinato per stazione di partenza.\n"); stampaTratte(pDB->trattaP,numeroTratte);  break;
            case stampaCT: printf("Elenco ordinato per codice tratta.\n"); stampaTratte(pDB->trattaCT,numeroTratte); break;
            case ricercaP:{
                char part[MAXR];
                printf("Inserisci stazione di partenza:\n>: ");
                scanf("%s",part);
                ricercaDaPartenzaDicotomica(pDB->trattaP,numeroTratte,part,strlen(part));
            }
                break;
            case ricercaC:{
                char cod[MAXR];
                int indice;
                printf("Inserisci codice tratta da cercare:\n>: ");
                scanf("%s",cod);
                indice=ricercaDaCodiceDicotomica(pDB->trattaCT,numeroTratte,cod);
                indice>=0 ? printf("Elemento trovato!\nTratta [%s] da %s a %s del %s (dalle %d:%d:%d alle %d:%d:%d, con ritardo di %d minut%c)\n", pDB->trattaCT[indice]->codice_tratta , pDB->trattaCT[indice]->partenza, pDB->trattaCT[indice]->destinazione, pDB->trattaCT[indice]->dataS,pDB->trattaCT[indice]->ora_arrivo.ora,pDB->trattaCT[indice]->ora_arrivo.minuto,pDB->trattaCT[indice]->ora_arrivo.secondi, pDB->trattaCT[indice]->ora_partenza.ora,pDB->trattaCT[indice]->ora_partenza.minuto,pDB->trattaCT[indice]->ora_partenza.secondi, pDB->trattaCT[indice]->ritardo, ((pDB->trattaCT[indice]->ritardo == 1) ? 'o' : 'i')) : printf("Elemento non trovato!\n");
            }
                break;

            case fine:
                continua=false;
                break;
            default:
                printf("Errore lettura comando!");
                continua=false;
                break;
        }
    }
}