
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"agent.h"
#include <gtk/gtk.h>
#include "interface.h"
#include "callbacks.h"
#include "support.h"


agent ag;
//treeview3
enum{
    ID,
    LAST_NAME,
    FIRST_NAME,
    CIN, 
    ADDRESS,
    EMAIL,
    PHONE,
    COLUMNS

};

enum{
	ID_RES,
	NOM,
	CATEGORIE,
	DESCRIPTION,
	TELEPHONE,
	COLUMNS1
};


//fct ajouter agent


int ajouter(char *filename, agent agent) {
    FILE *f = fopen(filename, "a");
    if (f != NULL) {
        fprintf(f, "%s %s %s %s %s %s %s %d %d %d %s %d %d %s\n",
                agent.id, agent.last_name, agent.first_name, agent.cin,
                agent.address, agent.governorate, agent.email,
                agent.birth_day, agent.birth_month, agent.birth_year,
                agent.gender, agent.use_check, agent.use_espece, agent.phone);
        fclose(f);
        return 1;
    }
    return 0;
}


int modifier(char *filename, char *id, agent ag_modifie) {
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w"); // Fichier temporaire pour les modifications

    agent ag;
    int modification_effectuee = 0; // Variable pour suivre si l'ID a été modifié

    if (file == NULL || temp == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier\n");
        return 0; // Retourner 0 si problème avec les fichiers
    }

    // Parcourir chaque ligne pour trouver et modifier l'agent
    while (fscanf(file, "%s %s %s %s %s %s %s %d %d %d %s %d %d %s\n",
                  ag.id, ag.last_name, ag.first_name, ag.cin,
                  ag.address, ag.governorate, ag.email, &ag.birth_day,
                  &ag.birth_month, &ag.birth_year, ag.gender,
                  &ag.use_check, &ag.use_espece, ag.phone) != EOF) {
        if (strcmp(ag.id, id) == 0) {
            // Écrire les nouvelles données dans le fichier temporaire
            fprintf(temp, "%s %s %s %s %s %s %s %d %d %d %s %d %d %s\n",
                    id, ag_modifie.last_name, ag_modifie.first_name, ag_modifie.cin,
                    ag_modifie.address, ag_modifie.governorate, ag_modifie.email, 
                    ag_modifie.birth_day, ag_modifie.birth_month, ag_modifie.birth_year,
                    ag_modifie.gender, ag_modifie.use_check, ag_modifie.use_espece, ag_modifie.phone);
            modification_effectuee = 1; // Modification réussie
        } else {
            // Réécrire les autres lignes sans modification
            fprintf(temp, "%s %s %s %s %s %s %s %d %d %d %s %d %d %s\n",
                    ag.id, ag.last_name, ag.first_name, ag.cin, ag.address, ag.governorate,
                    ag.email, ag.birth_day, ag.birth_month, ag.birth_year,
                    ag.gender, ag.use_check, ag.use_espece, ag.phone);
        }
    }

    fclose(file);
    fclose(temp);

    // Remplacer le fichier original par le fichier temporaire
    remove(filename);
    rename("temp.txt", filename);

    if (modification_effectuee) {
        return 1; // Retourner 1 si la modification a réussi
    } else {
        return 0; // Retourner 0 si l'ID n'a pas été trouvé
    }
}



//fct supp agent

