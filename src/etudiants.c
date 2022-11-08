#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "etudiants.h"
#include <gtk/gtk.h>
#include <config.h>
#include "interface.h"
#include "callbacks.h"
#include "support.h"
enum
	{
		NOM,
		PRENOM,
		ID,
		NIVEAU,
		DATE_NAISSANCE,
		SEXE,
		TELEPHONE,
		MAIL,
		ADRESSE,
		TYPE_CHAMBRE,
		NUM_CHAMBRE,
		DEBUT_SEJOUR,
		FIN_SEJOUR,
		COLUMNS,
	};

//fonction ajouter
void ajouter(Etudiant E, char fichier[])
{


    FILE*f=NULL;
    f=fopen(fichier,"a+");
    if (f!=NULL)
    {
        fprintf(f,"%s %s %s %s %s %s %s %s %s %s %s %s %s\n",E.nom,E.prenom,E.id,E.niveau,E.date_naissance,E.sexe,E.telephone,E.mail,E.adresse,E.type_chambre,E.num_chambre,E.debut_sej,E.fin_sej);
    	fclose(f);

    }
}

//fonction rechercher
Etudiant rechercher(char id[],int* trouve, char fichier[])
{
    FILE*f=NULL;
    Etudiant E;
    Etudiant E1;
    f=fopen(fichier,"r");

    if (f!=NULL)
    {
        while
        (fscanf(f,"%s %s %s %s %s %s %s %s %s %s %s %s %s",E.nom,E.prenom,E.id,E.niveau,E.date_naissance,E.sexe,E.telephone,E.mail,E.adresse,E.type_chambre,E.num_chambre,E.debut_sej,E.fin_sej)!=EOF && !(*trouve))


        {            
		if(strcmp(E.id,id)==0)
            	{
                	*trouve=1;
                	E1=E;
            	}
        }
        return(E1);
	fclose(f);
    }
}

//fonction modifier
void modifier(char id[], Etudiant E, char fichier[])

{

    Etudiant E1;
    FILE*f=NULL;
    FILE*f2=NULL;
    f=fopen(fichier,"r");
    f2=fopen("tempo.txt","a+");

    if (f!=NULL&&f2!=0)
    {
        while
        (fscanf(f,"%s %s %s %s %s %s %s %s %s %s %s %s %s",E1.nom,E1.prenom,E1.id,E1.niveau,E1.date_naissance,E1.sexe,E1.telephone,E1.mail,E1.adresse,E1.type_chambre,E1.num_chambre,E1.debut_sej,E1.fin_sej)!=EOF)
        {

            if
            (strcmp(id,E1.id)==0)

                /*modification*/
            {
                
                fprintf(f2,"%s %s %s %s %s %s %s %s %s %s %s %s %s\n",E.nom,E.prenom,E.id,E.niveau,E.date_naissance,E.sexe,E.telephone,E.mail,E.adresse,E.type_chambre,E.num_chambre,E.debut_sej,E.fin_sej);
            }
            else /*rien ne change*/
            {
                fprintf(f2,"%s %s %s %s %s %s %s %s %s %s %s %s %s\n",E1.nom,E1.prenom,E1.id,E1.niveau,E1.date_naissance,E1.sexe,E1.telephone,E1.mail,E1.adresse,E1.type_chambre,E1.num_chambre,E1.debut_sej,E1.fin_sej);
            }
        }
        fclose(f);
        fclose(f2);
        remove(fichier);
        rename("tempo.txt",fichier);
    }

}

//fonction supprimer
void supprimer(char id[20], char fichier[])
{
    Etudiant E;
    FILE*f=NULL;
    FILE*f1=NULL;

    f=fopen(fichier,"r");
    f1=fopen("tempo.txt","a+");

    /*scan de contenu du fichier f dans f1 */
    if((f!=NULL)&&(f1!=NULL))
    {
        while(fscanf(f,"%s %s %s %s %s %s %s %s %s %s %s %s %s",E.nom,E.prenom,E.id,E.niveau,E.date_naissance,E.sexe,E.telephone,E.mail,E.adresse,E.type_chambre,E.num_chambre,E.debut_sej,E.fin_sej)!=EOF)
        {
            if(strcmp(id,E.id)!=0)
                fprintf(f1,"%s %s %s %s %s %s %s %s %s %s %s %s %s\n",E.nom,E.prenom,E.id,E.niveau,E.date_naissance,E.sexe,E.telephone,E.mail,E.adresse,E.type_chambre,E.num_chambre,E.debut_sej,E.fin_sej);
        }
        fclose(f);
        fclose(f1);
        remove(fichier);
        rename("tempo.txt",fichier);
    }
}

