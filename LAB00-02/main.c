#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef enum {FALSE,TRUE} boolean ;

int conta(char s[],int n);
void stampa(char s[],int cont);
void stampaSS(char s[],int l,int r);
boolean vocale(char c);

int main(){

    FILE *fp;
    const int maxCaratteri=20;
    char nomeFile[maxCaratteri], parola[maxCaratteri];
    int n, contatore=0, numRighe;


     printf("Inserire nome file: ");
     scanf("%s",nomeFile);


    printf("\nInserisci lunghezza sottostringhe da trovare: ");
    scanf("%d",&n);

    fp=fopen(nomeFile,"r");
    if(fp==NULL){
        printf("Errore apertura file");
        return -1;
    }


    fscanf(fp,"%d",&numRighe);

    if(numRighe<=0) {
        printf("Errore, numero di righe non valido");
        return -1;
    }



    while(fscanf(fp,"%s",parola) !=EOF){
        printf("%s",parola);
        contatore+=conta(parola,n);
    }

    printf("Sottostringhe con 2 vocali totali trovate: %d", contatore);


    fclose(fp);

    return 0;
}

boolean vocale(char c){

    switch(tolower(c)){
    case 'a': case 'e': case 'i': case 'o': case 'u': return TRUE;
        default: return FALSE;
    }

 }

int conta(char s[], int n){
    int sottoStringhe=0;
    int contaVocali=0;
    int lungS=strlen(s);

    for(int i=0;i<lungS-n-1;i++){
        for(int j=0;j<n;j++) {
            if (vocale(s[i + j]))
                contaVocali++;
        }
            if(contaVocali==2) {
                sottoStringhe++;
                stampaSS(s,i,i+n);
        }
        contaVocali=0;
    }

    stampa(s, sottoStringhe);

    return sottoStringhe;
}

void stampaSS(char s[], int l,int r){
    printf("\n");
    for(int i=l;i<r;i++)
        printf("%c",s[i]);
}

void stampa(char s[], int cont){
    printf("\nS=\"");
    printf("%s",s);
    printf("\" sottostringhe trovate %d\n", cont);
}