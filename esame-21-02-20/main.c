#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "piatto.h"
#include "BST.h"

void generaMenu(BST bst, PIATTO *piatti,int nP,int k);
void generaMenuR(BST bst, PIATTO *piatti, int *mark, menu m, int pos, int *sol, int nP, int s,int k);
/*non implementato in aula
void stampaMenu(BST bst, PIATTO *piatti);
*/

int main(int argc, char **argv) {

    if(argc!=2) {
        printf("Errore numero parametri");
        exit(-1);
    }
    int k=atoi(argv[1]);
    char s[100];
    printf("Inserisci nome file:\n");
    scanf("%s",s);
    FILE *fp=fopen(s,"r");
    if(fp==NULL)
        exit(-2);

    PIATTO *piatti;
    int nP;
    nP=caricaPiatti(piatti,fp);
    BST bst=BSTinit();
    generaMenu(bst,piatti,nP,k);
    //stampaMenu(bst,piatti);


    free(piatti);
    fclose(fp);
    BSTfree(bst);

    return 0;
}

void generaMenuR(BST bst, PIATTO *piatti, int *mark, menu m, int pos, int *sol, int nP, int s, int k){
    if(pos>=k){
            m.totPrezzo=0;
        for (int i = 0; i < k; i++) {
            m.piatti[i]=sol[i];
            m.totPrezzo+=tornaPrezzo(piatti[sol[i]]);
        }

        if(menuCompare(BSTmax(bst),&m)==-1)
            BSTinsert_root(bst,&m);
        else
            BSTinsert_leafR(bst,&m);
        return;
    }

    for(int i=s; i<nP; i++){ //modificato
        if(mark[i]>0){
            mark[i]--;
            sol[pos]=i;
            generaMenuR(bst,piatti,mark,m,pos+1,sol,nP,s,k);
            s++;
            mark[i]++;
        }
    }
}

void generaMenu(BST bst, PIATTO *piatti, int nP,int k){
    int *mark=malloc(k* sizeof(int)); //modificato
    int *sol=malloc(k* sizeof(int)); //modificato
    menu m; m.piatti=malloc(k* sizeof(int)); m.nP=k;
    for (int i = 0; i < k; i++) {
        m.piatti[i]=-1;
        mark[i]=2;
    }
    generaMenuR(bst,piatti,mark,m,0,sol,nP,0,k);
    free(m.piatti);
    free(sol);
    free(mark);
}

/*non implementata in aula
void stampaMenu(BST bst, PIATTO *piatti){
     BSTvisit(bst,POSTORDER,piatti);
}*/