//fonction nb_etudiant_niveau
void nb_etudiant_niv(int t[5], char fichier[])
{
    FILE*f=NULL;
    Etudiant E;

    f=fopen(fichier,"r");
    if (f!=NULL)
    {
        while
        (fscanf(f,"%s %s %s %s %s %s %s %s %s %s %s %s %s",E.nom,E.prenom,E.id,E.niveau,E.date_naissance,E.sexe,E.telephone,E.mail,E.adresse,E.type_chambre,E.num_chambre,E.debut_sej,E.fin_sej)!=EOF)
        {
            if(strcmp(E.niveau,"1")==0) ++t[0];
            if(strcmp(E.niveau,"2")==0) ++t[1];
            if(strcmp(E.niveau,"3")==0) ++t[2];
            if(strcmp(E.niveau,"4")==0) ++t[3];
            if(strcmp(E.niveau,"5")==0) ++t[4];
        }
	fclose(f);
    }
}


//affichage liste treeview
void afficher_list_complete(GtkWidget *liste)
{

	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

    	char Nom[20];
    	char Prenom[20];
    	char Id[20];
    	char Niveau[5];
    	char DateNaissance[15];
    	char Sexe [20];
    	char Telephone[20];
    	char Mail[40];
    	char Adresse[100];
    	char TypeChambre[15];
    	char NumeroChambre[10];
    	char DebutSejour[15];
    	char FinSejour[15];

	store=NULL;
	FILE *f;
	

	if (store==NULL)
	{
		renderer=gtk_cell_renderer_text_new();
		column= gtk_tree_view_column_new_with_attributes("Nom", renderer, "text",NOM, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer=gtk_cell_renderer_text_new();
		column= gtk_tree_view_column_new_with_attributes("Prenom", renderer, "text",PRENOM, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer=gtk_cell_renderer_text_new();
		column= gtk_tree_view_column_new_with_attributes("Id", renderer, "text",ID, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer=gtk_cell_renderer_text_new();
		column= gtk_tree_view_column_new_with_attributes("Niveau", renderer, "text",NIVEAU, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer=gtk_cell_renderer_text_new();
		column= gtk_tree_view_column_new_with_attributes("DateNaissance", renderer, "text",DATE_NAISSANCE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);


		renderer=gtk_cell_renderer_text_new();
		column= gtk_tree_view_column_new_with_attributes("Sexe", renderer, "text",SEXE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer=gtk_cell_renderer_text_new();
		column= gtk_tree_view_column_new_with_attributes("Telephone", renderer, "text",TELEPHONE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer=gtk_cell_renderer_text_new();
		column= gtk_tree_view_column_new_with_attributes("Mail", renderer, "text",MAIL, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer=gtk_cell_renderer_text_new();
		column= gtk_tree_view_column_new_with_attributes("Adresse", renderer, "text",ADRESSE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer=gtk_cell_renderer_text_new();
		column= gtk_tree_view_column_new_with_attributes("TypeChambre", renderer, "text",TYPE_CHAMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer=gtk_cell_renderer_text_new();
		column= gtk_tree_view_column_new_with_attributes("NumeroChambre", renderer, "text",NUM_CHAMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer=gtk_cell_renderer_text_new();
		column= gtk_tree_view_column_new_with_attributes("DebutSejour", renderer, "text",DEBUT_SEJOUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);


		renderer=gtk_cell_renderer_text_new();
		column= gtk_tree_view_column_new_with_attributes("FinSejour", renderer, "text",FIN_SEJOUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
		


	}
	store=gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

	f=fopen("Etudiants.txt", "r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		f=fopen("Etudiants.txt", "a+");
		while(fscanf(f,"%s %s %s %s %s %s %s %s %s %s %s %s %s\n",Nom,Prenom,Id,Niveau,DateNaissance,Sexe,Telephone,Mail,Adresse,TypeChambre,NumeroChambre,DebutSejour,FinSejour)!=EOF)
		{
			
			gtk_list_store_append(store,&iter);
			gtk_list_store_set(store, &iter, NOM, Nom, PRENOM, Prenom, ID, Id, NIVEAU, Niveau, DATE_NAISSANCE, DateNaissance, SEXE, Sexe, TELEPHONE, Telephone, MAIL, Mail, ADRESSE, Adresse, TYPE_CHAMBRE, TypeChambre, NUM_CHAMBRE, NumeroChambre, DEBUT_SEJOUR, DebutSejour, FIN_SEJOUR, FinSejour, -1);
		}
		fclose(f);
		gtk_tree_view_set_model(GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}

}

//afficher_etudiant
void afficher_etudiant(GtkWidget *liste, Etudiant E)
{

	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

    	char Nom[20];
    	char Prenom[20];
    	char Id[20];
    	char Niveau[5];
    	char DateNaissance[15];
    	char Sexe [20];
    	char Telephone[20];
    	char Mail[40];
    	char Adresse[100];
    	char TypeChambre[15];
    	char NumeroChambre[10];
    	char DebutSejour[15];
    	char FinSejour[15];

	store=NULL;	
	if (store==NULL)
	{
		renderer=gtk_cell_renderer_text_new();
		column= gtk_tree_view_column_new_with_attributes("Nom", renderer, "text",NOM, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer=gtk_cell_renderer_text_new();

		column= gtk_tree_view_column_new_with_attributes("Prenom", renderer, "text",PRENOM, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer=gtk_cell_renderer_text_new();
		column= gtk_tree_view_column_new_with_attributes("Id", renderer, "text",ID, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer=gtk_cell_renderer_text_new();
		column= gtk_tree_view_column_new_with_attributes("Niveau", renderer, "text",NIVEAU, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer=gtk_cell_renderer_text_new();
		column= gtk_tree_view_column_new_with_attributes("DateNaissance", renderer, "text",DATE_NAISSANCE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);


		renderer=gtk_cell_renderer_text_new();
		column= gtk_tree_view_column_new_with_attributes("Sexe", renderer, "text",SEXE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer=gtk_cell_renderer_text_new();
		column= gtk_tree_view_column_new_with_attributes("Telephone", renderer, "text",TELEPHONE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer=gtk_cell_renderer_text_new();
		column= gtk_tree_view_column_new_with_attributes("Mail", renderer, "text",MAIL, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer=gtk_cell_renderer_text_new();
		column= gtk_tree_view_column_new_with_attributes("Adresse", renderer, "text",ADRESSE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer=gtk_cell_renderer_text_new();
		column= gtk_tree_view_column_new_with_attributes("TypeChambre", renderer, "text",TYPE_CHAMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer=gtk_cell_renderer_text_new();
		column= gtk_tree_view_column_new_with_attributes("NumeroChambre", renderer, "text",NUM_CHAMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer=gtk_cell_renderer_text_new();
		column= gtk_tree_view_column_new_with_attributes("DebutSejour", renderer, "text",DEBUT_SEJOUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);


		renderer=gtk_cell_renderer_text_new();
		column= gtk_tree_view_column_new_with_attributes("FinSejour", renderer, "text",FIN_SEJOUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
		


	}
	store=gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

			gtk_list_store_append(store,&iter);
			gtk_list_store_set(store, &iter, NOM, E.nom, PRENOM, E.prenom, ID, E.id, NIVEAU, E.niveau, DATE_NAISSANCE, E.date_naissance, SEXE, E.sexe, TELEPHONE, E.telephone, MAIL, E.mail, ADRESSE, E.adresse, TYPE_CHAMBRE, E.type_chambre, NUM_CHAMBRE, E.num_chambre, DEBUT_SEJOUR, E.debut_sej, FIN_SEJOUR, E.fin_sej, -1);

		gtk_tree_view_set_model(GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);

}

