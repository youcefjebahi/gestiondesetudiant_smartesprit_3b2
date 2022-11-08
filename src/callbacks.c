#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include<stdio.h>
#include<stdlib.h>
#include <gtk/gtk.h>
#include <string.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "etudiants.h"

Etudiant E, E1;
char fichier[20]="Etudiants.txt";
int trouve;
GtkWidget *nom,*prenom,*id,*niveau,*date_naissance,*telephone,*mail,*adresse,*type_chambre,*numero_chambre,*debut_sej,*fin_sej;
GtkWidget *window_gestion;
GtkWidget *window_ajout;
GtkWidget *window_modification;
GtkWidget *window_affichage;
GtkWidget *confirmer_supprission;
GtkWidget *confirmer_modification;
GtkWidget * window_quitter;
GtkTreeModel *model;
GtkTreeIter iter;
GtkTreeSelection *selection;
gchar *Nom, *Prenom, *Id, *Niveau, *DateNaissance, *Sexe, *Telephone, *Mail, *Adresse, *TypeChambre, *NumeroChambre, *DebutSejour, *FinSejour, *ids;
char id1[20], idm[20];
int x;

//dashboard
void
on_window_gestion_show                 (GtkWidget       *objet,
                                        gpointer         user_data)
{
	int t[]={0,0,0,0,0};
	int i, s=0;
	char t0[5], t1[5], t2[5], t3[5], t4[5], total[5];
	nb_etudiant_niv(t,fichier);
for(i=0;i<5;i++) s+=t[i];
	sprintf(t0,"%d",t[0]);
	sprintf(t1,"%d",t[1]);
	sprintf(t2,"%d",t[2]);
	sprintf(t3,"%d",t[3]);
	sprintf(t4,"%d",t[4]);
sprintf(total,"%d",s);

	GtkWidget *label_total;
	label_total = lookup_widget(objet, "label_nombre_total");
	gtk_label_set_text(GTK_LABEL(label_total),total);
	
	GtkWidget *label_nombre1;
	label_nombre1 = lookup_widget(objet, "label_nombre1");
	gtk_label_set_text(GTK_LABEL(label_nombre1),t0);

	GtkWidget *label_nombre2;
	label_nombre2 = lookup_widget(objet, "label_nombre2");
	gtk_label_set_text(GTK_LABEL(label_nombre2),t1);

	GtkWidget *label_nombre3;
	label_nombre3 = lookup_widget(objet, "label_nombre3");
	gtk_label_set_text(GTK_LABEL(label_nombre3),t2);

	GtkWidget *label_nombre4;
	label_nombre4 = lookup_widget(objet, "label_nombre4");
	gtk_label_set_text(GTK_LABEL(label_nombre4),t3);

	GtkWidget *label_nombre5;
	label_nombre5 = lookup_widget(objet, "label_nombre5");
	gtk_label_set_text(GTK_LABEL(label_nombre5),t4);

}


//afficher liste compète
void
on_button_afficher_liste_clicked       (GtkWidget       *objet,
                                        gpointer         user_data)
{	
	GtkWidget *treeview;

	window_affichage = create_window_affichage ();
	treeview=lookup_widget(window_affichage,"treeview");
        afficher_list_complete(treeview);
	window_gestion = lookup_widget(objet, "window_gestion");
	gtk_widget_hide (window_gestion);
	gtk_widget_show (window_affichage);

}


//retour après affichage
void
on_button_retour_affichage_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_hide (window_affichage);
	gtk_widget_show (window_gestion);
}



//ajouter etudiant 
void
on_button_ajouter_etudiant_clicked     (GtkWidget       *objet,
                                        gpointer         user_data)
{
	window_ajout = create_window_ajout ();
	gtk_widget_show (window_ajout);
	window_gestion = lookup_widget(objet, "window_gestion");
	gtk_widget_hide (window_gestion);
}


