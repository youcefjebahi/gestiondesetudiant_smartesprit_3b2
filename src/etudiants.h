#include <gtk/gtk.h>
typedef struct
{
    char nom[20];
    char prenom[20];
    char id[20];
    char niveau[5];
    char date_naissance[15];
    char sexe [20];
    char telephone[20];
    char mail[40];
    char adresse[100];
    char type_chambre[15];
    char num_chambre[10];
    char debut_sej[15];
    char fin_sej[15];
} Etudiant;

void ajouter(Etudiant E, char fichier[]);
Etudiant rechercher(char id[],int* trouve, char fichier[]);
void modifier(char id[], Etudiant E, char fichier[]);
void supprimer(char id[], char fichier[]);
void nb_etudiant_niv(int t[], char fichier[]);
void afficher(char fichier[]);

void afficher_etudiant(GtkWidget *liste, Etudiant E);
void afficher_list_complete(GtkWidget *liste);
void vider(GtkWidget *liste);

