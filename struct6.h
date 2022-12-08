#ifndef STRUCT6_H_INCLUDED
#define STRUCT6_H_INCLUDED
#include<stdbool.h>
#include<stdio.h>
#include<conio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
struct date
{
    int j;
    int m;
    int a;
};
typedef struct date DATE;
struct chambre
{
    int numero;
    int numetage;
    int type;
    float prix;
    bool ocup;
};
typedef struct chambre CHAMBRE;

struct service
{
    int id;
    char nom[20];
    float prix;
};
typedef struct service SERVICE;

struct client
{
    int id;
    char nom[50];
    char sexe[20];// male ou female
    char adress[40];
    int teleph;
    char email[35];
    char pays[20];
    char ville[40];
    float montant;
    int nbService;
    SERVICE* service;
};
typedef struct client CLIENT;
struct reserv
{
    int id;
    CHAMBRE chambre;
    CLIENT *client;// max 5 car on a max chambre a 5
    DATE dated;
    DATE datef;
    float montant;
    int durejour;
};
typedef struct reserv RESERV;

struct enregistrement
{
    CHAMBRE *ch;
    RESERV *res;
    SERVICE *ser;
};
typedef struct enregistrement ENREGISTREMENT;

struct service_classement
{
    int id;
    char nom[20];
    int nb_iteration;
};
typedef struct service_classement SERVICE_C;
//---------------------------------------------------------------------

int saisir_nb(char* ch)
{
    int n;
    printf("%s  ",ch);
    scanf("%d",&n);
    return n;
}

//-------------------------------
SERVICE_C* creation_service_C(SERVICE *ser,int n)
{
        SERVICE_C* ser_c;
        ser_c->id= ser->id;
        strcpy(ser_c->nom, ser->nom);
        ser_c->nb_iteration= n;
        return ser_c;
}





//----------------------------allocation------------------------------------------
SERVICE* malloc_service(int n)
{
     SERVICE *ser;
     ser=(SERVICE*)malloc(n*sizeof(SERVICE));
     return ser ;
}

CHAMBRE* malloc_chambre(int n)
{
     CHAMBRE *ch;
     ch=(CHAMBRE*)malloc(n*sizeof(CHAMBRE));
     return ch ;
}

RESERV* malloc_res(int n)
{
    RESERV *res;
    res=(RESERV*)malloc(n*sizeof(RESERV));
    return res;
}

CLIENT* malloc_client(int n )
{
    CLIENT *c;
    c=(CLIENT*)malloc(n*sizeof(CLIENT));
    return c;
}
//--------------------- saisie des structures ---------------
SERVICE saisir_service()
{
        SERVICE ser;
        printf("\ndonner la identifiant du service    ");
        scanf("%d",&ser.id);
        printf("donner le nom du service  ");
        scanf("%s",&ser.nom);
        printf("donner le prix du service en DT  ");
        scanf("%f",&ser.prix);
        return ser;
}

//--------------------------------
CHAMBRE saisir_chambre()
{
        CHAMBRE ch;
        printf("\ndonner la numero de chambre    ");
        scanf("%d",&ch.numero);
        printf("numero d'etage  ");
        scanf("%d",&ch.numetage);
        printf("donner le type de chambre    ");
        scanf("%d",&ch.type);
        printf("donner le prix de la chambre en DT  ");
        scanf("%f",&ch.prix);
        ch.ocup=false;
        return ch;
}
//------------------------------------

//-------------------------------------
CLIENT saisir_client(SERVICE* ser ,int duree)
{
    CLIENT c;
    int n,i,j,m,s;
    bool test;

    printf("donner id   ");
    scanf("%d",&c.id);
    printf("donner le nom de client    ");
    scanf("%s",&c.nom);
    printf("donner le sexe    ");
    scanf("%s",&c.sexe);
    printf("donner l adresse de client   ");
    scanf("%s",&c.adress);
    printf("doner le telephone    ");
    scanf("%d",&c.teleph);
    printf("donner son email   ");
    scanf("%s",&c.email);
    printf("donner son pays   ");
    scanf("%s",&c.pays);
    printf("donner son ville   ");
    scanf("%s",&c.ville);

    n=saisir_nb("donner le nombre des services a ajouter pour ce client");
    c.nbService = n;
    c.service= malloc_service(n);
    for(i=0;i<n;i++)
        {
            test=false;
            while(test == false)
            {
                 printf("saisir le id du service  %d ",i+1 );
                 scanf("%d",&m);
                 s=0;
                 for(j=0;j<sizeof(ser);j++)
                 {
                    if((ser+j)->id == m)
                    {
                         test=true;
                         (c.service+i)->id=m;
                         strcpy((c.service+i)->nom,(ser+j)->nom);
                         (c.service+i)->prix=(ser+j)->prix;
                         s=s+((c.service+i)->prix)*duree;

                     }
                 }
                 if(test == false)
                    {
                        printf("le service n'existe pas  \n");
                    }
             }
         }
    c.montant=s;
    return c;
};
//------------------------------------------

DATE saisir_date()
{
    DATE d;
    scanf("%d%d%d",&d.j,&d.m,&d.a);
    return d;
};