//ajouter
void
on_button_ajouter_clicked              (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *label_exist_ajout, *label_ajoute, *j, *radiobutton_homme, *radiobutton_femme;
int i, l, n, z, espace, k=0;
char *info;
char esp[2];
char label[13][40]={"label_nom_manquant","label_prenom_manquant", "label_id_manquant", "label_niveau_manquant", "label_naissance_manquant", "label_sexe_manquant", "label_telephone_manquant", "label_mail_manquant", "label_adresse_manquant", "label_type_chambre_manquant", "label_numero_chambre_manquant", "label_debut_sejour_manquant", "label_fin_sejour_manquant"};

	nom=lookup_widget(objet, "entry_nom");
	prenom=lookup_widget(objet, "entry_prenom");
	id=lookup_widget(objet, "entry_id");
	niveau=lookup_widget(objet, "spinbutton_niveau");
	date_naissance=lookup_widget(objet, "entry_naissance");
	radiobutton_homme= lookup_widget(objet, "radiobutton_homme");
	radiobutton_femme= lookup_widget(objet, "radiobutton_femme");
	telephone=lookup_widget(objet, "entry_telephone");
	mail=lookup_widget(objet, "entry_mail");
	adresse=lookup_widget(objet, "entry_adresse");
	type_chambre=lookup_widget(objet, "combobox_type_chambre");
	numero_chambre=lookup_widget(objet, "entry_numero_chambre");
	debut_sej=lookup_widget(objet, "entry_debut_sejour");
	fin_sej=lookup_widget(objet, "entry_fin_sejour");

for(i=0;i<13;i++)
{
switch(i)
{
case 0:
	n=strlen(gtk_entry_get_text(GTK_ENTRY(nom)));
	info=(char*) malloc(n);
	strcpy(info,gtk_entry_get_text(GTK_ENTRY(nom)));
	l=20;
	break;
case 1:
	n=strlen(gtk_entry_get_text(GTK_ENTRY(prenom)));
	info=(char*) malloc(n);
	strcpy(info,gtk_entry_get_text(GTK_ENTRY(prenom)));
	l=20;
	break;
case 2:
	n=strlen(gtk_entry_get_text(GTK_ENTRY(id)));
	info=(char*) malloc(n);
	strcpy(info,gtk_entry_get_text(GTK_ENTRY(id)));
	l=20;
	break;
case 3:
	n=5;
	info=(char*) malloc(n);
	sprintf(info,"%d",gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (niveau)));
	l=5;
	break;
case 4:
	n=strlen(gtk_entry_get_text(GTK_ENTRY(date_naissance)));
	info=(char*) malloc(n);
	strcpy(info,gtk_entry_get_text(GTK_ENTRY(date_naissance)));
	l=15;
	break;
case 5:
	n=20;
	info=(char*) malloc(n);
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(radiobutton_homme))) strcpy(info,"homme");
	else if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(radiobutton_femme))) strcpy(info,"femme");
	else strcpy(info,"");
	l=20;
	break;
case 6:
	n=strlen(gtk_entry_get_text(GTK_ENTRY(telephone)));
	info=(char*) malloc(n);
	strcpy(info,gtk_entry_get_text(GTK_ENTRY(telephone)));
	l=20;
	break;
case 7:
	n=strlen(gtk_entry_get_text(GTK_ENTRY(mail)));
	info=(char*) malloc(n);
	strcpy(info,gtk_entry_get_text(GTK_ENTRY(mail)));
	l=40;
	break;
case 8:
	n=strlen(gtk_entry_get_text(GTK_ENTRY(adresse)));
	info=(char*) malloc(n);
	strcpy(info,gtk_entry_get_text(GTK_ENTRY(adresse)));
	l=100;
	break;
case 9:
	n=15;
	info=(char*) malloc(n);
	if(gtk_combo_box_get_active_text(GTK_COMBO_BOX(type_chambre))!=NULL) strcpy(info,gtk_combo_box_get_active_text(GTK_COMBO_BOX(type_chambre)));
	else strcpy(info,"");
	l=15;
	break;
case 10:
	n=strlen(gtk_entry_get_text(GTK_ENTRY(numero_chambre)));
	info=(char*) malloc(n);
	strcpy(info,gtk_entry_get_text(GTK_ENTRY(numero_chambre)));
	l=10;
	break;
case 11:
	n=strlen(gtk_entry_get_text(GTK_ENTRY(debut_sej)));
	info=(char*) malloc(n);
	strcpy(info,gtk_entry_get_text(GTK_ENTRY(debut_sej)));
	l=15;
	break;
