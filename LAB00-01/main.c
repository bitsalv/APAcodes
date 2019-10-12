#include <stdio.h>
#include <string.h>

int inserimento();
int maxPassi(int N, int v[]);
void trovaSequenze(int N,int max, int v[]);
void stampaSequenze(int l, int r,int v[],int N);
int main() {


    int M=inserimento();
    if(M==-1) return 0;
    int v[M];

    for(int i=0;i<M;i++){
        printf("Inserisci numero:");
        scanf("%d", &v[i]);
    }

    int max=maxPassi(M,v);
    trovaSequenze(M,max,v);
    return 0;
}



int inserimento()
{
    int N;
    printf("Inserisci la lunghezza del vettore(max 30): ");
    scanf("%d", &N);

    if (N > 30) {
        printf("Errore! Troppo lungo.");
        return -1;
    }

    return N;
}

int maxPassi(int N, int v[]){
    int contatore=0;
    int max=0;

    for(int i=0;i<N;i++){
        if(v[i]!=0)
            contatore++;
        else {
            if(contatore>max)
                max=contatore;
            contatore=0;
        }
    }
    if(contatore>max)
        max=contatore;

    return max;
}

void trovaSequenze(int N,int max, int v[]){
    int contatore=0;

    for(int i=0;i<N;i++){
        if(v[i]!=0){
            contatore++;
            if(contatore==max){
                stampaSequenze(i-max+1,i+1,v,N);
                printf("\n");
            }
        } else contatore=0;
    }
}

void stampaSequenze(int r,int l,int v[], int N){
    for(int i=r;i<l;i++){
        printf("%d",v[i]);
    }
}
