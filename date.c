#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "date.h"
#include <string.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <gtk/gtk.h>
#include "interface.h"
#include "callbacks.h"
#include "support.h"
enum{
	ID_RES,
	NUM,
        ZONE,
	DUREE,
	PAIMENT,
	COLUMNS1
};

// Fonction pour afficher les réservations à une date donnée
void afficher_reservations_par_date(char *filename, int day, int month, int year) {
    reservation res;
    int found = 0; // Variable pour vérifier si des réservations ont été trouvées
    FILE *f = fopen(filename, "r");

    if (f != NULL) {
        // Lire les champs avec fscanf : %s pour les chaînes et %d pour les entiers
        while (fscanf(f, "%s %s %s %s %s %d %d %d ", 
                      res.id_res, res.num_res, res.parking_zone, &res.duree_res, 
                      &res.paiement, &res.day, &res.month, &res.year) == 8) { // Vérifie si 8 champs sont lus
            // Vérifie si la réservation correspond à la date donnée
            if (res.day == day && res.month == month && res.year == year) {
                // Affichage des réservations correspondantes à la date
                printf("Reservation ID: %s | Reservation Number: %s | Parking Zone: %s | Duration: %c | Payment: %c | Date: %02d/%02d/%04d\n",
                       res.id_res, res.num_res, res.parking_zone, 
                       res.duree_res, res.paiement, 
                       res.day, res.month, res.year);
                found = 1;
            }
        }
        fclose(f);

        // Si aucune réservation n'a été trouvée pour cette date
        if (!found) {
            printf("Aucune réservation trouvée pour la date %02d/%02d/%04d.\n", day, month, year);
        }
    } else {
        printf("Erreur lors de l'ouverture du fichier de réservations.\n");
    }
}











void afficher_res(GtkWidget *liste)
{



    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    reservation res;
    FILE *f;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));

    // Si le store est NULL, cela signifie que le TreeView n'a pas encore de modèle
    if (store == NULL) {
        store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

        // Ajout des colonnes au TreeView
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("id_res", renderer, "text", ID_RES, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("num_res", renderer, "text", NUM, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);


        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("parking_zone", renderer, "text", ZONE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);



        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("duree_res", renderer, "text", DUREE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);


	renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("paiement", renderer, "text", PAIMENT, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);


        


      
        

        // Définir le modèle du TreeView
        gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
        g_object_unref(store);
    }

    // Ouvrir le fichier pour lire les données
    f = fopen("reservation.txt", "r");
    if (f == NULL) {
        g_print("Erreur : Le fichier reservation.txt n'a pas pu être ouvert.\n");
        return;
    }

    // Lire les données et les ajouter au store
    while (fscanf(f, "%s %s %s %s %s  ", 
                      res.id_res, res.num_res, res.parking_zone, &res.duree_res, 
                      &res.paiement) != EOF) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, ID_RES, res.id_res, NUM, res.num_res, ZONE, res.parking_zone, DUREE, res.duree_res,
                           PAIMENT, res.paiement, -1);
    }

    fclose(f);
}























/*void afficher_reservations_par_date(char *filename, int day, int month, int year)
 {
    reservation res;
    int found = 0;
    FILE *f = fopen(filename, "r");

    if (f != NULL) {
        // Parcours des réservations dans le fichier
        while (fscanf(f, "%d %d %d %d %d %d\n", &res.id_reservation, &res.id_citoyen,
                      &res.day, &res.month, &res.year, &res.parking_spot) != EOF) {
            // Vérifie si la réservation correspond à la date donnée
            if (res.day == day && res.month == month && res.year == year) {
                printf("Reservation ID: %d | Citizen ID: %d | Date: %02d/%02d/%04d | Parking Spot: %d\n",
                       res.id_reservation, res.id_citoyen, res.day, res.month, res.year, res.parking_spot);
                found = 1;
            }
        }
        fclose(f);

        // Si aucune réservation n'a été trouvée pour cette date
        if (!found) {
            printf("Aucune réservation trouvée pour la date %02d/%02d/%04d.\n", day, month, year);
        }
    } else {
        printf("Erreur lors de l'ouverture du fichier de réservations.\n");
    }
}*/