case 12:
	n=strlen(gtk_entry_get_text(GTK_ENTRY(fin_sej)));
	info=(char*) malloc(n);
	strcpy(info,gtk_entry_get_text(GTK_ENTRY(fin_sej)));
	l=15;
	break;
}
z=0;
espace=0;
strcpy(esp, " ");
while(espace==0 && (z < strlen(info)))
{
if(info[z]==esp[0]) espace=1;
z++;
}

if(strcmp(info,"")==0)
{
	j = lookup_widget(objet, label[i]);
	gtk_label_set_text(GTK_LABEL(j),"* manquant");
	label_ajoute = lookup_widget(objet, "label_ajoute");
	gtk_label_set_text(GTK_LABEL(label_ajoute),"");
	label_exist_ajout = lookup_widget(objet, "label_exist_ajout");
	gtk_label_set_text(GTK_LABEL(label_exist_ajout),"");
}
else if (strlen(info)>l)
{
	j = lookup_widget(objet, label[i]);
	gtk_label_set_text(GTK_LABEL(j),"*taille très grande");
}
else if (espace)
{
	j = lookup_widget(objet, label[i]);
	gtk_label_set_text(GTK_LABEL(j),"*mettez ( _ ) au lieu de espace");
}
else
{
	j = lookup_widget(objet, label[i]);
	gtk_label_set_text(GTK_LABEL(j),"");
	k++;
}
free(info);
}

if(k==13)
{
	strcpy(E.nom, gtk_entry_get_text(GTK_ENTRY(nom)));
	strcpy(E.prenom, gtk_entry_get_text(GTK_ENTRY(prenom)));
	strcpy(E.id, gtk_entry_get_text(GTK_ENTRY(id)));
	sprintf(E.niveau,"%d",gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (niveau)));
	strcpy(E.date_naissance, gtk_entry_get_text(GTK_ENTRY(date_naissance)));
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(radiobutton_homme))) strcpy(E.sexe,"homme");
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(radiobutton_femme))) strcpy(E.sexe,"femme");
	strcpy(E.telephone, gtk_entry_get_text(GTK_ENTRY(telephone)));
	strcpy(E.mail, gtk_entry_get_text(GTK_ENTRY(mail)));
	strcpy(E.adresse, gtk_entry_get_text(GTK_ENTRY(adresse)));
	strcpy(E.type_chambre,gtk_combo_box_get_active_text(GTK_COMBO_BOX(type_chambre)));
	strcpy(E.num_chambre, gtk_entry_get_text(GTK_ENTRY(numero_chambre)));
	strcpy(E.debut_sej, gtk_entry_get_text(GTK_ENTRY(debut_sej)));
	strcpy(E.fin_sej, gtk_entry_get_text(GTK_ENTRY(fin_sej)));

strcpy(id1, gtk_entry_get_text(GTK_ENTRY(id)));
trouve=0;
E1=rechercher(id1,&trouve,fichier);
if(!trouve)
{
	ajouter(E, fichier);
	label_ajoute = lookup_widget(objet, "label_ajoute");
	gtk_label_set_text(GTK_LABEL(label_ajoute),"Etudiant ajouté");
	label_exist_ajout = lookup_widget(objet, "label_exist_ajout");
	gtk_label_set_text(GTK_LABEL(label_exist_ajout),"");
}
else
{
	label_exist_ajout = lookup_widget(objet, "label_exist_ajout");
	gtk_label_set_text(GTK_LABEL(label_exist_ajout),"Id existe déjà!");
	label_ajoute = lookup_widget(objet, "label_ajoute");
	gtk_label_set_text(GTK_LABEL(label_ajoute),"");
}
}	
}


//affichage après ajout
void
on_button_afficher_ajout_clicked       (GtkWidget       *objet,
                                        gpointer         user_data)
{	
	gtk_widget_hide (window_ajout);
	window_affichage = create_window_affichage ();
	GtkWidget *treeview;
	treeview=lookup_widget(window_affichage,"treeview");
        afficher_list_complete(treeview);
 	gtk_widget_show (window_affichage);
}




