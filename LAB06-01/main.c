#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int v;
    int w;
} arco_s;

int powerset_r(arco_s *archi, int k, int *sol, int pos, int start, int E, int N, int count);
int check(int *sol, arco_s *a, int E, int k);

int main() {

    int N, E, k, cnt, tot=0;
    char riga[25];
    printf("Inserisci nome file:\n>:");
    scanf("%s", riga);
    FILE *fp=fopen(riga,"r");
    fscanf(fp,"%d%d",&N,&E);

    arco_s *archi = (arco_s *) malloc( E * sizeof(arco_s));
    int *sol= calloc(N,sizeof(int));

    for (int i = 0; i < E ; i++)
        fscanf(fp,"%d%d",&archi[i].v,&archi[i].w);

    printf("Vertex cover\n");
    for(k=1;k<=N;k++){
        cnt=powerset_r(archi,k,sol,0,0,E,N,0);
        if(cnt==0)
            printf("Nessuna soluzione\n");
        tot+=cnt;
    }

    printf("Numero di soluzioni: %d\n",tot);


    free(sol);
    free(archi);
    return 0;
}


int check(int *sol, arco_s *a, int E, int k){
    int i, j, arcocnt = 0;
    int *arcocheck = calloc(E, sizeof(int));

    for (i=0; i<k; i++) {
        for (j=0; j<E; j++) {
            if (a[j].v == sol[i] || a[j].w == sol[i]) {
                if (arcocheck[j] == 0)
                    arcocnt++;
                arcocheck[j] = 1;
            }
        }
    }
    free(arcocheck);
    return (arcocnt == E);
}

int powerset_r(arco_s *archi, int k, int *sol, int pos, int start, int E, int N, int count){

    int i;

    if(pos>=k) {
        if (check(sol,archi,E,k)) {
            printf("{");
            for (i = 0; i <k; i++)
                printf("%d", sol[i]);
            printf("} ");
            return count+1;
        }
        return count;
    }
    for(i=start; i<N; i++){
        sol[pos]=i;
        count =powerset_r(archi,k,sol,pos+1,i+1,E,N,count);
    }

    return  count;
}