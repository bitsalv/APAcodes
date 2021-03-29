#include <stdio.h>
#include <stdlib.h>

typedef enum {FALSE,TRUE} boolean;

int majority(int *a, int N);
int quickMajority(int *vet, int l, int r);
void riempiVettore(int *a, int N);
int conta(int *a, int E1, int E2, int l, int r, int q);

int main() {

    int N, ris, *vet;
    printf("Inserisci numero elementi del vettore: ");
    scanf("%d",&N);
    vet=(int *) malloc(N* sizeof(int));
    if(vet==NULL)
        exit(-1);

    riempiVettore(vet,N);
    ris=majority(vet,N);

    ris==-1 ? printf("L'elemento maggioritario non esiste!") : printf("L'elemento maggioritario e`: %d", ris );

    free(vet);
    return 0;
}

int conta(int *a, int E1, int E2, int l, int r, int q){
    int k,tmp1=-1,tmp2=-1, cnt1=0,cnt2=0;

    for (k = l; k <=r ; k++) {
            if(a[k]==E1){
                tmp1=a[k];
                cnt1++;
        } else if(a[k]==E2){
                tmp2=a[k];
                cnt2++;
            }
    }

    if(cnt1>q)
        return tmp1;
    else if(cnt2>q)
        return tmp2;
    else
        return -1;
}

int quickMajority(int *vet, int l, int r){
    int q=(l+r)/2;
    int m=q, cnt=0;
    int v, u;

    if(r<=l) {
        return vet[l];
    }

    u=quickMajority(vet,l,q);
    v=quickMajority(vet,q+1,r);
    return conta(vet,u,v,l,r,q);
}


int majority(int *a, int N){
    int l=0, r=N-1;
    return  quickMajority(a,l,r);
}

void riempiVettore(int *vet, int N){

    for (int i = 0; i <N ; i++) {
        printf("\nInserisci l'elemento %d del vettore: ",i);
        scanf("%d",&vet[i]);
    }
    printf("\n");
}