//retour après ajout
void
on_button_retour_ajout_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_hide (window_ajout);
	gtk_widget_show (window_gestion);
}


//recherche
void
on_button_rechercher_clicked           (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *button_retour_recherche, *label_supprime;
trouve=0;
id=lookup_widget(objet, "entry_rechercher");
strcpy(id1, gtk_entry_get_text(GTK_ENTRY(id)));
E=rechercher(id1,&trouve,fichier);
if(trouve)
{
	
	gtk_widget_hide (window_affichage);
	window_affichage=create_window_affichage();
	gtk_widget_show (window_affichage);
	GtkWidget *treeview;
	treeview=lookup_widget(window_affichage,"treeview");
        afficher_etudiant(treeview, E);
	button_retour_recherche= lookup_widget(window_affichage, "button_retour_recherche");
	gtk_widget_show (button_retour_recherche);
	label_supprime = lookup_widget(objet, "label_supprime");
	gtk_label_set_text(GTK_LABEL(label_supprime),"");
}
else
{
	GtkWidget *label_non_trouve;
	label_non_trouve = lookup_widget(objet, "label_non_trouve");
	gtk_label_set_text(GTK_LABEL(label_non_trouve),"Non trouvé!");
	label_supprime = lookup_widget(objet, "label_supprime");
	gtk_label_set_text(GTK_LABEL(label_supprime),"");
}


}


//modification
void
on_button_modifier0_clicked            (GtkWidget       *objet,
                                        gpointer         user_data)
{

	GtkWidget *treeview;
	GtkWidget *label_selectionnez;
	GtkWidget *label_supprime;
	treeview=lookup_widget(window_affichage,"treeview");
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
	if(gtk_tree_selection_get_selected(selection, &model, &iter))
	{
		label_selectionnez = lookup_widget(objet, "label_selectionnez");
		gtk_label_set_text(GTK_LABEL(label_selectionnez),"");
		label_supprime = lookup_widget(objet, "label_supprime");
		gtk_label_set_text(GTK_LABEL(label_supprime),"");
		confirmer_modification=create_confirmer_modification ();
		gtk_widget_show (confirmer_modification);
	}
	else
	{
		label_selectionnez = lookup_widget(objet, "label_selectionnez");
		gtk_label_set_text(GTK_LABEL(label_selectionnez),"Selectionnez un étudiant pour modifier!");
		label_supprime = lookup_widget(objet, "label_supprime");
		gtk_label_set_text(GTK_LABEL(label_supprime),"");
	}
}


//confirmation modification
void
on_confirmer_modif_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{

		gtk_tree_model_get (model,&iter,0, &Nom, 1, &Prenom, 2, &Id, 3, &Niveau, 4, &DateNaissance, 5, &Sexe, 6, &Telephone, 7, &Mail, 8, &Adresse, 9, &TypeChambre, 10, &NumeroChambre, 11, &DebutSejour, 12, &FinSejour,-1);

window_modification = create_window_modification ();
gtk_widget_show (window_modification);

	GtkWidget *entry_nom2, *entry_prenom2, *entry_id2, *spinbutton_niveau2, *entry_naissance2, *radiobutton_homme2, *radiobutton_femme2, *entry_telephone2, *entry_mail2, *entry_adresse2, *combobox_type_chambre2, *entry_numero_chambre2, *entry_debut_sejour2, *entry_fin_sejour2;

	entry_nom2 = lookup_widget(window_modification, "entry_nom2");
	gtk_entry_set_text(GTK_LABEL(entry_nom2),Nom);
	entry_prenom2= lookup_widget(window_modification, "entry_prenom2");
	gtk_entry_set_text(GTK_LABEL(entry_prenom2),Prenom);
	entry_id2= lookup_widget(window_modification, "entry_id2");
	gtk_entry_set_text(GTK_LABEL(entry_id2),Id);
spinbutton_niveau2= lookup_widget(window_modification, "spinbutton_niveau2");
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton_niveau2),atoi(Niveau));
	entry_naissance2= lookup_widget(window_modification, "entry_naissance2");
	gtk_entry_set_text(GTK_LABEL(entry_naissance2),DateNaissance);
