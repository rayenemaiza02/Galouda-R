#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>


#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "agent.h"


char gender[50];
int p=-1;
int supp=0;
int v;


//ajouter

void
on_button9_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
    char text[100];
    GtkWidget *id;
    GtkWidget *lastname;
    GtkWidget *firstname;
    GtkWidget *cin;
    GtkWidget *address;
    GtkWidget *email;
    GtkWidget *phone;
    GtkWidget *output;
    GtkWidget *combobox5;
    GtkWidget *spinbutton8;
    GtkWidget *spinbutton9;
    GtkWidget *spinbutton10;
    agent ag;
    int t;

    // Récupération des widgets
    id = lookup_widget(GTK_WIDGET(button), "entry65");
    lastname = lookup_widget(GTK_WIDGET(button), "entry29");
    firstname = lookup_widget(GTK_WIDGET(button), "entry26");
    cin = lookup_widget(GTK_WIDGET(button), "entry27");
    address = lookup_widget(GTK_WIDGET(button), "entry28");
    email = lookup_widget(GTK_WIDGET(button), "entry30");
    phone = lookup_widget(GTK_WIDGET(button), "entry46");
    output = lookup_widget(GTK_WIDGET(button), "label180");
    combobox5 = lookup_widget(GTK_WIDGET(button), "combobox5");
    spinbutton8 = lookup_widget(GTK_WIDGET(button), "spinbutton8");
    spinbutton9 = lookup_widget(GTK_WIDGET(button), "spinbutton9");
    spinbutton10 = lookup_widget(GTK_WIDGET(button), "spinbutton10");

    // Récupération des données de l'interface
    ag.birth_day = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton8));
    ag.birth_month = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton9));
    ag.birth_year = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton10));
    strcpy(ag.id, gtk_entry_get_text(GTK_ENTRY(id)));
    strcpy(ag.last_name, gtk_entry_get_text(GTK_ENTRY(lastname)));
    strcpy(ag.first_name, gtk_entry_get_text(GTK_ENTRY(firstname)));
    strcpy(ag.cin, gtk_entry_get_text(GTK_ENTRY(cin)));
    strcpy(ag.address, gtk_entry_get_text(GTK_ENTRY(address)));
    strcpy(ag.email, gtk_entry_get_text(GTK_ENTRY(email)));
    strcpy(ag.phone, gtk_entry_get_text(GTK_ENTRY(phone)));
    strcpy(ag.governorate, gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox5)));
    strcpy(ag.gender, gender);

    if (p == 0) {
        ag.use_check = 1;
        ag.use_espece = 0;
    } else if (p == 1) {
        ag.use_check = 0;
        ag.use_espece = 1;
    } else {
        ag.use_check = 0;
        ag.use_espece = 0;
    }

    // Vérification de l'existence de l'ID
    if (verifier(ag.id)) {
        // ID existe déjà
        gtk_label_set_text(GTK_LABEL(output), "Erreur : ID existe déjà !");
        return; // Arrête la fonction si l'ID existe
    }

    // Ajout de l'agent si l'ID n'existe pas
    t = ajouter("agent.txt", ag);
    if (t == 1) {
        // Succès
        sprintf(text, "Agent ajouté avec succès !");
        gtk_label_set_text(GTK_LABEL(output), text);
        gtk_entry_set_text(GTK_ENTRY(id), "");
        gtk_entry_set_text(GTK_ENTRY(lastname), "");
        gtk_entry_set_text(GTK_ENTRY(firstname), "");
        gtk_entry_set_text(GTK_ENTRY(cin), "");
        gtk_entry_set_text(GTK_ENTRY(address), "");
        gtk_entry_set_text(GTK_ENTRY(email), "");
        gtk_entry_set_text(GTK_ENTRY(phone), "+216");
    } else {
        // Erreur lors de l'ajout
        gtk_label_set_text(GTK_LABEL(output), "Erreur lors de l'ajout !");
    }
}



void
on_radiobuttonR1_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{ if (gtk_toggle_button_get_active(togglebutton))
	strcpy(gender,"man");

}


void
on_radiobuttonR2_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{ if (gtk_toggle_button_get_active(togglebutton))
	strcpy(gender,"women");

}


void
on_checkbutton5_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{ GtkWidget *checkbutton6;
    checkbutton6 = lookup_widget(GTK_WIDGET(togglebutton), "checkbutton6");

    if (gtk_toggle_button_get_active(togglebutton))
 {p=0;
        // Si checkbutton5 est activé, décocher checkbutton6
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton6), FALSE);
    }
}


