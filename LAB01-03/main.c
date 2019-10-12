#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXM 30
#define MAXS 100
#define MAXNFILE 20


typedef enum {FALSE, TRUE} boolean;
typedef struct {
    int nr;
    int nc;
    boolean lettura;
} risultatoLettura ;

risultatoLettura leggiMatrice(FILE *fp, int m[][MAXM]);
boolean ruotaMatrice(int m[][MAXM], int nr, int nc);
void ruotaRiga(int m[][MAXM],int indice, char direzione[], int posizioni, int nr, int nc);
void ruotaColonna(int m[][MAXM],int indice, char direzione[], int posizioni, int nr, int nc);
void toLowerStringa(char s[]);
void stampaMatrice(int m[][MAXM],int nr,int nc);

int main(void) {

    int m[MAXM][MAXM];
    char nomeFile[MAXNFILE];

    FILE *fp;
    risultatoLettura rL;

    fprintf(stdout,"Inserisci nome file:");
    fscanf(stdin,"%s",nomeFile);
    fp=fopen(nomeFile,"r");

    rL=leggiMatrice(fp,m);
    if(!rL.lettura)
        exit(-1);
    while(ruotaMatrice(m,rL.nr,rL.nc));

    return 0;
}


void stampaMatrice(int m[][MAXM],int nr,int nc){

    fprintf(stdout,"\nMatrice ruotata:\n");
    for (int i = 0; i <nr ; ++i) {
        for (int j = 0; j <nc ; ++j) {
            fprintf(stdout,"%d", m[i][j]);
        }
        fprintf(stdout,"\n");
    }
}

void toLowerStringa(char s[]){
    int l=strlen(s);

    for (int i = 0; i <l ; ++i) {
        s[i]= (char) tolower(s[i]);
    }
}

risultatoLettura leggiMatrice(FILE *fp, int m[][MAXM]){
    int nr,nc;
    risultatoLettura rl;

    if(fp==NULL) {
        rl.lettura=FALSE;
        return rl;
    }

    fscanf(fp,"%d%d", &nr, &nc);

    for (int i=0;i<nr;i++)
        for(int j=0;j<nc;j++)
            fscanf(fp,"%d", &m[i][j]);

        rl.nr=nr;
        rl.nc=nc;
        rl.lettura=TRUE;
    return rl;
}

void ruotaRiga(int m[][MAXM],int indice, char direzione[], int posizioni, int nr, int nc) {
    int tmp;
    toLowerStringa(direzione);

    if (strcmp(direzione, "sinistra")==0) {
        for (int j = 0; j < posizioni; j++) {
            tmp = m[indice][0];
            for (int i = 1; i < nc; i++) {
                m[indice][i-1]= m[indice][i];
            }
            m[indice][nc-1]=tmp;
        }
    } else if (strcmp(direzione, "destra")==0) {
        for (int j = 0; j < posizioni; j++) {
            tmp = m[indice][nc-1];
            for (int i = nc - 1; i >= 0; i--) {
                m[indice][i + 1] = m[indice][i];
            }
            m[indice][0] = tmp;
        }
    }
}

    void ruotaColonna(int m[][MAXM],int indice, char direzione[], int posizioni, int nr, int nc) {
        int tmp;
        toLowerStringa(direzione);

        if (strcmp(direzione, "su")==0) {
                for (int j = 0; j < posizioni; j++) {
                    tmp = m[0][indice];
                    for (int i = 1; i < nr; i++) {
                        m[i-1][indice]= m[i][indice];
                    }
                    m[nr-1][indice]=tmp;
                }
            } else if (strcmp(direzione, "giu")==0) {
                for (int j = 0; j < posizioni; j++) {
                    tmp = m[nr-1][indice];
                    for (int i = nr-1; i >= 0; i--) {
                        m[i + 1][indice] = m[i][indice];
                    }
                    m[0][indice] = tmp;
                }
            }
}


    boolean ruotaMatrice(int m[][MAXM], int nr, int nc) {
        char s[MAXS];
        char selettore[MAXS],direzione[MAXS];
        int indice,posizioni;


        fprintf(stdout,"\nInserisci <selettore> <indice> <direzione> <posizioni>.\nEsempio: \"riga 1 destra 1\"\nInserisci \"fine\" per terminare\n");
        fgets(s, MAXS, stdin);

        sscanf(s, "%s %d %s %d", selettore, &indice, direzione, &posizioni);
        toLowerStringa(selettore); toLowerStringa(direzione);

        if (strcmp(selettore, "fine")==0)
            return FALSE;

        if (strcmp(selettore, "riga")==0)
            ruotaRiga(m,indice-1, direzione, posizioni,nr,nc);
        else if (strcmp(selettore, "colonna")==0)
            ruotaColonna(m,indice-1, direzione, posizioni,nr,nc);

        stampaMatrice(m,nr,nc);
        return TRUE;
    }


