#include <stdio.h>
#include <stdlib.h>
#define MAXR 30
typedef enum {false,true} boolean;

typedef struct {
    int inizio, fine, durata;
}att;

void attSel(int N, att *v);
void attSelR(int pos, att *v, int *sol, int *bestsol, int n, int sum,int *max);
int check(att *v, int *sol, int n, int pos);

int main() {
    FILE *fp;
    char s[MAXR];
    int N;
    att *v;
    printf("Inserisci nome file:\n>:");
    scanf("%s", s);
    fp=fopen(s,"r");
    if(fp==NULL) {
        printf("Errore apertura file!\n");
        exit(-1);
    }
    fscanf(fp,"%d",&N);
    v= (att*) malloc(N*sizeof(att));

    if(v==NULL){
        printf("Errore allocazione memoria!\n");
        exit(-2);
    }

    for(int i=0;i<N;i++) {
        fscanf(fp, "%d %d", &v[i].inizio, &v[i].fine);
    }

    printf("S=(");
    for (int j = 0; j < N ; j++) {
        printf("(%d,%d)%s",v[j].inizio,v[j].fine, j==(N-1) ? "" : " ");
        v[j].durata=v[j].fine-v[j].inizio;
    }
    printf(")\nInsieme delle attivita' compatibili che massimizza la somma delle durate e':\n");
    attSel(N,v);

    free(v);
    fclose(fp);
    return 0;
}

int check(att *v, int *sol, int n, int pos){
    for (int i = 0; i <pos ; i++)
        if(sol[i]!=0)
            if(v[i].inizio<v[pos].fine && v[pos].inizio<v[i].fine)
                return 1;
    return 0;
}

void attSelR(int pos, att *v, int *sol, int *bestsol, int n, int sum, int *max){
    int i=0;
    if(pos>=n){
        if(*max<sum){
            *max=sum;
            for (i=0; i<n; i++)
                bestsol[i]=sol[i];
        }
        return;
    }
    sol[pos]=0;
    attSelR(pos+1,v,sol,bestsol,n,sum,max);
    if(!check(v,sol,n,pos)) {
        sol[pos] = 1;
        attSelR(pos + 1, v, sol, bestsol, n,sum+v[pos].durata,max);
    }
    return;
}

void attSel(int N, att *v){
    int max=0,*s=calloc(N,sizeof(int)),*bestsol=calloc(N, sizeof(int));
    attSelR(0,v,s,bestsol,N,0,&max);
    for(int i=0;i<N;i++)
        if(bestsol[i])
            printf("(%d,%d)%s", v[i].inizio,v[i].fine, i==(N-1)? "":" ");
    printf(" per una somma delle durate pari a %d", max);
    free(s);
    free(bestsol);
}