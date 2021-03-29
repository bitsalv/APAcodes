#include <stdio.h>

int gcd(int a,int b);

int main() {
    int a,b, tmp, mcd;
    printf("Inserisci a:");
    scanf("%d",&a);
    printf("Inserisci b:");
    scanf("%d",&b);


    if(a<=b) {
        tmp = a;
        a = b;
        b = tmp;
    }

    mcd=gcd(a,b);

    printf("Il Massimo Comune Divisore di %d e %d e': %d",a,b,mcd);

    return 0;
}

int gcd(int a,int b){
    int gcdn=1, tmp;

    if(a<=b) {
        tmp = a;
        a = b;
        b = tmp;
    }

    if(a%b==0){
        return b;
    }

    if(a%2==0 && b%2==0)
        gcdn=2*gcd(a/2,b/2);
    else if(a%2==1 && b%2==0)
        gcdn=2*gcd(a,b/2);
    else if(a%2==1 && b%2==1)
        gcdn=2*gcd((a-b)/2,b);


    return gcdn;
}