radiobutton_homme2= lookup_widget(window_modification, "radiobutton_homme2");
radiobutton_femme2= lookup_widget(window_modification, "radiobutton_femme2");
if(strcmp(Sexe,"homme")==0) gtk_toggle_button_set_active(GTK_RADIO_BUTTON(radiobutton_homme2),TRUE);
else gtk_toggle_button_set_active(GTK_RADIO_BUTTON(radiobutton_femme2),TRUE); 
	entry_telephone2= lookup_widget(window_modification, "entry_telephone2");
	gtk_entry_set_text(GTK_LABEL(entry_telephone2),Telephone);
	entry_mail2= lookup_widget(window_modification, "entry_mail2");
	gtk_entry_set_text(GTK_LABEL(entry_mail2),Mail);
	entry_adresse2= lookup_widget(window_modification, "entry_adresse2");
	gtk_entry_set_text(GTK_LABEL(entry_adresse2),Adresse);
combobox_type_chambre2= lookup_widget(window_modification, "combobox_type_chambre2");
char chambres[4][20]={"Chambre_à_1","Chambre_à_2","Chambre_à_3","Chambre_à_4"};
int i=0;
while(i<4 && (strcmp(TypeChambre,chambres[i])!=0)) {i++;}
gtk_combo_box_set_active(GTK_COMBO_BOX(combobox_type_chambre2),i);
	entry_numero_chambre2= lookup_widget(window_modification, "entry_numero_chambre2");
	gtk_entry_set_text(GTK_LABEL(entry_numero_chambre2),NumeroChambre);
	entry_debut_sejour2= lookup_widget(window_modification, "entry_debut_sejour2");
	gtk_entry_set_text(GTK_LABEL(entry_debut_sejour2),DebutSejour);
	entry_fin_sejour2= lookup_widget(window_modification, "entry_fin_sejour2");
	gtk_entry_set_text(GTK_LABEL(entry_fin_sejour2),FinSejour);
strcpy(idm,Id);
gtk_widget_hide(window_affichage);
gtk_widget_hide(confirmer_modification);
}

//annulation modification
void
on_annuler_modif_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_widget_hide (confirmer_modification);
}

//modifier
void
on_button_modifier_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *label_confirmer;
label_confirmer=lookup_widget(objet,"label_confirmer");
if (x==1)
{
gtk_label_set_text(GTK_LABEL(label_confirmer),"");

GtkWidget *label_existe_modification, *label_modifie, *j, *radiobutton_homme2, *radiobutton_femme2;
int i, l, n, z, espace, k=0;
char *info;
char esp[2];
char label2[13][40]={"label_nom_manquant2","label_prenom_manquant2", "label_id_manquant2", "label_niveau_manquant2", "label_naissance_manquant2", "label_sexe_manquant2", "label_telephone_manquant2", "label_mail_manquant2", "label_adresse_manquant2", "label_type_chambre_manquant2", "label_numero_chambre_manquant2", "label_debut_sejour_manquant2", "label_fin_sejour_manquant2"};


	nom=lookup_widget(objet, "entry_nom2");
	prenom=lookup_widget(objet, "entry_prenom2");
	id=lookup_widget(objet, "entry_id2");
	niveau=lookup_widget(objet, "spinbutton_niveau2");
	date_naissance=lookup_widget(objet, "entry_naissance2");
	radiobutton_homme2= lookup_widget(objet, "radiobutton_homme2");
	radiobutton_femme2= lookup_widget(objet, "radiobutton_femme2");
	telephone=lookup_widget(objet, "entry_telephone2");
	mail=lookup_widget(objet, "entry_mail2");
	adresse=lookup_widget(objet, "entry_adresse2");
	type_chambre=lookup_widget(objet, "combobox_type_chambre2");
	numero_chambre=lookup_widget(objet, "entry_numero_chambre2");
	debut_sej=lookup_widget(objet, "entry_debut_sejour2");
	fin_sej=lookup_widget(objet, "entry_fin_sejour2");

for(i=0;i<13;i++)
{
switch(i)
{
case 0:
	n=strlen(gtk_entry_get_text(GTK_ENTRY(nom)));
	info=(char*) malloc(n);
	strcpy(info,gtk_entry_get_text(GTK_ENTRY(nom)));
	l=20;
	break;
case 1:
	n=strlen(gtk_entry_get_text(GTK_ENTRY(prenom)));
	info=(char*) malloc(n);
	strcpy(info,gtk_entry_get_text(GTK_ENTRY(prenom)));
	l=20;
	break;
case 2:
	n=strlen(gtk_entry_get_text(GTK_ENTRY(id)));
	info=(char*) malloc(n);
	strcpy(info,gtk_entry_get_text(GTK_ENTRY(id)));
	l=20;
	break;
case 3:
	n=5;
	info=(char*) malloc(n);
	sprintf(info,"%d",gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (niveau)));
	l=5;
	break;
case 4:
	n=strlen(gtk_entry_get_text(GTK_ENTRY(date_naissance)));
	info=(char*) malloc(n);
	strcpy(info,gtk_entry_get_text(GTK_ENTRY(date_naissance)));
	l=15;
	break;
case 5:
	n=20;
	info=(char*) malloc(n);
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(radiobutton_homme2))) strcpy(info,"homme");
	else if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(radiobutton_femme2))) strcpy(info,"femme");
	else strcpy(info,"");
	l=20;
	break;
