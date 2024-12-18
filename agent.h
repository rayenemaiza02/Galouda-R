#ifndef agent_H_INCLUDED
#define agent_H_INCLUDED
#include <stdio.h>
#include <gtk/gtk.h>


typedef struct agent  {
    char id[30];
    char last_name[50];
    char first_name[50];
    char cin[50]; 
    char address[100];
    char governorate[50];
    char email[100];
    int birth_day;
    int birth_month;
    int birth_year;
    char gender[50]; 
    int use_check; 
    int use_espece; 
    char phone[100]; 
} agent;

typedef struct {
    int id;                      // Identifiant
    char nom[50];                // Nom
    char categorie[50];          // Catégorie
    char description[200];       // Description
    char telephone[15];          // Téléphone
    int jour;                    // Jour
    int mois;                    // Mois
    int annee;                   // Année;
} reserv;


reserv chercher_reserv_par_date(const char *filename, int jour, int mois, int annee, const char *output_filename) ;
int ajouter(char *filename, agent agent);
int modifier(char *filename, char *id, agent ag_modifie);
int supprimer(const char *filename, const char *id);
agent chercher(char *filename, char *id);
void afficher(GtkWidget *liste);
void afficher_res(GtkWidget *liste);
int verifier(char averif[30]);




#endif


