void
on_checkbutton6_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{GtkWidget *checkbutton5;
    checkbutton5 = lookup_widget(GTK_WIDGET(togglebutton), "checkbutton5");

    if (gtk_toggle_button_get_active(togglebutton)) {p=1;
        // Si checkbutton6 est activé, décocher checkbutton5
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton5), FALSE);
    }
}


//chercher
void
on_SEARCH_ADD_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
   
    // Widgets de l'interface
    GtkWidget *id;
    GtkWidget *lastname;
    GtkWidget *firstname;
    GtkWidget *cin;
    GtkWidget *address;
    GtkWidget *email;
    GtkWidget *phone;
    GtkWidget *combobox5;
    GtkWidget *spinbutton8;
    GtkWidget *spinbutton9;
    GtkWidget *spinbutton10;
    GtkWidget *output_label;

    // Variables
    char search_id[30];
    agent ag;

    // Récupération des widgets de l'interface
    id=lookup_widget(GTK_WIDGET(button),"entry_search");
    lastname = lookup_widget(GTK_WIDGET(button), "entry29");
    firstname = lookup_widget(GTK_WIDGET(button), "entry26");
    cin = lookup_widget(GTK_WIDGET(button), "entry27");
    address = lookup_widget(GTK_WIDGET(button), "entry28");
    email = lookup_widget(GTK_WIDGET(button), "entry30");
    phone = lookup_widget(GTK_WIDGET(button), "entry46");
    combobox5 = lookup_widget(GTK_WIDGET(button), "combobox5");
    spinbutton8 = lookup_widget(GTK_WIDGET(button), "spinbutton8");
    spinbutton9 = lookup_widget(GTK_WIDGET(button), "spinbutton9");
    spinbutton10 = lookup_widget(GTK_WIDGET(button), "spinbutton10");
    output_label = lookup_widget(GTK_WIDGET(button), "label_search_result");

    // Récupérer l'ID saisi
    
    strcpy(search_id, gtk_entry_get_text(GTK_ENTRY(id)));

    // Debug pour voir si l'ID a été correctement récupéré
    printf("ID saisi : %s\n", search_id);

    // Recherche de l'agent dans le fichier
    ag = chercher("agent.txt",search_id);
	 printf("ID agenttrouve : %s\n", ag.id);

    // Vérifier si l'agent a été trouvé
    if (strcmp(ag.id, "-1") == 0) {
        // Agent non trouvé
        gtk_label_set_text(GTK_LABEL(output_label), "Erreur : Aucun agent trouvé avec cet ID.");

        // Effacer les champs
        gtk_entry_set_text(GTK_ENTRY(lastname), "");
        gtk_entry_set_text(GTK_ENTRY(firstname), "");
        gtk_entry_set_text(GTK_ENTRY(cin), "");
        gtk_entry_set_text(GTK_ENTRY(address), "");
        gtk_entry_set_text(GTK_ENTRY(email), "");
        gtk_entry_set_text(GTK_ENTRY(phone), "+216");
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton8), 1);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton9), 1);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton10), 2000);
        gtk_combo_box_set_active(GTK_COMBO_BOX(combobox5), -1); // Aucun élément sélectionné

        // Décocher les boutons
        GtkWidget *gender_man_radio = lookup_widget(GTK_WIDGET(button), "radiobuttonR1");
        GtkWidget *gender_woman_radio = lookup_widget(GTK_WIDGET(button), "radiobuttonR2");
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gender_man_radio), FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gender_woman_radio), FALSE);

        GtkWidget *check_checkbutton = lookup_widget(GTK_WIDGET(button), "checkbutton5");
        GtkWidget *espece_checkbutton = lookup_widget(GTK_WIDGET(button), "checkbutton6");
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_checkbutton), FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(espece_checkbutton), FALSE);
    } else {
        // Agent trouvé, remplir les champs
        gtk_label_set_text(GTK_LABEL(output_label), "Agent trouvé avec succès !");
        gtk_entry_set_text(GTK_ENTRY(lastname), ag.last_name);
        gtk_entry_set_text(GTK_ENTRY(firstname), ag.first_name);
        gtk_entry_set_text(GTK_ENTRY(cin), ag.cin);
        gtk_entry_set_text(GTK_ENTRY(address), ag.address);
        gtk_entry_set_text(GTK_ENTRY(email), ag.email);
        gtk_entry_set_text(GTK_ENTRY(phone), ag.phone);

        // Sélectionner la bonne valeur dans le combobox
        gtk_combo_box_set_active(GTK_COMBO_BOX(combobox5), 0); // Valeur par défaut
        if (strcmp(ag.governorate, "ARIANA") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(combobox5), 0);
        } else if (strcmp(ag.governorate, "BEJA") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(combobox5), 1);
        }
	 else if (strcmp(ag.governorate, "BIZERTE") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(combobox5), 2);
        }
	 else if (strcmp(ag.governorate, "BEN AROUS") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(combobox5), 3);
        }
 	else if (strcmp(ag.governorate, "TATAOUIN") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(combobox5), 4);
        }
 	else if (strcmp(ag.governorate, "TOZEUR") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(combobox5), 5);
        } else if (strcmp(ag.governorate, "TUNIS") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(combobox5), 6);
        }
 	else if (strcmp(ag.governorate, "JENDOUBA") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(combobox5), 7);
        }
 	else if (strcmp(ag.governorate, "ZAGHOUANE") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(combobox5), 8);
        }
	 else if (strcmp(ag.governorate, "SILIANA") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(combobox5), 9);
        }
 	else if (strcmp(ag.governorate, "SOUSSE") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(combobox5), 10);
        }
 	else if (strcmp(ag.governorate, "SIDI BOUZID") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(combobox5), 11);
        }
 	else if (strcmp(ag.governorate, "SFAX") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(combobox5), 12);
	}
 	else if (strcmp(ag.governorate, "GABES") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(combobox5), 13);
        }
 	else if (strcmp(ag.governorate, "GBELI") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(combobox5), 14);
        }
 	else if (strcmp(ag.governorate, "GASSERINE") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(combobox5), 15);
        }
 	else if (strcmp(ag.governorate, "GAFSA") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(combobox5), 16);
        }
 	else if (strcmp(ag.governorate, "KAIRAOUN") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(combobox5), 17);
        }
 	else if (strcmp(ag.governorate, "KEF") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(combobox5), 18);
        }
 	else if (strcmp(ag.governorate, "MEDNIN") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(combobox5), 19);
        }
 	else if (strcmp(ag.governorate, "MONASTIR") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(combobox5), 20);
        }
 	else if (strcmp(ag.governorate, "MANOUBA") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(combobox5), 21);
        }
 	else if (strcmp(ag.governorate, "MAHDIA") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(combobox5), 22);
        }
 	else if (strcmp(ag.governorate, "NABEUL") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(combobox5), 23);
        }
       

        // Remplir les spinbuttons
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton8), ag.birth_day);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton9), ag.birth_month);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton10), ag.birth_year);

        // Boutons radio pour le genre
        GtkWidget *gender_man_radio = lookup_widget(GTK_WIDGET(button), "radiobuttonR1");
        GtkWidget *gender_woman_radio = lookup_widget(GTK_WIDGET(button), "radiobuttonR2");

        if (strcmp(ag.gender, "man") == 0) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gender_man_radio), TRUE);
        } else if (strcmp(ag.gender, "woman") == 0) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gender_woman_radio), TRUE);
        }

        // Checkbuttons pour le mode de paiement
        GtkWidget *check_checkbutton = lookup_widget(GTK_WIDGET(button), "checkbutton5");
        GtkWidget *espece_checkbutton = lookup_widget(GTK_WIDGET(button), "checkbutton6");

        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_checkbutton), ag.use_check);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(espece_checkbutton), ag.use_espece);
    }
}











