#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct nodo
{
    int info1;
    int info2;
    struct nodo *successivo;
};
typedef struct nodo Nodo;
typedef Nodo *Puntatore;
int Potenza(int a, int b)
;Puntatore inizializza ();
Puntatore inserisci_in_testa(Puntatore o, int nuovo1, int nuovo2);
void stampalista(Puntatore o, int s);
Puntatore elimina_tutti(Puntatore o, int eliminandus);
void stampalista(Puntatore o, int s)
{
    while (o!=NULL)
    {
        if(o->info1!=0)
        {
            if(s==1)
                o->info1=-o->info1;
            printf("%6d%6d\n", o->info1, o->info2);
        }
        o=o->successivo;
    }
}
Puntatore inserisci_in_testa(Puntatore o, int nuovo1, int nuovo2)
{ 
    Puntatore p,a;
    p=malloc(sizeof(Nodo));
    a=p;
    p->info1=nuovo1;
    p->info2=nuovo2;
    p->successivo=o;
    return a;
}
Puntatore inizializza ()
{
    return NULL;
}
int Potenza(int a, int b)
{
    if (b==0)
        return 1; //lo so che sto dicendo che 0^0=1 ma nell'algoritmo in questione non ha importanza
    return a*Potenza(a, b-1);
}
int main()
{
    long int x, i, j,ka, kb, kc, t, k, s=0;
    int potenze[6];
    Puntatore candidati, o, p=NULL, q;
    candidati=inizializza();
    printf("Signore, digiti un numero compreso tra -32767 e 32767 e il computer lo fattorizzerà!\n");
    scanf("%ld", &x);
    if (x<0)
    {
        x=-x;
        s=1;
    }
    /*ho pensato che sia inutile calcolarsi ogni volta 10^2, quindi me lo calcolo una volta per tutte
    Si assume che log(0)=-infinito in ogni compilatore*/
    for ( i = 0; i < log10(x)+1; i++)
    {
        potenze[i]=Potenza(10,i);
    }
    for ( j = 1; j < 10; j++)
    {
        for ( k = 1; k<= 10; k++)
        {
            if(  ((j*k)%10)==(x%10)  )
            {
                candidati=inserisci_in_testa(candidati, j, k);

            }
        }
    }
//la logica che c'è dietro l'algoritmo è che verifico se il prodotto tra le ultime cifre sia uguale alle ultime 
//cifre dell'input , se sì procedo.    
    for ( i = 1; i < log10(x); i++) 
    {
        o=candidati;
        q=candidati;
        while (o!=p)
        {
            t=0;
            for ( kb = 0; kb < 10; kb++)
            {
                for(ka = 0; ka < 10; ka++)
                {
                    if (((    (o->info1+potenze[i]*ka) * (o->info2+potenze[i]*kb)    )%potenze[i+1])==(x%(potenze[i+1])))
                    {
                        candidati=inserisci_in_testa(candidati,o->info1+potenze[i]*ka, o->info2+potenze[i]*kb);
                    }
                }
            }
            o->info1=0;
            o->info2=0;
            o=o->successivo;
        }
        p=q;
    }
    o=candidati;
    while (o!=NULL)
    {
        if (o->info1*o->info2!=x)
        {
            o->info1=0;
            o->info2=0;//in realtà non serve, è un'operazione inutile che ho lasciato per creare simmetria
        }
        o=o->successivo;
    }
    putchar('\n');
    stampalista(candidati, s);
    main();
}