case 6:
	n=strlen(gtk_entry_get_text(GTK_ENTRY(telephone)));
	info=(char*) malloc(n);
	strcpy(info,gtk_entry_get_text(GTK_ENTRY(telephone)));
	l=20;
	break;
case 7:
	n=strlen(gtk_entry_get_text(GTK_ENTRY(mail)));
	info=(char*) malloc(n);
	strcpy(info,gtk_entry_get_text(GTK_ENTRY(mail)));
	l=40;
	break;
case 8:
	n=strlen(gtk_entry_get_text(GTK_ENTRY(adresse)));
	info=(char*) malloc(n);
	strcpy(info,gtk_entry_get_text(GTK_ENTRY(adresse)));
	l=100;
	break;
case 9:
	n=15;
	info=(char*) malloc(n);
	if(gtk_combo_box_get_active_text(GTK_COMBO_BOX(type_chambre))!=NULL) strcpy(info,gtk_combo_box_get_active_text(GTK_COMBO_BOX(type_chambre)));
	else strcpy(info,"");
	l=15;
	break;
case 10:
	n=strlen(gtk_entry_get_text(GTK_ENTRY(numero_chambre)));
	info=(char*) malloc(n);
	strcpy(info,gtk_entry_get_text(GTK_ENTRY(numero_chambre)));
	l=10;
	break;
case 11:
	n=strlen(gtk_entry_get_text(GTK_ENTRY(debut_sej)));
	info=(char*) malloc(n);
	strcpy(info,gtk_entry_get_text(GTK_ENTRY(debut_sej)));
	l=15;
	break;
case 12:
	n=strlen(gtk_entry_get_text(GTK_ENTRY(fin_sej)));
	info=(char*) malloc(n);
	strcpy(info,gtk_entry_get_text(GTK_ENTRY(fin_sej)));
	l=15;
	break;
}
z=0;
espace=0;
strcpy(esp, " ");
while(espace==0 && (z < strlen(info)))
{
if(info[z]==esp[0]) espace=1;
z++;
}

if(strcmp(info,"")==0)
{
	j = lookup_widget(objet, label2[i]);
	gtk_label_set_text(GTK_LABEL(j),"* manquant");
	label_modifie = lookup_widget(objet, "label_modifie");
	gtk_label_set_text(GTK_LABEL(label_modifie),"");
	label_existe_modification = lookup_widget(objet, "label_existe_modification");
	gtk_label_set_text(GTK_LABEL(label_existe_modification),"");
}
else if (strlen(info)>l)
{
	j = lookup_widget(objet, label2[i]);
	gtk_label_set_text(GTK_LABEL(j),"*taille très grande");
}
else if (espace)
{
	j = lookup_widget(objet, label2[i]);
	gtk_label_set_text(GTK_LABEL(j),"*mettez ( _ ) au lieu de espace");
}
else
{
	j = lookup_widget(objet, label2[i]);
	gtk_label_set_text(GTK_LABEL(j),"");
	k++;
}
free(info);
}

