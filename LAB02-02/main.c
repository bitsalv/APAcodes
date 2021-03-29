#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NR 1000
#define NL 30
#define NOMEFILE "log.txt"


typedef enum  {erroreLettura,r_date,r_partenza,r_capolinea,r_ritardo,r_ritardoTOT,r_fine} comando_e;
typedef enum {FALSE,TRUE} boolean;

typedef struct {
    int anno;
    int mese;
    int giorno;
} dataS;

typedef struct {
    int ore;
    int minuti;
    int secondi;
} oraS;

typedef struct {
    char codice_tratta [20];
    char partenza [20] ;
    char destinazione [20] ;
    char dataS[20];
    char oraPS[20];
    char oraAS[20];
    dataS data;
    oraS oraPartenza;
    oraS oraArrivo;
    int ritardo;
} tratta_s;

void caricaTratte(tratta_s tratte[],FILE *fp, int nr);
comando_e leggiComando();
void eseguiComando(tratta_s tratte[],int nT);
void toLowerS(char s[]);
void comandoDate(tratta_s tratte[], int nT);
void comandoPartenza(tratta_s tratte[],int nT);
void comandoCapolinea(tratta_s tratte[],int nT);
void comandoRitardo(tratta_s tratte[],int nT);
void comandoRitardoTOT(tratta_s tratte[],int nT);
int confrontaDate(dataS data1, dataS data2);

int main() {

    int nr;
    char riga[NL];
    tratta_s tratte[NR];

    FILE *fp=fopen(NOMEFILE,"r");
    if(fp==NULL){
        printf("Errore apertura file!\n");
        exit(-1);
    }

    fscanf(fp,"%d",&nr);

    caricaTratte(tratte,fp,nr);

    eseguiComando(tratte,nr);

     return 0;
}

void stampaTratta(tratta_s t) {
    printf("Tratta [%s] da %s a %s del %s (dalle %s alle %s, con ritardo di %d minut%c)", t.codice_tratta, t.partenza, t.destinazione, t.dataS, t.oraAS, t.oraPS, t.ritardo, ((t.ritardo == 1) ? 'o' : 'i'));
    printf("\n");
}

void toLowerS(char s[]) {
    for (int i = 0; *s !='\0' ; i++) {
        *s=tolower(*s);
        s+=i;
    }
}


void caricaTratte(tratta_s tratte[], FILE *fp, int nr){

    for (int i = 0; i <nr ; i++) {
        fscanf(fp,"%s %s %s %s %s %s %d\n",tratte[i].codice_tratta,tratte[i].partenza,tratte[i].destinazione,tratte[i].dataS,tratte[i].oraPS,tratte[i].oraAS,&tratte[i].ritardo);
        sscanf (tratte[i].dataS,"%d/%d/%d", &tratte[i].data.anno,&tratte[i].data.mese,&tratte[i].data.giorno);
        sscanf (tratte[i].oraPS,"%d:%d:%d", &tratte[i].oraArrivo.ore,&tratte[i].oraArrivo.minuti,&tratte[i].oraArrivo.secondi);
        sscanf (tratte[i].oraAS,"%d:%d:%d", &tratte[i].oraPartenza.ore,&tratte[i].oraPartenza.minuti,&tratte[i].oraPartenza.secondi);
    }

    for (int i = 0; i <nr ; ++i) {
        printf("%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d",tratte[i].codice_tratta,tratte[i].partenza,tratte[i].destinazione,tratte[i].data.anno,tratte[i].data.mese,tratte[i].data.giorno,tratte[i].oraPartenza.ore,tratte[i].oraPartenza.minuti,tratte[i].oraPartenza.secondi,tratte[i].oraArrivo.ore,tratte[i].oraArrivo.minuti,tratte[i].oraArrivo.secondi,tratte[i].ritardo);
        printf("\n");
    }

}