int supprimer(const char *filename, const char *id) 
{

    if (filename == NULL || id == NULL || strlen(id) == 0) {
        printf("Erreur : Paramètres invalides (fichier ou ID).\n");
        return 0;
    }

    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", filename);
        return 0;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        fclose(f);
        printf("Erreur : Impossible de créer le fichier temporaire.\n");
        return 0;
    }

    agent ag;
    char line[1024];
    int found = 0;

    // Lire le fichier ligne par ligne
    while (fgets(line, sizeof(line), f)) {
        // Vérifier si la ligne est trop longue
        if (strchr(line, '\n') == NULL && !feof(f)) {
            printf("Erreur : Ligne trop longue, ignorée.\n");
            continue;
        }

        // Utilisation de sscanf pour lire la ligne et remplir la structure 'agent'
        if  (sscanf(line, "%s %s %s %s %s %s %s %d %d %d %s %d %d %s\n",
                  ag.id, ag.last_name, ag.first_name, ag.cin,
                  ag.address, ag.governorate, ag.email, &ag.birth_day,
                  &ag.birth_month, &ag.birth_year, ag.gender,
                  &ag.use_check, &ag.use_espece, ag.phone) == 14) {

            // Supprimer les caractères invisibles dans l'ID lu
            char *newline = strchr(ag.id, '\n');
            if (newline) *newline = '\0';

            // Vérifier si l'ID correspond
            if (strcmp(ag.id, id) == 0) {
                found = 1; // Marquer comme trouvé
                continue;  // Ne pas écrire cette ligne dans le fichier temporaire
            }
        } else {
            printf("Ligne ignorée : %s\n", line);
        }

        // Écrire les lignes non supprimées dans le fichier temporaire
        fprintf(temp, "%s", line);
    }

    fclose(f);
    fclose(temp);

    if (found) {
        if (remove(filename) != 0) {
            printf("Erreur : Impossible de supprimer le fichier original.\n");
            return 0;
        }
        if (rename("temp.txt", filename) != 0) {
            printf("Erreur : Impossible de renommer le fichier temporaire.\n");
            return 0;
        }
        return 1;
    } else {
        remove("temp.txt");
        printf("Erreur : Compte avec l'ID %s introuvable.\n", id);
        return 0;
    }
}