if(k==13)
{

	strcpy(E.nom, gtk_entry_get_text(GTK_ENTRY(nom)));
	strcpy(E.prenom, gtk_entry_get_text(GTK_ENTRY(prenom)));
	strcpy(E.id, gtk_entry_get_text(GTK_ENTRY(id)));
	sprintf(E.niveau,"%d",gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (niveau)));
	strcpy(E.date_naissance, gtk_entry_get_text(GTK_ENTRY(date_naissance)));
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(radiobutton_homme2)))	strcpy(E.sexe,"homme");
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(radiobutton_femme2)))	strcpy(E.sexe,"femme");
	strcpy(E.telephone, gtk_entry_get_text(GTK_ENTRY(telephone)));
	strcpy(E.mail, gtk_entry_get_text(GTK_ENTRY(mail)));
	strcpy(E.adresse, gtk_entry_get_text(GTK_ENTRY(adresse)));
	strcpy(E.type_chambre, gtk_combo_box_get_active_text(GTK_COMBO_BOX(type_chambre)));
	strcpy(E.num_chambre, gtk_entry_get_text(GTK_ENTRY(numero_chambre)));
	strcpy(E.debut_sej, gtk_entry_get_text(GTK_ENTRY(debut_sej)));
	strcpy(E.fin_sej, gtk_entry_get_text(GTK_ENTRY(fin_sej)));

strcpy(id1, gtk_entry_get_text(GTK_ENTRY(id)));
trouve=0;
E1=rechercher(id1,&trouve,fichier);
if(!trouve || (trouve&&(strcmp(idm,E.id)==0)))
{
int trouve1=0;
E1=rechercher(idm,&trouve1,fichier);
if(trouve1)
{
	modifier(idm, E, fichier);
	label_modifie = lookup_widget(objet, "label_modifie");
	gtk_label_set_text(GTK_LABEL(label_modifie),"Etudiant modifié");
	label_existe_modification = lookup_widget(objet, "label_existe_modification");
	gtk_label_set_text(GTK_LABEL(label_existe_modification),"");
}
else
{
	label_modifie = lookup_widget(objet, "label_modifie");
	gtk_label_set_text(GTK_LABEL(label_modifie),"Déjà modifié");
	label_existe_modification = lookup_widget(objet, "label_existe_modification");
	gtk_label_set_text(GTK_LABEL(label_existe_modification),"");
}

}
if(trouve && (strcmp(idm,E.id)!=0))
{
int trouve1=0;
E1=rechercher(idm,&trouve1,fichier);
if(trouve1)
{

	label_existe_modification = lookup_widget(objet, "label_existe_modification");
	gtk_label_set_text(GTK_LABEL(label_existe_modification),"Id existe déjà!");
	label_modifie = lookup_widget(objet, "label_modifie");
	gtk_label_set_text(GTK_LABEL(label_modifie),"");
}
else
{
	label_modifie = lookup_widget(objet, "label_modifie");
	gtk_label_set_text(GTK_LABEL(label_modifie),"Déjà modifié");
}
}
}
x=0;	
}
else 
{
gtk_label_set_text(GTK_LABEL(label_confirmer),"cocher 'confirmer' pour modifier");
}
}

//check button confirmer modificatin
void
on_checkbutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)) x=1;
else x=0;
}

//affichage après modification
void
on_button_afficher_modification_clicked
                                        (GtkWidget       *objet,
                                        gpointer         user_data)
{
	gtk_widget_hide (window_modification);
	window_affichage = lookup_widget(objet, "window_affichage");
	window_affichage = create_window_affichage ();
	GtkWidget *treeview;
	treeview=lookup_widget(window_affichage,"treeview");
        afficher_list_complete(treeview);
 	gtk_widget_show (window_affichage);
}




//retour après modification
void
on_button_retour_modification_clicked  (GtkWidget       *objet,
                                        gpointer         user_data)
{
	gtk_widget_hide (window_modification);
	window_affichage = lookup_widget(objet, "window_affichage");
	window_affichage = create_window_affichage ();
	GtkWidget *treeview;
	treeview=lookup_widget(window_affichage,"treeview");
        afficher_list_complete(treeview);
 	gtk_widget_show (window_affichage);
}