comando_e leggiComando(){
    char s[NL];
    printf("Inserire comando: -date -partenza -capolinea -ritardo -ritardo_tot -fine \n");
    scanf("%s",s);
    toLowerS(s);

    if(strcmp(s,"date")==0){
        return r_date;
    } else if(strcmp(s,"partenza")==0){
        return r_partenza;
    } else if(strcmp(s,"capolinea")==0){
        return r_capolinea;
    } else if(strcmp(s,"ritardo")==0){
        return r_ritardo;
    } else if(strcmp(s,"fine")==0){
        return r_fine;
    } else if(strcmp(s,"ritardo_tot")==0){
        return r_ritardoTOT;
    }

    return erroreLettura;
}

int confrontaDate(dataS data1, dataS data2){
    if(data1.anno!=data2.anno)
        return data1.anno-data2.anno;
    else if(data1.mese!=data2.mese)
        return data1.mese-data2.mese;
    else if(data1.giorno!=data2.giorno)
        return data1.giorno-data2.giorno;
    else return 0;
}

void comandoDate(tratta_s tratte[],int nT){
    dataS data1;
    dataS data2;
    printf("Inserisci la prima data nel formato aaaa/mm/gg : ");
    scanf("%d/%d/%d",&data1.anno,&data1.mese,&data1.giorno);
    printf("Inserisci la seconda data nel formato aaaa/mm/gg : ");
    scanf("%d/%d/%d",&data2.anno,&data2.mese,&data2.giorno);

    for (int i = 0; i < nT; i++) {
        if(confrontaDate(data1,tratte[i].data) <=0 && confrontaDate(tratte[i].data,data2)<=0 ){
            stampaTratta(tratte[i]);
        }
    }

}
void comandoPartenza(tratta_s tratte[],int nT){
    char s[20];
    char tmp[20];
    printf("Inserisci fermata di partenza: ");
    scanf("%s",s);
    toLowerS(s);

    for (int i = 0; i <nT ; i++) {
        strcpy(tmp,tratte[i].partenza);
        toLowerS(tmp);
        if(strcmp(tmp,s)==0){
            stampaTratta(tratte[i]);
        }
    }
}
void comandoCapolinea(tratta_s tratte[],int nT){
    char s[20];
    char tmp[20];
    printf("Inserisci fermata di capolinea: ");
    scanf("%s",s);
    toLowerS(s);

    for (int i = 0; i <nT ; i++) {
        strcpy(tmp,tratte[i].destinazione);
        toLowerS(tmp);
        if(strcmp(tmp,s)==0){
            stampaTratta(tratte[i]);
        }
    }
}
void comandoRitardo(tratta_s tratte[],int nT){
    dataS data1;
    dataS data2;
    printf("Inserisci la prima data nel formato aaaa/mm/gg : ");
    scanf("%d/%d/%d",&data1.anno,&data1.mese,&data1.giorno);
    printf("Inserisci la seconda data nel formato aaaa/mm/gg : ");
    scanf("%d/%d/%d",&data2.anno,&data2.mese,&data2.giorno);

    for (int i = 0; i < nT; i++) {
        if(confrontaDate(data1,tratte[i].data) <=0 && confrontaDate(data2,tratte[i].data)>=0 ){
            if(tratte[i].ritardo>0){
                stampaTratta(tratte[i]);
            }
        }
    }

}
void comandoRitardoTOT(tratta_s tratte[],int nT){
    char s[20];
    int ritardoTOT=0;

    printf("Inserire codice tratta: ");
    scanf("%s",s);

    for (int i = 0; i <nT ; i++) {
        if(strcmp(tratte[i].codice_tratta,s)==0){
            ritardoTOT+=tratte[i].ritardo;
        }
    }

    printf("Il ritardo complessivo della tratta con codice %s e' %d\n",s,ritardoTOT);
}

void eseguiComando(tratta_s tratte[],int nT) {

    boolean continua = TRUE;
    while (continua){
        switch (leggiComando()) {
            case r_date:
                comandoDate(tratte,nT);
                break;
            case r_partenza:
                comandoPartenza(tratte,nT);
                break;
            case r_capolinea:
                comandoCapolinea(tratte,nT);
                break;
            case r_ritardo:
                comandoRitardo(tratte,nT);
                break;
            case r_ritardoTOT:
                comandoRitardoTOT(tratte,nT);
                break;
            case r_fine :
                continua = FALSE;
                break;
            case erroreLettura:
            default:
                printf("Errore lettura comando!"); continua=FALSE;

        }
    }
}


