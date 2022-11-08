#include <gtk/gtk.h>


void
on_button_ajouter_etudiant_clicked     (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button_afficher_liste_clicked       (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button_rechercher_clicked           (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button_ajouter_clicked              (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button_afficher_ajout_clicked       (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button_retour_modification_clicked  (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button_modifier_clicked             (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button_afficher_modification_clicked
                                        (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button_supprimer_affichage_clicked  (GtkWidget       *objet,
                                        gpointer         user_data);


void
on_button_retour_affichage_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_window_gestion_show                 (GtkWidget       *widget,
                                        gpointer         user_data);


void
on_confirmer_supp_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_annuler_supp_clicked                (GtkButton       *button,
                                        gpointer         user_data);


void
on_confirmer_modif_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_annuler_modif_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_supprimer_clicked            (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button_retour_ajout_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void

on_button_modifier0_clicked            (GtkWidget       *objet,
                                        gpointer         user_data);


void
on_entry_rechercher_activate           (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button_retour_recherche_clicked     (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_entry_rechercher_delete_text        (GtkWidget       *objet,
                                        gint             start_pos,
                                        gint             end_pos,
                                        gpointer         user_data);


void
on_quitter_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_confirmer_quitter_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_annuler_quitter_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_checkbutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);