//modifier



void
on_button10_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
    // Widgets
    GtkWidget *id, *lastname, *firstname, *cin, *address, *email, *phone;
    GtkWidget *combobox5, *spinbutton8, *spinbutton9, *spinbutton10;
    GtkWidget *gender_man_radio, *gender_woman_radio, *check_checkbutton, *espece_checkbutton;

    // Variables
    agent ag_modifie;
    char search_id[30];
	int success=-1;
    // Récupération des widgets
    id = lookup_widget(GTK_WIDGET(button), "entry_search");
    lastname = lookup_widget(GTK_WIDGET(button), "entry29");
    firstname = lookup_widget(GTK_WIDGET(button), "entry26");
    cin = lookup_widget(GTK_WIDGET(button), "entry27");
    address = lookup_widget(GTK_WIDGET(button), "entry28");
    email = lookup_widget(GTK_WIDGET(button), "entry30");
    phone = lookup_widget(GTK_WIDGET(button), "entry46");
    combobox5 = lookup_widget(GTK_WIDGET(button), "combobox5");
    spinbutton8 = lookup_widget(GTK_WIDGET(button), "spinbutton8");
    spinbutton9 = lookup_widget(GTK_WIDGET(button), "spinbutton9");
    spinbutton10 = lookup_widget(GTK_WIDGET(button), "spinbutton10");
    gender_man_radio = lookup_widget(GTK_WIDGET(button), "radiobuttonR1");
    gender_woman_radio = lookup_widget(GTK_WIDGET(button), "radiobuttonR2");
    check_checkbutton = lookup_widget(GTK_WIDGET(button), "checkbutton5");
    espece_checkbutton = lookup_widget(GTK_WIDGET(button), "checkbutton6");

    // Récupération des nouvelles valeurs
    strcpy(search_id, gtk_entry_get_text(GTK_ENTRY(id)));

    strcpy(ag_modifie.last_name, gtk_entry_get_text(GTK_ENTRY(lastname)));
    strcpy(ag_modifie.first_name, gtk_entry_get_text(GTK_ENTRY(firstname)));
    strcpy(ag_modifie.cin, gtk_entry_get_text(GTK_ENTRY(cin)));
    strcpy(ag_modifie.address, gtk_entry_get_text(GTK_ENTRY(address)));
    strcpy(ag_modifie.email, gtk_entry_get_text(GTK_ENTRY(email)));
    strcpy(ag_modifie.phone, gtk_entry_get_text(GTK_ENTRY(phone)));

    ag_modifie.birth_day = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton8));
    ag_modifie.birth_month = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton9));
    ag_modifie.birth_year = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton10));

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gender_man_radio))) {
        strcpy(ag_modifie.gender, "man");
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gender_woman_radio))) {
        strcpy(ag_modifie.gender, "woman");
    }

    ag_modifie.use_check = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_checkbutton));
    ag_modifie.use_espece = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(espece_checkbutton));

    // Gouvernorat depuis le combobox
    int active_index = gtk_combo_box_get_active(GTK_COMBO_BOX(combobox5));
    const char *governorates[] = {"ARIANA", "BEJA", "BIZERTE", "BEN AROUS", "TATAOUIN",
                                  "TOZEUR", "TUNIS", "JENDOUBA", "ZAGHOUANE", "SILIANA",
                                  "SOUSSE", "SIDI BOUZID", "SFAX", "GABES", "GBELI",
                                  "GASSERINE", "GAFSA", "KAIRAOUN", "KEF", "MEDNIN",
                                  "MONASTIR", "MANOUBA", "MAHDIA", "NABEUL"};
    if (active_index >= 0 && active_index < 24) {
        strcpy(ag_modifie.governorate, governorates[active_index]);
    }

    // Appeler la fonction modifier
    success=modifier("agent.txt", search_id, ag_modifie);
	if (success==1)

    // Afficher un message
   { GtkWidget *output_label = lookup_widget(GTK_WIDGET(button), "label_search_result");
    gtk_label_set_text(GTK_LABEL(output_label), "Modification réussie !");
}else{
GtkWidget *output_label = lookup_widget(GTK_WIDGET(button), "label_search_result");
    gtk_label_set_text(GTK_LABEL(output_label), "Modification non réussie !");

}
}
 

 
    












