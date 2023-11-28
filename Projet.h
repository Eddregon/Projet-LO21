
#ifndef PROJET_H
#define PROJET_H

#include <stdlib.h>
#include <stdio.h>



// Défininition de la structure d'une proposition
typedef struct prop{
    char *value;
    struct prop * next;
    struct prop * prev;
} proposition;

// Défininition de la structure d'un element de la base de connaissances (donc une regle).
// La base de connaissances est une liste chainée d'éléments.
typedef struct regle{
    proposition * premisse; // pointeur sur la première proposition de la prémisse.
    proposition * conclusion; // pointeur sur la dernière proposition, donc sur la conclusion de la règle.
    struct regle * prochain;
} elem_BC;



// Fonctions sur les regles

elem_BC* creer_regle_vide();

elem_BC* ajouter_proposition(elem_BC *regle, char *valeur);

elem_BC* creer_conclusion(elem_BC *regle, char *valeur);

int appartient_premisse(elem_BC *regle, char *valeur);
    //Fonction appelée par appartient_premisse
    int appartient_premisse_recursif(proposition *courante, proposition *conclusion, char *valeur);

elem_BC* supprimer_proposition(elem_BC *regle, char *valeur);

int premisse_est_vide(elem_BC *regle);

proposition* premiere_proposition(elem_BC *regle);

proposition* acceder_conclusion(elem_BC *regle);





// Création d'une structure, qui sera utilisé pour créer une variable
    // qui pointera sur le premier element de la liste base de connaissances,
    // et retient le nombre d'elements de la base de connaissances (donc le nombre de règles).
typedef struct {
    elem_BC * BC;
    int nb_elem;
} liste_BC;

// La liste de faits est une liste chainée de propositions
// Création d'une structure, qui sera utilisé pour créer une variable
    // qui pointera sur le premier element de la liste base de connaissances,
    // et retient le nombre d'elements de la base de faits.
typedef struct {
    proposition * BF;
    int nb_elem;
} liste_BF;



// Fonctions sur la base de connaissance et la base de faits
liste_BC* creer_base_vide();

void ajouter_regle(liste_BC *base, elem_BC *nouvelle_regle);

elem_BC* acceder_regle_tete(liste_BC *base);



// Fonctions complémentaires

liste_BF* creer_base_vide_BF();

void ajouter_proposition_BF(liste_BF *base, proposition *nouvelle_proposition);

void charger_base_de_connaissances_et_faits(const char *nom_fichier, liste_BC *base_connaissances, liste_BF *base_faits);



#endif