#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct date {
    int j,m,a;
} date;
typedef struct {
    int code_clt;
    char nom[20],prenom[20];
    int telephone;
} client;
typedef struct {
    int code_prd;
    char nom_prd[20];
    float prix_achat,prix_vente;
} produit;
typedef struct {
    int code_clt;
    int code_prd,quantite;
    date d;
} acheter;
typedef struct list1 {
    client clt;
    struct list1 *suivant;
} list1;
typedef struct list2 {
    produit prd;
    struct list2 *suivant;
} list2;
typedef struct list3 {
    acheter acht;
    struct list3 *suivant;
} list3;
/******************************************** fonction de recherche du code de client dans la liste ************************************************/
int rech_clt(int code_clt,list1 *l1) {
    if(l1==NULL) {
        return 0;
    }
    else {
        list1 *tmp=l1;
        while(tmp!=NULL) {
            if(tmp->clt.code_clt==code_clt)
                return 1;
            tmp=tmp->suivant;
        }
        return -1;
    }
}
/************************************************* Ajouter un client au debut de la liste **********************************************************/
list1* ajt_clt_debut(list1 *l1) {
    list1 *nv=(list1*)malloc(sizeof(list1));
    printf("Entrer le code du client: ");
    scanf("%d",&nv->clt.code_clt);
    if(rech_clt(nv->clt.code_clt,l1)==1) {
    	puts("\n======================");
        printf("Ce client existe deja\n");
        puts("======================\n\n\n");
        return l1;
    }
    printf("\nEntrer le nom du client: ");
    scanf("%s",nv->clt.nom);
    printf("\nEntrer le prenom du client: ");
    scanf("%s",nv->clt.prenom);
    printf("\nEntrer le numero de telephone: ");
    scanf("%d",&nv->clt.telephone);
    nv->suivant=l1;
    printf("\n==>Operation terminee avec succes\n");
    return  nv;
}
/********************************************************** Ajouter un client a la fin de la liste ************************************************/
list1 *ajt_clt_fin(list1 *l1) {
    list1* nv=(list1*) malloc(sizeof(list1));
    printf("Entrer le code du client: ");
    scanf("%d",&nv->clt.code_clt);
    if(rech_clt(nv->clt.code_clt,l1)==1) {
    	puts("\n======================");
        printf("Ce code existe deja\n");
        puts("======================\n\n\n");
        return l1;
    }
    printf("\nEntrer le nom du client: ");
    scanf("%s",nv->clt.nom);
    printf("\nEntrer le prenom du client: ");
    scanf("%s",nv->clt.prenom);
    printf("\nEntrer le numero de telephone: ");
    scanf("%d",&nv->clt.telephone);
    nv->suivant=NULL;
    printf("\n==>Operation terminee avec succes\n");
    if(l1==NULL) return nv;
    else {
        list1 *tmp=l1;
        while(tmp->suivant!=NULL) tmp=tmp->suivant;
        tmp->suivant=nv;
        return l1;
    }
}
/******************************************************************************** Afficher les clients ************************************************/
void afficher_clt(list1* l1) {
    if(l1==NULL) {
        puts("\n======================");
        printf("Liste vide\n");
        puts("======================\n\n\n\n");
    }
    else {
        list1 *tmp=l1;
        printf ("la liste des client est:\n");
        puts("=======================================================================================================================");
        while(tmp!=NULL) {
            printf("Code de client: %d\t Nom de client: %s\t\t Prenom de client: %s\t Telephone: 0%d\n",tmp->clt.code_clt,tmp->clt.nom,tmp->clt.prenom,tmp->clt.telephone);
        	puts("=======================================================================================================================");
            tmp=tmp->suivant;
        }
    }
}
/********************************************************************************* Supprimer un client ************************************************/
list1 *supp_clt(list1 *l1) {
    int code_clt;
    if(l1==NULL) {
        puts("\n======================");
        printf("Liste vide\n");
        puts("======================\n\n\n\n");
        return l1;
    }
    printf("Entrer le code de client a supprimer: ");
    scanf("%d",&code_clt);
    if(rech_clt(code_clt,l1)==-1) {
    	puts("\n======================");
    	printf("Ce code n'existe pas\n");
        puts("======================\n\n\n\n");
        return l1;
    }
    list1 *tmp1=l1;
    while(tmp1!=NULL) {
        if(tmp1->clt.code_clt==code_clt) {
            if(tmp1==l1) l1=l1->suivant;
            else {
                list1 *tmp2=l1;
                while(tmp2->suivant!=tmp1) tmp2=tmp2->suivant;
                tmp2->suivant=tmp1->suivant;
                free(tmp1);
            }
            puts("\n======================================");
            printf("Ce client est supprimee avec succes\n");
            puts("======================================\n\n\n");
            return l1;
        }
        tmp1=tmp1->suivant;
    }
}
/******************************************************************* Modifier un client ***************************************************************/
list1 *modifier_clt(list1 *l1,list3 *l3) {
    int code_clt,nv_code_clt;
    if(l1==NULL) {
    	puts("======================");
        printf("Liste vide\n");
        puts("======================\n\n\n");
        return l1;
    }
    printf("Enter la code de client que vous voulez modifier ses informations: ");
    scanf("%d",&code_clt);
    if(rech_clt(code_clt,l1)==-1) {
    	puts("\n=======================");
        printf("Ce client n'existe pas\n");
        puts("=======================\n\n\n");
        return l1;
    }
    else {
        list1 *tmp=l1;
        while(tmp->clt.code_clt!=code_clt) {
            tmp=tmp->suivant;
        }
        printf("Entrer la nouvelle code de client: ");
        scanf("%d",&nv_code_clt);
        if(rech_clt(nv_code_clt,l1)==1) {
        	puts("\n==================================");
            printf("Ce code associe a un autre client\n");
            puts("==================================\n\n\n\n");
            return l1;
        }
        tmp->clt.code_clt=nv_code_clt;
        printf("Entrer le nouveau nom  du client:");
        scanf("%s",tmp->clt.nom);
        printf("Entrer le nouveau prenom: ");
        scanf("%s",tmp->clt.prenom);
        printf("Entrer le nouveau numero de telephone: ");
        scanf("%d",&tmp->clt.telephone);
        list3 *tmp1=l3;		// Modification dans la liste des achats
        while(tmp1!=NULL){
        	if(tmp1->acht.code_clt==code_clt)
        		tmp1->acht.code_clt=nv_code_clt;
        	tmp1=tmp1->suivant;
		}
		printf("\n==>Operation terminee avec succes\n");
        return l1;
    }
}
/**************************************************** Rechercher un client par code de client **********************************************************/
void rechercher_code_clt(list1 *l1) {
    if(l1==NULL) {
    	puts("======================");
        printf("Liste vide\n");
        puts("======================\n\n\n");
        return ;
    }
    list1 *tmp=l1;
    int code_clt;
    printf("Entre le code du client: ");
    scanf("%d",&code_clt);
    while(tmp->clt.code_clt!=code_clt) {
        tmp=tmp->suivant;
        if(tmp==NULL) {
        	puts("\n======================");
            printf("Ce client n'existe pas\n");
            puts("======================\n\n\n\n");
            return;
        }
    }
    puts("=======================================================================================================================");
    printf("Code du client: %d\t Nom du client: %s\t\t Prenom du client: %s\t Telephone: 0%d\n",tmp->clt.code_clt,tmp->clt.nom,tmp->clt.prenom,tmp->clt.telephone);
    puts("=======================================================================================================================");
}
/******************************************************************* Rechercher un client par son nom ************************************************/
void rechercher_nom(list1 *l1) {
    if(l1==NULL) {
    	puts("\n======================");
        printf("Liste vide\n");
        puts("======================\n\n\n\n");
        return ;
    }
    list1 *tmp=l1;
    char nom[20];
    int i=0;
    printf("Entrer le nom du client: ");
    scanf("%s",nom);
    puts("=======================================================================================================================");
    while(tmp!=NULL) {
        if(strcmp(tmp->clt.nom,nom)==0) {
            printf("Code du client: %d\t Nom de client: %s\t\t Prenom de client: %s\t Telephone: 0%d\n",tmp->clt.code_clt,tmp->clt.nom,tmp->clt.prenom,tmp->clt.telephone);
        	puts("=======================================================================================================================");
        	i++;
        }
        tmp=tmp->suivant;
    }
    if (i==0) {
        puts("\n========================");
        printf("Ce client n'existe pas\n");
        puts("========================\n\n\n\n\n");
	}
}
/************************************************************* Rechercher un client par son prenom **************************************************/
void rechercher_prenom(list1 *l1) {
    if(l1==NULL) {
    	puts("\n======================");
        printf("Liste vide\n");
        puts("======================\n\n\n\n");
        return ;
    }
    list1 *tmp=l1;
    char prenom[20];
    int i=0;
    printf("Entrer le prenom du client: ");
    scanf("%s",prenom);
    puts("=======================================================================================================================");
    while(tmp!=NULL) {
        if(strcmp(tmp->clt.prenom,prenom)==0) {
            printf("Code du client: %d\t Nom de client: %s\t\t Prenom de client: %s\t Telephone: 0%d\n",tmp->clt.code_clt,tmp->clt.nom,tmp->clt.prenom,tmp->clt.telephone);
        	puts("=======================================================================================================================");
        	i++;
        }
        tmp=tmp->suivant;
    }
    if(i==0) {
        puts("\n=============================");
       	printf("Ce client n'existe pas\n");
       	puts("=============================\n\n\n\n");
    }
}
/************************************************** Rechercher un client par le numero de telephone ****************************************************/
void rechercher_telephone(list1 *l1) {
    if(l1==NULL) {
        puts("\n======================");
        printf("Liste vide\n");
        puts("======================\n\n\n\n");
        return ;
    }
    list1 *tmp=l1;
    int telephone,i=0;
    printf("Entrer le numero de telephone du client: ");
    scanf("%d",&telephone);
    puts("=======================================================================================================================");
    while(tmp!=NULL) {
        if(tmp->clt.telephone==telephone) {
            printf("Code du client: %d\t Nom de client: %s\t\t Prenom de client: %s\t Telephone: 0%d\n",tmp->clt.code_clt,tmp->clt.nom,tmp->clt.prenom,tmp->clt.telephone);
        	puts("=======================================================================================================================");
        	i++;
        }
        tmp=tmp->suivant;
    }
    if(i==0) {
    	puts("\n==============================");
       	printf("Ce client n'existe pas\n");
       	puts("==============================\n\n\n\n");
   	}
}
/**************************************************************************** Menu de recherche les clients ************************************************/
void  menu_rechercher_clt(list1* l1) {
    int choix;
a:
    do {
        system("cls");
        system("color 90");
        printf("============================================ Menu de recherche ========================================================\n");
        puts("=======================================================================================================================");
        printf("\t\t\t\t\t1- Rechercher par le code du client\n");
        printf("\t\t\t\t\t2- Rechercher par le nom du client\n");
        printf("\t\t\t\t\t3- Rechercher par le prenom du client\n");
        printf("\t\t\t\t\t4- Rechercher par le numero de telephone\n");
        printf("\t\t\t\t\t0- Annuller l'operation\n");
        puts("=======================================================================================================================");
        puts("======================");
        printf("Entrez votre choix: ");
        scanf("%d",&choix);
        puts("======================\n");
        switch(choix) {
        case 0:
            return;
            break;
        case 1:
            rechercher_code_clt(l1);
            break;
        case 2:
            rechercher_nom(l1);
            break;
        case 3:
            rechercher_prenom(l1);
            break;
        case 4:
            rechercher_telephone(l1);
            break;
        default:
            goto a;
        }
        printf("\n\n\n\n===========================================> ");
        system("Pause");
    } while(choix!=0);
}
/******************************************************* Enregistrer les client dans un fichier ************************************************************/
void enregistrer_clt(list1 *l1) {
	if(l1==NULL) {
    	puts("======================");
        printf("Liste vide\n");
        puts("======================\n\n\n");
        return ;
    }
    int code_clt,telephone;
    char nom[20],prenom[20];
    list1 *tmp=l1;
    FILE *p=fopen("client.txt","w");
    while(tmp!=NULL) {
        fprintf(p,"%d\n%s\n%s\n%d\n",tmp->clt.code_clt,tmp->clt.nom,tmp->clt.prenom,tmp->clt.telephone);
        tmp=tmp->suivant;
    }
    fclose(p);
	printf("\n==>Operation terminee avec succes\n");
}
/************************************************* Charger les information de fichier dans la liste *******************************************************/
list1* charger_clt(list1 *l1,FILE *p,int code_clt,char nom[20],char prenom[20],int telephone) {
    list1 *tmp1=l1;
    list1* nv=(list1*) malloc(sizeof(list1));
    nv->clt.code_clt=code_clt;
    strcpy(nv->clt.nom,nom);
    strcpy(nv->clt.prenom,prenom);
    nv->clt.telephone=telephone;
    nv->suivant=NULL;
    if(l1==NULL) return nv;
    else {
        list1 *tmp=l1;
        while(tmp->suivant!=NULL) tmp=tmp->suivant;
        tmp->suivant=nv;
        return l1;
    }
}
/************************************************************* Fonction de recherche du produit *********************************************************/
int rech_prd(int code_prd,list2 *l2) {
    if(l2==NULL) {
        return 0;
    }
    else {
        while(l2!=NULL) {
            if(l2->prd.code_prd==code_prd)
                return 1;
            l2=l2->suivant;
        }
        return -1;
    }
}
/************************************************************* Ajouter un produit au debut de la liste ************************************************/
list2* ajt_prd_debut(list2 *l2) {
    list2* nv=(list2*)malloc(sizeof(list2));
    printf("Entrer le code du produit: ");
    scanf("%d",&nv->prd.code_prd);
    if(rech_prd(nv->prd.code_prd,l2)==1) {
    	puts("\n======================");
        printf("Ce code existe deja\n");
        puts("======================\n\n\n");
        return l2;
    }
    printf("\nEntrer le nom de produit: ");
    scanf("%s",nv->prd.nom_prd);
    printf("\nEntrer le prix d'achat: ");
    scanf("%f",&nv->prd.prix_achat);
    printf("\nEntrer le prix de vente: ");
    scanf("%f",&nv->prd.prix_vente);
    nv->suivant=l2;
    printf("\n==>Operation terminee avec succes\n");
    return  nv;
}
/************************************************************** Ajouter un produit a la fin de la  ************************************************/
list2 *ajt_prd_fin(list2 *l2) {
    list2* nv=(list2*) malloc(sizeof(list2));
    printf("Entrer le code du produit: ");
    scanf("%d",&nv->prd.code_prd);
    if(rech_prd(nv->prd.code_prd,l2)==1) {
    	puts("\n======================");
        printf("Ce code existe deja:\n");
        puts("======================\n\n\n");
        return l2;
    }
    printf("\nEntrer le nom de produit: ");
    scanf("%s",nv->prd.nom_prd);
    printf("\nEntrer le prix d'achat: ");
    scanf("%f",&nv->prd.prix_achat);
    printf("\nEntrer le prix d'vente: ");
    scanf("%f",&nv->prd.prix_vente);
    nv->suivant=NULL;
    if(l2==NULL) return nv;
    else {
        list2 *tmp=l2;
        while(tmp->suivant!=NULL) tmp=tmp->suivant;
        tmp->suivant=nv;
        printf("\n==>Operation terminee avec succes\n");
        return l2;
    }
}
/**************************************************************** Afficher les produits ****************************************************************/
void afficher_prd(list2* l2) {
    if(l2==NULL) {
        puts("\n======================");
        printf("Liste vide\n");
        puts("======================\n\n\n\n");
    }
    else {
        list2 *tmp=l2;
        printf ("la liste des produits est:\n");
        while(tmp!=NULL) {
            puts("=======================================================================================================================");
            printf("Code du produit: %d\t Nom du produit: %s\t\t Prix d'achat: %.2f\t Prix de vente: %.2f\n",tmp->prd.code_prd,tmp->prd.nom_prd,tmp->prd.prix_achat,tmp->prd.prix_vente);
            puts("=======================================================================================================================");
            tmp=tmp->suivant;
        }
    }
}
/************************************************************************ Supprimer un produit *******************************************************/
list2 *supp_prd(list2 *l2) {
    int code_prd;
    if(l2==NULL) {
        puts("\n===============");
        printf("Liste vide\n");
        puts("===============\n\n\n\n");
        return l2;
    }
    printf("Entrer le code de produit a supprimer: ");
    scanf("%d",&code_prd);
    if(rech_prd(code_prd,l2)==-1) {
    	puts("\n===================================");
        printf("Code du produit n'existe pas\n");
        puts("===================================\n\n\n");
        return l2;
    }
    list2 *tmp1=l2;
    while(tmp1!=NULL) {
        if(tmp1->prd.code_prd==code_prd) {
            if(tmp1==l2) l2=l2->suivant;
            else {
                list2 *tmp2=l2;
                while(tmp2->suivant!=tmp1) tmp2=tmp2->suivant;
                tmp2->suivant=tmp1->suivant;
                free(tmp1);
            }
            puts("\n======================================");
            printf("Ce produit est supprimee avec succes\n");
            puts("======================================\n\n\n");
            return l2;
        }
        tmp1=tmp1->suivant;
    }
}
/****************************************************************** Modifier un produit ************************************************************/
list2 *modifier_prd(list2 *l2,list3 *l3) {
    int code_prd,nv_code_prd;
    if(l2==NULL) {
        puts("\n======================");
        printf("Liste vide\n");
        puts("======================\n\n\n\n");
        return l2;
    }
    printf("Enter la code de produit que vous voulez modifier ses informations: ");
    scanf("%d",&code_prd);
    if(rech_prd(code_prd,l2)==-1) {
    	puts("\n==========================");
        printf("Ce produit n'existe pas\n");
        puts("==========================\n\n\n\n");
        return l2;
    }
    else {
        list2 *tmp=l2;
        while(tmp->prd.code_prd!=code_prd)
            tmp=tmp->suivant;
        printf("Entrer la nouvelle code de produit: ");
        scanf("%d",&nv_code_prd);
        if(rech_prd(nv_code_prd,l2)==1) {
        	puts("\n======================================");
            printf("Ce code associe a un autre produit\n");
            puts("======================================\n\n\n\n");
            return l2;
        }
        tmp->prd.code_prd=nv_code_prd;
        printf("Entrer le nouveau nom  du produit:");
        scanf("%s",tmp->prd.nom_prd);
        printf("Entrer le nouveau prix d'achat: ");
        scanf("%f",&tmp->prd.prix_achat);
        printf("Entrer le nouveau quantite: ");
        scanf("%f",&tmp->prd.prix_vente);
        list3 *tmp1=l3;
        while(tmp1!=NULL){
        	if(tmp1->acht.code_prd==code_prd)
        		tmp1->acht.code_prd=nv_code_prd;
        	tmp1=tmp1->suivant;
		}
		printf("\n==>Operation terminee avec succes\n");
        return l2;
    }
}
/********************************************************** Rechercher un produit par code de produit ************************************************/
void rechercher_code_prd(list2 *l2) {
    if(l2==NULL) {
        puts("\n==================");
        printf("Liste vide\n");
        puts("==================\n\n\n\n");
        return ;
    }
    list2 *tmp=l2;
    int code_prd;
    printf("Entre le code du produit: ");
    scanf("%d",&code_prd);
    while(tmp->prd.code_prd!=code_prd) {
        tmp=tmp->suivant;
        if(tmp==NULL) {
        	puts("======================================");
            printf("Ce produit n'existe pas\n");
            puts("======================================\n\n\n\n");
            return;
        }
    }
    puts("=======================================================================================================================");
    printf("Code du produit: %d\t Nom du produit: %s\t\t Prix d'achat: %f\t Prix d'vente: %f\n ",tmp->prd.code_prd,tmp->prd.nom_prd,tmp->prd.prix_achat,tmp->prd.prix_vente);
    puts("=======================================================================================================================\n\n\n\n");
}
/********************************************************** Rechercher un produit par nom de produit ************************************************/
void rechercher_nom_prd(list2 *l2) {
    if(l2==NULL) {
        puts("\n======================");
        printf("Liste vide\n");
        puts("======================\n\n\n\n");
        return ;
    }
    list2 *tmp=l2;
    char nom_prd[20];
    int i=0;
    printf("Entrer le nom du produit: ");
    scanf("%s",nom_prd);
    puts("============================================================================================================");
    while(tmp!=NULL) {
        if(strcmp(tmp->prd.nom_prd,nom_prd)==0) {
            printf("Code du produit: %d\t Nom de produit: %s\t\t Prix d'achat: %f\t Prix de vente: %f\n",tmp->prd.code_prd,tmp->prd.nom_prd,tmp->prd.prix_achat,tmp->prd.prix_vente);
            puts("============================================================================================================");
            i++;
        }
        tmp=tmp->suivant;
    }
    if(i==0) {
    	puts("\n=============================");
        printf("Ce produit n'existe pas\n");
        puts("=============================\n");
    }
}
/******************************************************** Rechercher un produit par prix d'achat ************************************************************/
void rechercher_prix_achat(list2 *l2) {
    if(l2==NULL) {
        puts("\n======================");
        printf("Liste vide\n");
        puts("======================\n\n\n\n");
        return ;
    }
    list2 *tmp=l2;
    float prix_achat;
    int i=0;
    printf("Entrer le prix d'achat du produit: ");
    scanf("%f",&prix_achat);
    puts("============================================================================================================");
    while(tmp!=NULL) {
        if(tmp->prd.prix_achat==prix_achat) {
            printf("Code du produit: %d\t Nom du produit: %s\t\t Prix d'achat: %f\t Prix de vente: %f\n",tmp->prd.code_prd,tmp->prd.nom_prd,tmp->prd.prix_achat,tmp->prd.prix_vente);
            puts("============================================================================================================");
            i++;
        }
        tmp=tmp->suivant;
    }
    if(i==0) {
    		puts("\n=========================================");
       		printf("Ce produit n'existe pas\n");
        	puts("=========================================\n\n\n\n");
    	}
}
/****************************************************** Rechercher un produit par prix d'vente ************************************************************/
void rechercher_prix_vente(list2 *l2) {
    if(l2==NULL) {
        puts("\n======================");
        printf("Liste vide\n");
        puts("======================\n\n\n\n");
        return ;
    }
    list2 *tmp=l2;
    float prix_vente;
    int i=0;
    printf("Entrer le prix d'achat du produit: ");
    scanf("%f",&prix_vente);
    puts("============================================================================================================");
    while(tmp!=NULL) {
        if(tmp->prd.prix_vente==prix_vente) {
            printf("Code du produit: %d\t Nom de produit: %s\t\t Prix d'achat: %f\t Prix de vente: %f\n",tmp->prd.code_prd,tmp->prd.nom_prd,tmp->prd.prix_achat,tmp->prd.prix_vente);
            puts("============================================================================================================");
            i++;
        }
        tmp=tmp->suivant;
    }
    if(i==0) {
    	puts("======================================");
        printf("Ce produit n'existe pas\n");
        puts("======================================\n\n\n\n");
	}
}
/********************************************************************** Menu de recherche les produits ************************************************/
void menu_recherche_prd(list2* l2) {
    int choix;
a:
    do {
        system("cls");
        system("color 90");
        printf("============================================ Menu de recherche ========================================================\n");
        puts("=======================================================================================================================");
        printf("\t\t\t\t\t1- Rechercher par le code du produit\n");
        printf("\t\t\t\t\t2- Rechercher par le nom du produit\n");
        printf("\t\t\t\t\t3- Rechercher par le prix d'achat du produit\n");
        printf("\t\t\t\t\t4- Rechercher par le prix de vente du produit\n");
        printf("\t\t\t\t\t0- Annuller l'operation\n");
        puts("=======================================================================================================================");
        puts("======================");
        printf("Entrez votre choix: ");
        scanf("%d",&choix);
        puts("======================\n");
        switch(choix) {
        case 0:
            return;
            break;
        case 1:
            rechercher_code_prd(l2);
            break;
        case 2:
            rechercher_nom_prd(l2);
            break;
        case 3:
            rechercher_prix_achat(l2);
            break;
        case 4:
            rechercher_prix_vente(l2);
            break;
        default:
            goto a;
        }
        printf("\n\n\n\n===========================================> ");
        system("Pause");
    } while(choix!=0);
}
/************************************************************* Enregistrer les produit dans un fichier *************************************************/
void enregistrer_prd(list2 *l2) {
	if(l2==NULL) {
    	puts("====================");
        printf("Liste vide\n");
        puts("====================\n\n\n");
        return;
    }
    list2 *tmp=l2;
    FILE *p=fopen("produit.txt","w");
    while(tmp!=NULL) {
        fprintf(p,"%d\n%s\n%f\n%f\n",tmp->prd.code_prd,tmp->prd.nom_prd,tmp->prd.prix_achat,tmp->prd.prix_vente);
        tmp=tmp->suivant;
    }
    fclose(p);
	printf("\n==>Operation terminee avec succes\n");
}
/***************************************** Charger les information de fichier de produits dans la liste ****************************************************/
list2* charger_prd(list2 *l2,FILE *p,int code_prd,char nom_prd[20],float prix_achat,float prix_vente) {
    list2 *tmp1=l2;
    list2* nv=(list2*) malloc(sizeof(list2));
    nv->prd.code_prd=code_prd;
    strcpy(nv->prd.nom_prd,nom_prd);
    nv->prd.prix_achat=prix_achat;
    nv->prd.prix_vente=prix_vente;
    nv->suivant=NULL;
    if(l2==NULL) return nv;
    else {
        list2 *tmp=l2;
        while(tmp->suivant!=NULL) tmp=tmp->suivant;
        tmp->suivant=nv;
        return l2;
    }
}
/****************************************************************** Ajouter un achat au debut de la liste ************************************************/
list3* ajt_achat_debut(list3 *l3,list1 *l1,list2 *l2) {
    list3* nv=(list3*)malloc(sizeof(list3));
    printf("Entrer le code de client: ");
    scanf("%d",&nv->acht.code_clt);
    if(rech_clt(nv->acht.code_clt,l1)!=1) {
    	puts("\n===========================================");
        printf("Code n'existe pas dans la liste des client\n");
        puts("===========================================\n\n\n");
        return l3;
    }
    printf("\nEntrer le code de produit: ");
    scanf("%d",&nv->acht.code_prd);
    if(rech_prd(nv->acht.code_prd,l2)!=1) {
    	puts("\n===========================================");
        printf("Ce produit n'existe pas\n");
        puts("===========================================\n\n\n");
        return l3;
    }
    printf("\nEntrer la date d'achat(jour-mois-annee): ");
    scanf("%d%d%d",&nv->acht.d.j,&nv->acht.d.m,&nv->acht.d.a);
    printf("\nEntrer la quantite: ");
    scanf("%d",&nv->acht.quantite);
    nv->suivant=l3;
    printf("\n==>Operation terminee avec succes\n");
    return  nv;
}
/*************************************************************** Ajouter un achat a la fin de la liste ************************************************/
list3 *ajt_achat_fin(list3 *l3,list1 *l1,list2 *l2) {
    list3* nv=(list3*) malloc(sizeof(list3));
    printf("Entrer le code de client: ");
    scanf("%d",&nv->acht.code_clt);
    if(rech_clt(nv->acht.code_clt,l1)!=1) {
    	puts("\n===========================================");
        printf("Code n'existe pas dans la liste des client\n");
        puts("===========================================\n\n\n");
        return l3;
    }
    printf("\nEntrer le code de produit: ");
    scanf("%d",&nv->acht.code_prd);
    if(rech_prd(nv->acht.code_prd,l2)!=1) {
    	puts("\n===========================================");
        printf("Ce produit n'existe pas\n");
        puts("===========================================\n\n\n");
        return l3;
    }
    printf("\nEntrer la date d'achat(jour-mois-annee): ");
    scanf("%d%d%d",&nv->acht.d.j,&nv->acht.d.m,&nv->acht.d.a);
    printf("\nEntrer la quantite: ");
    scanf("%d",&nv->acht.quantite);
    nv->suivant=NULL;
    if(l3==NULL) return nv;
    else {
        list3 *tmp=l3;
        while(tmp->suivant!=NULL) tmp=tmp->suivant;
        tmp->suivant=nv;
        printf("\n==>Operation terminee avec succes\n");
        return l3;
    }
}
/******************************************************************** Afficher les achats ************************************************************/
void afficher_achat(list3* l3) {
    if(l3==NULL) {
        puts("\n===================");
        printf("Liste vide\n");
        puts("===================\n\n\n\n");
    }
    else {
        list3 *tmp=l3;
        printf ("La liste des achats est:\n");
        while(tmp!=NULL) {
            puts("======================================================================================================================");
            printf("Code de client: %d\t Code de produit: %d\t\t Date d'achat: %d/%d/%d\t\t Quantite: %d\n",tmp->acht.code_clt,tmp->acht.code_prd,tmp->acht.d.j,tmp->acht.d.m,tmp->acht.d.a,tmp->acht.quantite);
            puts("======================================================================================================================");
            tmp=tmp->suivant;
        }
    }
}
/************************************************************************ Supprimer un achat **********************************************************/
list3 *supp_achat(list3 *l3) {
    int code_clt,code_prd,i=0;
    if(l3==NULL) {
        puts("\n======================");
        printf("Liste vide\n");
        puts("======================\n\n\n\n");
        return l3;
    }
    printf("Entrer le code de client pour supprimer ses achats: ");
    scanf("%d",&code_clt);
    printf("Entrer le code de produit a supprimer: ");
    scanf("%d",&code_prd);
    list3 *tmp1=l3;
    while(tmp1!=NULL) {
        if(tmp1->acht.code_clt==code_clt && tmp1->acht.code_prd==code_prd) {
            if(tmp1==l3) l3=l3->suivant;
            else {
                list3 *tmp2=l3;
                while(tmp2->suivant!=tmp1) tmp2=tmp2->suivant;
                tmp2->suivant=tmp1->suivant;
                free(tmp1);
            }
            i++;
            puts("\n======================================");
            printf("%d achats est supprimee avec succes\n",i);
            puts("======================================\n\n\n");
        }
        tmp1=tmp1->suivant;
    }
    if(i==0) {
    	puts("\n==========================");
        printf("Cette achat n'existe pas\n");
        puts("==========================\n\n\n\n\n");
        
        return l3;
    }
    return l3;
}
/**************************************************************************** Modifier un achat ************************************************************/
list3 *modifier_achat(list3 *l3) {
    int code_clt,code_prd;
    if(l3==NULL) {
        puts("\n======================");
        printf("Liste vide\n");
        puts("======================\n\n\n\n");
        return l3;
    }
    else {
        printf("Enter la code de client que vous voulez modifier ses achats: ");
        scanf("%d",&code_clt);
        list3 *tmp=l3;
        while(tmp->acht.code_clt!=code_clt) {
            tmp=tmp->suivant;
            if(tmp==NULL) {
            	puts("\n=====================");
                printf("Ce code n'existe pas\n");
                puts("=====================\n\n\n\n");
                return l3;
            }
        }
        printf("Enter la code de produit de client que vous voulez modifier ses achats: ");
        scanf("%d",&code_prd);
        tmp=l3;
        while(tmp->acht.code_prd!=code_prd) {
            tmp=tmp->suivant;
            if(tmp==NULL) {
                puts("\n=====================");
                printf("Ce code n'existe pas\n");
                puts("=====================\n\n\n\n");
                return l3;
            }
        }
        printf("Entrer la nouvelle code de client: ");
        scanf("%d",&tmp->acht.code_clt);
        printf("Entrer le nouveau code  du produit:");
        scanf("%d",&tmp->acht.code_prd);
        printf("Entrer le nouveau date d'achat(jj/mm/aaaa): ");
        scanf("%d%d%d",&tmp->acht.d.j,&tmp->acht.d.m,&tmp->acht.d.a);
        printf("Entrer le nouveau quantite: ");
        scanf("%d",&tmp->acht.quantite);
        printf("\n==>Operation terminee avec succes\n");
        return l3;
    }
}
/*************************************************** Rechercher un achat par code de client ************************************************************/
void rechercher_achat_code_clt(list3 *l3) {
    if(l3==NULL) {
        puts("\n====================");
        printf("Liste vide\n");
        puts("====================\n\n\n\n");
        return ;
    }
    list3 *tmp=l3;
    int code_clt,i=0;
    printf("Entrer le code du client: ");
    scanf("%d",&code_clt);
    puts("============================================================================================================");
    while(tmp!=NULL) {
        if(tmp->acht.code_clt==code_clt) {
            printf("Code du client: %d\t Code du produit: %d\t\t Date d'achat: %d/%d/%d\t\t Quantite: %d\n",tmp->acht.code_clt,tmp->acht.code_prd,tmp->acht.d.j,tmp->acht.d.m,tmp->acht.d.a,tmp->acht.quantite);
            puts("============================================================================================================");
            i++;
        }
        tmp=tmp->suivant;
    }
    if(i==0) {
    	puts("\n============================");
       	printf("Cette achat  n'existe pas\n");
       	puts("============================\n\n\n\n");
    }
}
/********************************************************** Rechercher un achat par code de produit ************************************************/
void rechercher_achat_code_prd(list3 *l3) {
    if(l3==NULL) {
        puts("\n====================");
        printf("Liste vide\n");
        puts("====================\n\n\n\n");
        return ;
    }
    list3 *tmp=l3;
    int code_prd,i=0;
    printf("Entrer le code du client: ");
    scanf("%d",&code_prd);
    puts("============================================================================================================");
    while(tmp!=NULL) {
        if(tmp->acht.code_prd==code_prd) {
            printf("Code du client: %d\t Code du produit: %d\t\t Date d'achat: %d/%d/%d\t\t Quantite: %d\n",tmp->acht.code_clt,tmp->acht.code_prd,tmp->acht.d.j,tmp->acht.d.m,tmp->acht.d.a,tmp->acht.quantite);
            puts("============================================================================================================");
            i++;
        }
        tmp=tmp->suivant;
    }
    if(i==0) {
    		puts("\n================================");
        	printf("Cette achat  n'existe pas\n");
        	puts("================================\n\n\n\n");
    	}
}
/************************************************ Rechercher un achat par date d'achat ************************************************************/
void rechercher_achat_date(list3 *l3) {
    if(l3==NULL) {
        puts("\n====================");
        printf("Liste vide\n");
        puts("====================\n\n\n\n");
        return ;
    }
    list3 *tmp=l3;
    int j,m,a;
    int i=0;
    printf("Entrer la date d'achat: ");
    scanf("%d%d%d",&j,&m,&a);
    puts("============================================================================================================");
    while(tmp!=NULL) {
        if(tmp->acht.d.j==j && tmp->acht.d.m==m && tmp->acht.d.a==a) {
            printf("Code du client: %d\t Code du produit: %d\t\t Date d'achat: %d/%d/%d\t\t Quantite: %d\n",tmp->acht.code_clt,tmp->acht.code_prd,tmp->acht.d.j,tmp->acht.d.m,tmp->acht.d.a,tmp->acht.quantite);
            puts("============================================================================================================");
            i++;
        }
        tmp=tmp->suivant;
    }
    if(i==0) {
    	puts("\n===================================");
       	printf("Cette achat  n'existe pas\n");
       	puts("===================================\n\n\n\n");
	}
}
/********************************************************* Rechercher par quantite ************************************************************************/
void rechercher_achat_quantite(list3 *l3) {
    if(l3==NULL) {
        puts("\n======================");
        printf("Liste vide\n");
        puts("======================\n\n\n\n");
        return ;
    }
    list3 *tmp=l3;
    int quantite,i=0;
    printf("Entrer la quantite: ");
    scanf("%d",&quantite);
    puts("============================================================================================================");
    while(tmp!=NULL) {
        if(tmp->acht.quantite==quantite) {
            printf("Code du client: %d\t Code du produit: %d\t\t Date d'achat: %d/%d/%d\t\t Quantite: %d\n",tmp->acht.code_clt,tmp->acht.code_prd,tmp->acht.d.j,tmp->acht.d.m,tmp->acht.d.a,tmp->acht.quantite);
            puts("============================================================================================================");
            i++;
        }
        tmp=tmp->suivant;
    }
    if(i==0) {
    	puts("\n=================================");
        printf("Cette achat  n'existe pas\n");
        puts("=================================\n\n\n\n");
	}
}
/********************************************************************** Menu de recherche les achats ************************************************/
void menu_recherche_acht(list3* l3) {
    int choix;
a:
    do {
        system("cls");
        system("color 90");
        printf("============================================ Menu de recherche ========================================================\n");
        puts("=======================================================================================================================");
        printf("\t\t\t\t\t1- Rechercher par le code du client\n");
        printf("\t\t\t\t\t2- Rechercher par le code du produit\n");
        printf("\t\t\t\t\t3- Rechercher par la date d'achat\n");
        printf("\t\t\t\t\t4- Rechercher par la quantite\n");
        printf("\t\t\t\t\t0- Annuller l'operation\n");
        puts("=======================================================================================================================");
        puts("======================");
        printf("Entrez votre choix: ");
        scanf("%d",&choix);
        puts("======================\n");
        switch(choix) {
        case 0:
            return;
            break;
        case 1:
            rechercher_achat_code_clt(l3);
            break;
        case 2:
            rechercher_achat_code_prd(l3);
            break;
        case 3:
            rechercher_achat_date(l3);
            break;
        case 4:
            rechercher_achat_quantite(l3);
            break;
        default:
            goto a ;
        }
        printf("\n\n\n\n===========================================> ");
        system("Pause");
    } while(choix!=0);
}
/******************************************************* Enregistrer les achat dans un fichier ************************************************************/
void enregistrer_achat(list3 *l3) {
	if(l3==NULL) {
    	puts("======================");
        printf("Liste vide\n");
        puts("======================\n\n\n");
        return ;
    }
    list3 *tmp=l3;
    FILE *p=fopen("achat.txt","w");
    while(tmp!=NULL) {
        fprintf(p,"%d\n%d\n%d\n%d\n%d\n%d\n",tmp->acht.code_clt,tmp->acht.code_prd,tmp->acht.d.j,tmp->acht.d.m,tmp->acht.d.a,tmp->acht.quantite);
        tmp=tmp->suivant;
    }
    fclose(p);
	printf("\n==>Operation terminee avec succes\n");
}
/************************************************** Charger les information de fichier dans la liste ***************************************************/
list3* charger_achat(list3 *l3,FILE *p,int code_clt,int code_prd,int j,int m,int a,int quantite) {
    list3 *tmp1=l3;
    list3* nv=(list3*) malloc(sizeof(list3));
    nv->acht.code_clt=code_clt;
    nv->acht.code_prd=code_prd;
    nv->acht.d.j=j;
    nv->acht.d.m=m;
    nv->acht.d.a=a;
    nv->acht.quantite=quantite;
    nv->suivant=NULL;
    if(l3==NULL) return nv;
    else {
        list3 *tmp=l3;
        while(tmp->suivant!=NULL) tmp=tmp->suivant;
        tmp->suivant=nv;
        return l3;
    }
}
/******************************************************************** MENU PRINCIPALE ****************************************************************/
void menu_principale(list1 *l1,list2 *l2,list3 *l3) {
    int code_clt,telephone,code_prd,j,m,a,quantite,choix;
    char nom[20],prenom[20],nom_prd[20];
    float prix_achat,prix_vente;
    char login[10],pass[10],rep;
    login:
        system("cls");
        system("color A0");
        printf("============================================== Authentification ========================================================\n");
        printf("\n\n Entrer votre login >\t\t");
        scanf("%s",login);
        printf("\n\n Entrer votre mot de passe >\t");
        scanf("%s",pass);
        if(strcmp(login,"admin") || strcmp(pass,"1234")) {
        	puts("\n\n\n\n=================================");
            printf("login ou mot de passe incorrect!\n");
            puts("=================================\n\n\n\n\n\n\n");
            printf("===========================================> ");
            system("Pause");
            goto login;
        }
        system("cls");
        system("color 47");
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n================ Veuillez charger les informations des trois fichiers dans les listes devant commancer =================\n\n\n\n\n\n");
        printf("=============a> ");
		system("Pause");
a:
    do {
        system("cls");
        system("color E0");
        printf("=========================================== MENU PRINCIPALE ===========================================================\n");
        puts("=======================================================================================================================");
        printf("\t\t\t\t\t 1- Gestion des clients\n\n");
        printf("\t\t\t\t\t 2- Gestion des produits\n\n");
        printf("\t\t\t\t\t 3- Gestion des achats\n\n");
        printf("\t\t\t\t\t 4- Quitter l'application\n");
        puts("=======================================================================================================================\n");
        printf("Fais votre choix: ");
        scanf("%d",&choix);
        switch(choix) {
        case 1: {
b:
            do {
                system("cls");
                system("color B0");
                printf ("=========================================== Gestion des Clients =======================================================\n");
                puts("=======================================================================================================================");
                printf("\t\t\t\t1- Ajouter un client au debut de la liste\n");
                printf("\t\t\t\t2- Ajouter un client a la fin de la liste\n");
                printf("\t\t\t\t3- Afficher les clients\n");
                printf("\t\t\t\t4- Modifier les information d'un client\n");
                printf("\t\t\t\t5- Supprimer un client\n");
                printf("\t\t\t\t6- Rechercher un client\n");
                printf("\t\t\t\t7- Enregistrer les informations des clients dans un fichier\n");
                printf("\t\t\t\t8- Charger les informations du fichier dans la liste\n");
                printf("\t\t\t\t9- Retourner a la Menu principale\n");
                puts("=======================================================================================================================");
                puts("======================");
                printf("Entrez votre choix: ");
                scanf("%d",&choix);
                puts("======================\n");
                switch (choix) {
                case 1:
                    l1=ajt_clt_debut(l1);
                    break;
                case 2:
                    l1=ajt_clt_fin(l1);
                    break;
                case 3:
                    afficher_clt(l1);
                    break;
                case 4:
                    l1=modifier_clt(l1,l3);
                    break;
                case 5:
                    l1=supp_clt(l1);
                    break;
                case 6:
                    menu_rechercher_clt(l1);
                    break;
                case 7:
                    enregistrer_clt(l1);
                    break;
                case 8: {
                    FILE *p=fopen("client.txt","r");
                    if(p==NULL) {
                        printf("fichier n'existe pas\n\n\n\n");
                        system("Pause");
                        goto b;
                    }
                    while(!feof(p)) {
                        fscanf(p,"%d\n%s\n%s\n%d\n",&code_clt,nom,prenom,&telephone);
                        if(rech_clt(code_clt,l1)==1) continue;
                        l1=charger_clt(l1,p,code_clt,nom,prenom,telephone);
                    }
                    fclose(p);
                    printf("\n==>Operation terminee avec succes\n");
                    break;
                }
                case 9:
                    goto a;
                    break;
                default:
                    goto b;
                }
                printf("\n\n\n\n===========================================> ");
                system("Pause");
            } while(choix!=9);
        }
        break;
        case 2: {
c:
            do {
                system("cls");
                system("color B0");
                printf("========================================== Gestion des produits =======================================================\n");
                puts("=======================================================================================================================");
                printf("\t\t\t\t1- Ajouter un produit au debut de la liste\n");
                printf("\t\t\t\t2- Ajouter un produit a la fin de la liste\n");
                printf("\t\t\t\t3- Afficher les produits\n");
                printf("\t\t\t\t4- Modifier les information d'un produit\n");
                printf("\t\t\t\t5- Supprimer un produit\n");
                printf("\t\t\t\t6- Rechercher un produit\n");
                printf("\t\t\t\t7- Enregistrer les informations des produits dans un fichier\n");
                printf("\t\t\t\t8- Charger les informations du fichier dans la liste\n");
                printf("\t\t\t\t9- Retourner a la Menu principale\n");
                puts("=======================================================================================================================");
                puts("======================");
                printf("Entrez votre choix: ");
                scanf("%d",&choix);
                puts("======================\n");
                switch (choix) {
                case 1:
                    l2=ajt_prd_debut(l2);
                    break;
                case 2:
                    l2=ajt_prd_fin(l2);
                    break;
                case 3:
                    afficher_prd(l2);
                    break;
                case 4:
                    l2=modifier_prd(l2,l3);
                    break;
                case 5:
                    l2=supp_prd(l2);
                    break;
                case 6:
                    menu_recherche_prd(l2);
                    break;
                case 7:
                    enregistrer_prd(l2);
                    break;
                case 8: {
                    FILE *p=fopen("produit.txt","r");
                    if(p==NULL) {
                        printf("fichier n'existe pas\n\n\n\n");
                        system("Pause");
                        goto c;
                    }
                    list2 *tmp;
                    while(!feof(p)) {
                        fscanf(p,"%d\n%s\n%f\n%f\n",&code_prd,nom_prd,&prix_achat,&prix_vente);
                        if(rech_prd(code_prd,l2)==1) continue;
                        l2=charger_prd(l2,p,code_prd,nom_prd,prix_achat,prix_vente);
                    }
                    fclose(p);
                    printf("\n==>Operation terminee avec succes\n");
                    break;
                }
                case 9:
                    goto a;
                    break;
                default:
                    goto c;
                }
                printf("\n\n\n\n===========================================> ");
                system("Pause");
            }
            while (choix!=9);
            break;
        }
        case 3:  {
d:
            do {
                system("cls");
                system("color B0");
                printf ("=============================================== Gestion des achats ====================================================\n");
                puts("=======================================================================================================================");
                printf("\t\t\t\t1- Ajouter un achat au debut de la liste\n");
                printf("\t\t\t\t2- Ajouter un achat a la fin de la liste\n");
                printf("\t\t\t\t3- Afficher les achats\n");
                printf("\t\t\t\t4- Modifier les information d'un achat\n");
                printf("\t\t\t\t5- Supprimer un achat\n");
                printf("\t\t\t\t6- Rechercher un achat\n");
                printf("\t\t\t\t7- Enregistrer les informations dans un fichier\n");
                printf("\t\t\t\t8- Charger les informations du fichier dans la liste\n");
                printf("\t\t\t\t9- Retourner a la Menu principale\n");
                puts("=======================================================================================================================");
                puts("======================");
                printf("Entrez votre choix: ");
                scanf("%d",&choix);
                puts("======================\n");
                switch(choix) {
                case 1:
                    l3=ajt_achat_debut(l3,l1,l2);
                    break;
                case 2:
                    l3=ajt_achat_fin(l3,l1,l2);
                    break;
                case 3:
                    afficher_achat(l3);
                    break;
                case 4:
                    l3=modifier_achat(l3);
                    break;
                case 5:
                    l3=supp_achat(l3);
                    break;
                case 6:
                    menu_recherche_acht(l3);
                    break;
                case 7:
                    enregistrer_achat(l3);
                    break;
                case 8: {
                    FILE *p=fopen("achat.txt","r");
                    if(p==NULL) {
                        printf("fichier n'existe pas\n\n\n\n");
                        system("Pause");
                        goto d;
                    }
                    list3 *tmp;
                    while(!feof(p)) {
                        fscanf(p,"%d\n%d\n%d\n%d\n%d\n%d\n",&code_clt,&code_prd,&j,&m,&a,&quantite);
                        l3=charger_achat(l3,p,code_clt,code_prd,j,m,a,quantite);
                    }
                    fclose(p);
                    printf("\n==>Operation terminee avec succes\n");
                }
                break;
                case 9:
                    goto a;
                    break;
                default:
                    goto d;
                }
                printf("\n\n\n\n===========================================> ");
                system("Pause");
            } while (choix!=9);
            break;
        }
        break;
        case 4:
        	system("cls");
        	system("color 47");
            printf("======================== Vous devez enregistrer les information devant quitter l'application! =========================\n\n\n\n");
            printf("Vous etes sur? \no/n:\t");
            scanf("%s",&rep);
            if(rep!='o' && rep!='O') goto a;
            printf("\n\n\n================================================= Au revoir ============================================================\n\n\n\n\n\n\n\n");
            return;
        }
    }
    while(choix!=4);
}
int main() {
    list1 *l1=NULL;
    list2 *l2=NULL;
    list3 *l3=NULL;
    menu_principale(l1,l2,l3);
    return 0;
}