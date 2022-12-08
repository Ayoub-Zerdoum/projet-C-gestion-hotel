#include<stdio.h>
#include<conio.h>
#include<stdbool.h>
#include<stdlib.h>
#include <C:\Users\Ayoub Zerdoum\Desktop\projet C\struct6.h>

void main ()
{
    ENREGISTREMENT eng;
    int n,p,i,j,r,x,z,y,k,w,num,xx;

//-------------------------------------------------------------------------------------------
    n=saisir_nb("donner le nombre des chambres a ajouter");
    eng.ch= malloc_chambre(n);
    for(i=0;i<n;i++)//Remplisage de chambre
    {
        *(eng.ch+i)= saisir_chambre();
        printf("\n*******************************\n");
    }
//-----------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------
    p=saisir_nb("donner le nombre des services a ajouter");
    eng.ser= malloc_service(p);
    for(i=0;i<p;i++)//Remplisage de service
    {
        *(eng.ser+i)= saisir_service();
        printf("\n*******************************\n");
    }
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
    r=saisir_nb("donner le nombre des reservation a ajouter");
    eng.res=malloc_res(r);
    for(i=0;i<r;i++)//Remplisage de reservation
    {
        *(eng.res+i)= saisir_reservation(eng.ch,eng.ser);
        (eng.ch+i)->ocup=true;

        printf("\n*******************************\n");

    }
//------------------------------affichage des occurences de services et le meilleur service ------------------------------------------
int tab[20],maxi;
char *str;

str = meilleur_service_total(tab,p,r,eng,&maxi);
printf("le meilleur service est %s avec %d occurence \n",str,maxi);


//--------------------------------tableau d'adresses de structures-----------------------------------------

    SERVICE_C **tab1;
    SERVICE_C *ser_c;
    tab1=(SERVICE_C**)malloc(p*sizeof(SERVICE_C*));
    for(i=0;i<p;i++)
        *(tab1+i)=(SERVICE_C*)malloc(1*sizeof(SERVICE_C));
    for(i=0;i<p;i++)
    {

        ser_c= creation_service_C(eng.ser+i,*(tab+i));
        *(*(tab1+i)) = *ser_c;
    }

for(i=0;i<p;i++)
{
    printf("%d \t", (*(tab1+i))->id);
    printf("%s \t", (*(tab1+i))->nom);
    printf("%d \t", (*(tab1+i))->nb_iteration);
    printf("\n");
}



//-----------------------------------------------------------------------------------------
    //affichage d'une chambre
    do{
    printf("donner le numero du chambre a afficher     ");
    scanf("%d",&num);
    k=0;
    for (i=0;i<sizeof(eng.ch);i++)
    {
        if(num==(eng.ch+i)->numero)
        {k=1;
            afficher_chambre(eng.ch+i);
        }
    }
    if (k==0) printf("erreur / cette numero faute\n");
    printf("pour rechercher un autre chambre taper 1   ");
    scanf("%d",&xx);
    }while(xx==1);
    printf("\n//////////////////////\n");
//-----------------------------------------------------------------------------------------
//affichage d'un service
    do{
    printf("donner le numero du service a afficher     ");
    scanf("%d",&num);
    k=0;
    for (i=0;i<sizeof(eng.ser);i++)
    {
        if(num==(eng.ser+i)->id)
        {
            k=1;
            afficher_service(eng.ser+i);
            break;
        }
    }
    if (k==0)
        printf("erreur / cette numero faute\n");
    printf("pour rechercher un autre service taper 1   ");
    scanf("%d",&xx);
    }while(xx==1);
    printf("\n//////////////////////\n");

//-----------------------------------------------------------------------------------------
    //affichage d'une reservation
    do{
    printf("saisir le numero de reservation afficher   \n");
    scanf("%d",&num);
    k=0;
    for(i=0;i<sizeof(eng.res);i++)
    {
        if(num==(eng.res+i)->id)
        {
            k==1;
            afficher_reservation(eng.res+i);
            break;
        }

    }
    if (k==0)
        printf("erreur / cette numero faute\n");
    printf("pour rechercher un autre reservattion taper 1   ");
    scanf("%d",&xx);
    }while(xx==1);
//-----------------------------------------------------------------------------------------

    getch();
}
