 #include <stdio.h>

int grandezzaV();
void ruota(int v[], int N, int P, int dir);
void stampa(int v[], int N, int dir);


int main() {


    const int maxN=30;
    int N=0;
    N=grandezzaV();
    if(N>maxN || N<=0) {
        printf("Errore! Numero inserito non valido!\n");
        return 0;
    }

    int v[N];
    int dir=0;
    int P=0;

    for(int i=0;i<N;i++){
        printf("Inserisci numero nel vettore in positizione %d \n", i);
        scanf("%d", &v[i]);
    }

    ruota(v, N, P, dir);

    return 0;
}

int grandezzaV(){
    int n;
    printf("Inserisci la grandezza del vettore: ");
    scanf("%d", &n);
    return n;
}


void stampa(int v[], int N,int dir){

    for (int i = 0; i < N; i++)
        printf("%d \b", v[i]);
    printf("\n\n");
}

void ruota(int v[], int N, int P, int dir){

    int tmp;

    do {
        printf("Inserisci direzione:\n -1 per rotazione a destra \n  1 per rotazione a sinistra\n");
        scanf("%d", &dir);


        printf("Inserisci posizioni da ruotare (inserisci 0 per terminare il programma): ");
        scanf("%d", &P);
        if(P<N) {

            if (dir == 1) {
                for (int j = 0; j < P; j++) {
                    tmp = v[0];
                    for (int i = 1; i<N ; i++) {
                        v[i-1] = v[i];
                    }
                    v[N-1]=tmp;
                }
            } else if (dir == -1) {
                for (int j = 0; j < P; j++) {
                    tmp = v[N-1];
                    for (int i= N-1; i>=0 ; i--) {
                        v[i+1] = v[i];
                    }
                    v[0] = tmp;
                }
            } else {
                printf("\nErrore! Dovevi inserire \"1\" oppure \"-1\"");
                break;
            }
        }
        if (P != 0 && (dir == 1 || dir == -1))
            stampa(v,N,dir);
    }
    while (P!=0);
}