//afficher treeview3

   
void afficher(GtkWidget *liste)
{
    

    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    agent ag;
    FILE *f;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));

    // Si le store est NULL, cela signifie que le TreeView n'a pas encore de modèle
    if (store == NULL) {
        store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

        // Ajout des colonnes au TreeView
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("id", renderer, "text", ID, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("last_name", renderer, "text", LAST_NAME, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("first_name", renderer, "text", FIRST_NAME, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("cin", renderer, "text", CIN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("address", renderer, "text", ADDRESS, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("email", renderer, "text", EMAIL, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("phone", renderer, "text", PHONE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // Définir le modèle du TreeView
        gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
        g_object_unref(store);
    }

    // Ouvrir le fichier pour lire les données
    f = fopen("agent.txt", "r");
    if (f == NULL) {
        g_print("Erreur : Le fichier agent.txt n'a pas pu être ouvert.\n");
        return;
    }

    // Lire les données et les ajouter au store
    while (fscanf(f, "%s %s %s %s %s %s %s %d %d %d %s %d %d %s\n", ag.id, ag.last_name, ag.first_name, ag.cin,
                  ag.address, ag.governorate, ag.email, &ag.birth_day, &ag.birth_month, &ag.birth_year,
                  ag.gender, &ag.use_check, &ag.use_espece, ag.phone) != EOF) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, ID, ag.id, LAST_NAME, ag.last_name, FIRST_NAME, ag.first_name, CIN, ag.cin,
                           ADDRESS, ag.address, EMAIL, ag.email, PHONE, ag.phone, -1);
    }

    fclose(f);
}




//chercher agent

agent chercher(char *filename, char *id) {
    agent agent;
    int found = 0; // Pour indiquer si l'agent a été trouvé
    FILE *f = fopen(filename, "r");

    // Initialisation au cas où le fichier n'existe pas ou l'agent n'est pas trouvé
    strcpy(agent.id, "-1");

    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return agent;
    }

    // Parcours du fichier
    while (!found && fscanf(f, "%s %s %s %s %s %s %s %d %d %d %s %d %d %s\n",
                            agent.id, agent.last_name, agent.first_name, agent.cin,
                            agent.address, agent.governorate, agent.email,
                            &agent.birth_day, &agent.birth_month, &agent.birth_year,
                            agent.gender, &agent.use_check, &agent.use_espece, agent.phone) != EOF) {
        if (strcmp(agent.id, id) == 0) {
            found = 1;
        }
    }

    fclose(f);
    if (!found) {
        strcpy(agent.id, "-1"); // Indiquer que l'agent n'a pas été trouvé
    }
    return agent;
}


//recherche reservation par date

reserv chercher_reserv_par_date(const char *filename, int jour, int mois, int annee, const char *output_filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur : Impossible d'ouvrir le fichier");
        reserv empty = {-1};  // Retourner une réservation "vide" en cas d'erreur
        return empty;
    }

    reserv result;
    result.jour = -1;  // Valeur par défaut si aucune réservation n'est trouvée

    // Ouvrir le fichier de sortie pour stocker les résultats
    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        perror("Erreur : Impossible d'ouvrir le fichier de sortie");
        fclose(file);
        return result;
    }

    char line[512];
    int found_first = 0;  // Indicateur pour savoir si la première réservation a été trouvée

    // Lire les lignes du fichier
    while (fgets(line, sizeof(line), file)) {
        reserv temp;
        // Extraire les données de chaque ligne
        if (sscanf(line, "%d|%49[^|]|%49[^|]|%199[^|]|%14[^|]|%d|%d|%d", 
                   &temp.id, temp.nom, temp.categorie, temp.description, 
                   temp.telephone, &temp.jour, &temp.mois, &temp.annee) == 8) {
            // Vérifier si la date correspond à celle recherchée
            if (temp.jour == jour && temp.mois == mois && temp.annee == annee) {
                // Si c'est la première réservation trouvée, on la garde pour retour
                if (!found_first) {
                    result = temp;  // Sauvegarder la première réservation trouvée
                    found_first = 1;
                }

                // Enregistrer cette réservation dans le fichier de sortie
                fprintf(output_file, "%d|%s|%s|%s|%s|%d|%d|%d\n", 
                        temp.id, temp.nom, temp.categorie, temp.description, 
                        temp.telephone, temp.jour, temp.mois, temp.annee);
            }
        }
    }

    fclose(file);
    fclose(output_file);

    // Retourner la première réservation trouvée
    return result;  
}
   
void afficher_res(GtkWidget *liste) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    reserv res;
    FILE *f;
    char line[512];  // Taille du buffer pour lire chaque ligne du fichier

    // Vérifier si le modèle du TreeView est déjà initialisé
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));
    if (store == NULL) {
        // Créer un nouveau modèle pour le TreeView
        store = gtk_list_store_new(5, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

        // Créer et ajouter les colonnes pour afficher les informations de la réservation
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID_RES", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Catégorie", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Description", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Téléphone", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // Définir le modèle du TreeView
        gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
        g_object_unref(store);  // Libérer la référence après l'association avec le TreeView
    }

    // Ouvrir le fichier pour lire les données
    f = fopen("resultats_reservation.txt", "r");
    if (f == NULL) {
        g_print("Erreur : Le fichier reservation.txt n'a pas pu être ouvert.\n");
        return;
    }

    // Lire chaque ligne du fichier et ajouter les réservations au TreeView
    while (fgets(line, sizeof(line), f)) {
        // Analyser la ligne et extraire les informations
        if (sscanf(line, "%d|%49[^|]|%49[^|]|%199[^|]|%14[^|]", &res.id, res.nom, res.categorie, res.description, res.telephone) == 5) {
            // Ajouter la ligne au TreeView
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                               0, res.id,
                               1, res.nom,
                               2, res.categorie,
                               3, res.description,
                               4, res.telephone,
                               -1);  // Terminer la ligne
        }
    }

    fclose(f);  // Fermer le fichier
}

//verifier l'id

int verifier(char averif[30])
{
int v=0;
agent ag;
FILE *f=NULL;
    f=fopen("agent.txt","r");

    if (f!=NULL)
    {
     while(fscanf(f, "%s %s %s %s %s %s %s %d %d %d %s %d %d %s\n", ag.id, ag.last_name, ag.first_name, ag.cin,
                  ag.address, ag.governorate, ag.email, &ag.birth_day, &ag.birth_month, &ag.birth_year,
                  ag.gender, &ag.use_check, &ag.use_espece, ag.phone) != EOF)
    {	
        if ( strcmp(averif,ag.id)==0)
        {
       v=1;
	
        }

         }
    
    }return v;
}