//afficher treeview 


void
on_hercher_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{  GtkWidget *window5,*fixed6;
   GtkWidget *treeview3;


window5=lookup_widget(GTK_WIDGET(button),"window5");

fixed6=lookup_widget(GTK_WIDGET(button),"fixed6");
treeview3=lookup_widget(window5,"treeview3");

  treeview3 = gtk_tree_view_new ();
  gtk_widget_show (treeview3);
  gtk_fixed_put (GTK_FIXED (fixed6), treeview3, 100, 120);
  gtk_widget_set_size_request (treeview3, 595, 350);
  gtk_tree_view_set_rules_hint (GTK_TREE_VIEW (treeview3), TRUE);

afficher(treeview3);
}



//supprimer par id


void
on_DELETE_clicked                      (GtkButton       *button,
                                        gpointer         user_data)

{
    GtkWidget *entry = lookup_widget(GTK_WIDGET(button), "entryid_delete");
    const char *id = gtk_entry_get_text(GTK_ENTRY(entry));

    // Vérification de la case à cocher
    if (supp == 0) {
        GtkWidget *label_status = lookup_widget(GTK_WIDGET(button), "label_supp");
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Vous devez cocher la case pour confirmer la suppression.");
        return;
    }

    // Vérification si l'ID est vide
    if (strlen(id) == 0) {
        GtkWidget *label_status = lookup_widget(GTK_WIDGET(button), "label_supp");
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : ID non fourni.");
        return;
    }

    // Afficher l'ID pour débogage
    g_print("ID récupéré : %s\n", id);

    // Supprimer le compte
    if (supprimer("agent.txt", id)) {
        GtkWidget *label_status = lookup_widget(GTK_WIDGET(button), "label_supp");
        gtk_label_set_text(GTK_LABEL(label_status), "Compte supprimé avec succès.");
    } else {
        GtkWidget *label_status = lookup_widget(GTK_WIDGET(button), "label_supp");
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Compte non trouvé.");
    }
}