//supprission
void
on_button_supprimer_clicked            (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *treeview;
	GtkWidget *label_selectionnez;
	GtkWidget *label_supprime;
	treeview=lookup_widget(window_affichage,"treeview");
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));

	if(gtk_tree_selection_get_selected(selection, &model, &iter))
	{
		label_selectionnez = lookup_widget(objet, "label_selectionnez");
		gtk_label_set_text(GTK_LABEL(label_selectionnez),"");
		label_supprime = lookup_widget(objet, "label_supprime");
		gtk_label_set_text(GTK_LABEL(label_supprime),"");
		confirmer_supprission=create_confirmer_supprission ();
		gtk_widget_show (confirmer_supprission);
	}
	else
	{
		label_selectionnez = lookup_widget(objet, "label_selectionnez");
		gtk_label_set_text(GTK_LABEL(label_selectionnez),"Selectionnez un étudiant pour supprimer!");
		label_supprime = lookup_widget(objet, "label_supprime");
		gtk_label_set_text(GTK_LABEL(label_supprime),"");
	}
}


//confirmation supprission
void
on_confirmer_supp_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_tree_model_get (model,&iter,2,&ids,-1);
	gtk_list_store_remove(GTK_LIST_STORE(model),&iter);
	supprimer(ids, fichier);
	GtkWidget *label_supprime;
	label_supprime = lookup_widget(window_affichage, "label_supprime");
	gtk_label_set_text(GTK_LABEL(label_supprime),"Etudiant supprimé!");
	gtk_widget_hide (confirmer_supprission);	
}


//annulation supprission
void
on_annuler_supp_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_widget_hide (confirmer_supprission);
}


//recherche entrer
void
on_entry_rechercher_activate           (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *button_retour_recherche, *label_supprime;
trouve=0;
id=lookup_widget(objet, "entry_rechercher");
strcpy(id1, gtk_entry_get_text(GTK_ENTRY(id)));
E=rechercher(id1,&trouve,fichier);
if(trouve)
{
	gtk_widget_hide (window_affichage);
	window_affichage=create_window_affichage();
	gtk_widget_show (window_affichage);
	GtkWidget *treeview;
	treeview=lookup_widget(window_affichage,"treeview");
        afficher_etudiant(treeview, E);
	button_retour_recherche= lookup_widget(window_affichage, "button_retour_recherche");
	gtk_widget_show (button_retour_recherche);
	label_supprime = lookup_widget(objet, "label_supprime");
	gtk_label_set_text(GTK_LABEL(label_supprime),"");
}
else
{

	GtkWidget *label_non_trouve;
	label_non_trouve = lookup_widget(objet, "label_non_trouve");
	gtk_label_set_text(GTK_LABEL(label_non_trouve),"Non trouvé!");
	label_supprime = lookup_widget(objet, "label_supprime");
	gtk_label_set_text(GTK_LABEL(label_supprime),"");

}

}

//retour recherche
void
on_button_retour_recherche_clicked     (GtkWidget       *objet,
                                        gpointer         user_data)
{
	gtk_widget_hide (window_affichage);
	window_affichage=create_window_affichage();
	gtk_widget_show (window_affichage);
	GtkWidget *treeview;
	treeview=lookup_widget(window_affichage,"treeview");
	afficher_list_complete(treeview);
}

//entry recherche delete
void
on_entry_rechercher_delete_text        (GtkWidget       *objet,
                                        gint             start_pos,
                                        gint             end_pos,
                                        gpointer         user_data)
{
	GtkWidget *label_non_trouve;
	label_non_trouve = lookup_widget(objet, "label_non_trouve");
	gtk_label_set_text(GTK_LABEL(label_non_trouve),"");
}

//quitter
void
on_quitter_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	window_quitter=create_window_quitter ();
	gtk_widget_show (window_quitter);
}

//confirmer quitter
void
on_confirmer_quitter_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_main_quit();
}

//annuler quitter
void
on_annuler_quitter_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_hide (window_quitter);
}