//----------------------------------------------------------------
RESERV saisir_reservation(CHAMBRE* ch,SERVICE* ser)
{
        RESERV res;
        bool test1,test2;
        int m,j,i,s;
        printf("donner la numero de resrvation  ");
        scanf("%d",&res.id);
        printf("donner la dure    ");
        scanf("%d",&res.durejour);
        printf("donner la date de debut jour/mois/annee      ");
        res.dated=saisir_date();
        printf("donner la date de fin jour/mois/annee    ");
        res.datef=saisir_date();
        test1=false;
        test2=true;
        while((test1 == false) || (test2 == true))
        {
             printf("donner le numero du chambre");
             scanf("%d",&m);
             for(j=0;j<sizeof(ch);j++)
             {
                if((ch+j)->numero == m)
                {
                    test1=true;
                    if((ch+j)->ocup == true)
                    {
                        printf("la chambre est reservé actuellement \n");
                        break;
                    }
                    else
                    {
                     test2=false;
                     res.chambre.numero=m;
                     res.chambre.numetage=(ch+j)->numetage;
                     res.chambre.type=(ch+j)->type;
                     res.chambre.prix=(ch+j)->prix;
                     res.chambre.ocup= true;
                    }
                  }
                }
                if(test1 == false)
                {
                    printf("la chambre n'existe pas \n");
                }
        }


        res.client=malloc_client(res.chambre.type);
        s=0;
        for(j=0;j<(res.chambre.type);j++)
        {
            printf("pour le client de numero  %d ",j+1 );
            *(res.client+j)=saisir_client(ser,res.durejour);
            s=s+(res.client+j)->montant;
        }
        s=s+res.durejour*res.chambre.prix;
        res.montant=s;

        return res;
}
//-----------------------------------------------------------------






//----------------------------affichage des structures -------------------------------------
void afficher_chambre(CHAMBRE* ch)
{
    printf("le numero du chambre est %d \n ", ch->numero);
    printf("l'etage du chambre est %d \n", ch->numetage);
    printf("le type du chambre est %d \n", ch->type);
    printf("le prix du chambre est %.2f DT\n", ch->prix);
    if(ch->ocup == false)
        printf("la chambre est libre \n");
    else
        printf("la chambre est occupé \n");

}
//------------------------------------
void afficher_service(SERVICE* ser)
{
    printf("le id du service est %d \n ", ser->id);
    printf("le nom du service est %s \n", ser->nom);
    printf("le prix du service est %.2f DT\n", ser->prix);
}


//------------------------------------
void afficher_client(CLIENT* cl)
{
    int j;
    printf("l'id du client est %d \n", cl->id);
    printf("le nom du client est %s \n", cl->nom);
    printf("le sexe du client est %s \n", cl->sexe);
    printf("l'adress du client est %s \n", cl->adress);
    printf("le numero de telephone du client est %d \n", cl->teleph);
    printf("le pays du client est %s \n", cl->pays);
    printf("la ville du client est %s \n", cl->ville);
    printf("les services utilisé sont:");
     for(j=0;j<cl->nbService;j++)
        {
            printf(" nom du service :%s  et son prix est %.2f DT\n",(cl->service+j)->nom ,(cl->service+j)->prix);
        }
}
//----------------------------------------
void afficher_reservation(RESERV* res)
{
            int j;
            printf("l'ID de la reservation est %d ", res->id);
            printf("le numero de la chambre %d", res->chambre.numero);
            for(j=0;j<res->chambre.type;j++)
            {
                afficher_client(res->client+j);
            }
            printf("la date de debut du reservation est %d/%d/%d \n", res->dated.a,res->dated.m,res->dated.j);
            printf("la date de fin du reservation est %d/%d/%d \n", res->datef.a,res->datef.m,res->datef.j);

            printf("le montant a payer est %.2f DT \n",res->montant);
            printf("la duree du reservation est %d \n",res->durejour);
}
//----------------------------------------affichage des occurences de services et le meilleur service (Niveau 2) ----------
char* meilleur_service_reservation(int *tab,int p,ENREGISTREMENT eng,RESERV* res)
{
    int i,j,k,num,maxi;
    for(i=0;i<p;i++)
        {
            *(tab+i) = 0;
        }
    for(k=0;k<res->chambre.type;k++)
    {
        for(i=0;i<p;i++)
            {
                for(j=0;j<((res->client+k)->nbService);j++)
                    {
                        if(((res->client+k)->service+j)->id == i+1)
                            {
                                *(tab+i) = *(tab+i) +1;
                            }
                    }
            }
    }
    maxi=0;
    num=0;
    for(i=0;i<p;i++)
    {
        if(*(tab+i)>maxi)
        {
            maxi = *(tab+i);
            num = i;
        }
    }
    return((eng.ser+num)->nom);
}
//------------ fonction au niveau 1 --------------------------------
char* meilleur_service_total(int *tab,int p,int r,ENREGISTREMENT eng,int *maxi)
{
    int tab1[20],i,j,num;
    char *str;

    for(i=0;i<p;i++)
        {
            *(tab+i) = 0;
        }
    for(i=0;i<r;i++)
    {
        str = meilleur_service_reservation(tab1,p,eng,eng.res+i);
        for(j=0;j<p;j++)
        {
            *(tab+j) = *(tab+j) + *(tab1+j);
        }
    }
    *maxi=0;
    num=0;
    for(i=0;i<p;i++)
    {
        if(*(tab+i)>*maxi)
        {
            *maxi = *(tab+i);
            num = i;
        }
    }
    return((eng.ser+num)->nom);
}


#endif // STRUCT6_H_INCLUDED