void
on_checkbutton_delete_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
supp=1;

}





           

//actualiser
void
on_refresh_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *window5,*w5;
	GtkWidget *treeview3;
	w5=lookup_widget(GTK_WIDGET(button),"window5");
	window5=create_window5();

	gtk_widget_show(window5);

	gtk_widget_hide(w5);

	treeview3=lookup_widget(window5,"treeview3");

	afficher(treeview3);
		
}





void
on_button_SEARCH__DATE_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
 
    // Récupération des widgets
    GtkWidget *entry_date = lookup_widget(GTK_WIDGET(button), "entrydate");
    GtkWidget *label_status = lookup_widget(GTK_WIDGET(button), "label_res");

    if (!entry_date || !label_status) {
        g_print("Erreur : Widgets non trouvés.\n");
        return;
    }

    // Récupération de la date entrée par l'utilisateur
    const char *date_text = gtk_entry_get_text(GTK_ENTRY(entry_date));
    if (!date_text || strlen(date_text) == 0) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Veuillez entrer une date.");
        g_print("Erreur : Date est vide.\n");
        return;
    }

    int jour, mois, annee;
    // Vérification du format de la date (jj/mm/aaaa)
    if (sscanf(date_text, "%d/%d/%d", &jour, &mois, &annee) != 3) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Format de date invalide. Utilisez jj/mm/aaaa.");
        g_print("Erreur : Format de date invalide (%s).\n", date_text);
        return;
    }

    // Vérification de la validité des valeurs de date
    if (jour <= 0 || jour > 31 || mois <= 0 || mois > 12 || annee <= 0) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Date invalide.");
        g_print("Erreur : Date invalide (%d/%d/%d).\n", jour, mois, annee);
        return;
    }

    // Recherche de la réservation avec la date (jour, mois, année)
    reserv res = chercher_reserv_par_date("reservation.txt", jour, mois, annee,"resultats_reservation.txt");
    if (res.jour == -1) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Réservation introuvable pour cette date.");
        g_print("Erreur : Réservation introuvable pour la date %02d/%02d/%d.\n", jour, mois, annee);
        return;
    }

    // Mise à jour de l'interface avec les informations de réservation
    char message[512];  // Taille du tampon
    snprintf(message, sizeof(message), "Réservation trouvée : %s", res.nom);
    gtk_label_set_text(GTK_LABEL(label_status), message);
    g_print("Réservation trouvée : %s (%s)\n", res.nom, res.description);

	GtkWidget *window5,*fixed_date;
	   GtkWidget *treeview2;


	window5=lookup_widget(GTK_WIDGET(button),"window5");

	fixed_date=lookup_widget(GTK_WIDGET(button),"fixed_date");
	treeview2=lookup_widget(window5,"treeview2");

	  treeview2 = gtk_tree_view_new ();
	  gtk_widget_show (treeview2);
	  gtk_fixed_put (GTK_FIXED (fixed_date), treeview2, 100, 120);
	  gtk_widget_set_size_request (treeview2, 595, 350);
	  gtk_tree_view_set_rules_hint (GTK_TREE_VIEW (treeview2), TRUE);

	afficher_res(treeview2);
}











void
on_INSTAGRAM_clicked(GtkButton *button, gpointer user_data)
{
    (void)system("xdg-open 'https://www.instagram.com/parking_parky/'");
}


void
on_FACEBOOK_clicked(GtkButton *button, gpointer user_data)
{
    // Ouverture de l'URL Facebook dans le navigateur par défaut
    (void)system("xdg-open 'https://www.facebook.com/profile.php?id=61570435274062'");
}

