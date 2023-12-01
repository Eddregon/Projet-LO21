#include "Projet.h"


#include <string.h>
#include <stdio.h>
#include <stdlib.h>





// Fonctions sur les regles

elem_BC* creer_regle_vide() {
    elem_BC *nouvelle_regle = (elem_BC*)malloc(sizeof(elem_BC));
    if (nouvelle_regle) {
        nouvelle_regle->premisse = NULL;
        nouvelle_regle->conclusion = NULL;
        nouvelle_regle->prochain = NULL;
    }
    return nouvelle_regle;
}



elem_BC* ajouter_proposition(elem_BC *regle, char *valeur) {
    proposition *nouvelle_prop = (proposition*)malloc(sizeof(proposition));
    nouvelle_prop->value = strdup(valeur);
    nouvelle_prop->next = regle->conclusion; // Pointe directement vers la conclusion existante

    if (regle->premisse == NULL) {
        // Si la prémisse est vide, la nouvelle proposition devient la première de la liste
        regle->premisse = nouvelle_prop;
        nouvelle_prop->prev = NULL;
    } else {
        // Sinon, insérer la nouvelle proposition juste avant la conclusion
        if (regle->conclusion && regle->conclusion->prev) {
            regle->conclusion->prev->next = nouvelle_prop;
            nouvelle_prop->prev = regle->conclusion->prev;
            regle->conclusion->prev = nouvelle_prop;
        } else {
            // Dans le cas où il n'y a pas encore de conclusion
            proposition *derniere = regle->premisse;
            while (derniere->next != NULL) {
                derniere = derniere->next;
            }
            derniere->next = nouvelle_prop;
            nouvelle_prop->prev = derniere;
        }
    }
    return regle;
}



elem_BC* creer_conclusion(elem_BC *regle, char *valeur) {
    // Si une conclusion existe déjà, remplacez simplement sa valeur.
    if (regle->conclusion != NULL) {
        free(regle->conclusion->value);
        regle->conclusion->value = strdup(valeur);
    } else {
        // Création de la nouvelle conclusion
        proposition *concl = (proposition*)malloc(sizeof(proposition));
        concl->value = strdup(valeur);
        concl->next = NULL; // La conclusion est le dernier élément, donc next est NULL
        concl->prev = NULL; // Initialisé à NULL, sera mis à jour si nécessaire

        if (regle->premisse != NULL) {
             // insérer la conclusion à la fin de la liste
            proposition *tmp = regle->premisse;
            while (tmp->next != NULL) {
                tmp = tmp->next;
            }
            tmp->next = concl;
            concl->prev = tmp;
        } 

        // Mettre à jour le pointeur de conclusion de la règle
        regle->conclusion = concl;
    }

    return regle;
}



int appartient_premisse_recursif(proposition *courante, proposition *conclusion, char *valeur) {
    // Vérifier si on est arrivé à la fin de la prémisse ou à la conclusion
    if (courante == NULL || courante == conclusion) {
        return 0;
    }

    // Vérifier si la valeur courante correspond
    if (strcmp(courante->value, valeur) == 0) {
        return 1;
    }

    // Appel récursif avec la proposition suivante
    return appartient_premisse_recursif(courante->next, conclusion, valeur);
}



int appartient_premisse(elem_BC *regle, char *valeur) {
    // Vérifier si la règle ou la valeur est NULL
    if (regle == NULL || valeur == NULL) {
        return 0;
    }

    // Appel initial de la fonction récursive
    return appartient_premisse_recursif(regle->premisse, regle->conclusion, valeur);
}



elem_BC* supprimer_proposition(elem_BC *regle, char *valeur) {
    if (regle == NULL || valeur == NULL || regle->premisse == NULL) {
        return regle; // Rien à faire si la règle est vide ou la valeur est NULL
    }

    proposition *courante = regle->premisse;
    proposition *precedente = NULL;

    while (courante != NULL && courante != regle->conclusion) {
        if (strcmp(courante->value, valeur) == 0) {
            if (precedente == NULL) {
                // La proposition à supprimer est la première de la prémisse
                regle->premisse = courante->next;
            } else {
                // Relier le précédent au suivant, en sautant la proposition actuelle
                precedente->next = courante->next;
                if (courante->next != NULL) {
                    courante->next->prev = precedente;
                }
            }
            // Libérer la mémoire de la proposition supprimée
            free(courante->value);
            free(courante);
            break;
        }
        precedente = courante;
        courante = courante->next;
    }

    return regle;
}



int premisse_est_vide(elem_BC *regle) {
    if (regle == NULL) {
        return 1; // Considérer la prémisse comme vide si la règle elle-même est NULL
    }

    return (regle->premisse == NULL);
}



proposition* premiere_proposition(elem_BC *regle) {
    if (regle == NULL || regle->premisse == NULL) {
        return NULL; // Retourner NULL si la règle est NULL ou si la prémisse est vide
    }

    return regle->premisse;
}



proposition* acceder_conclusion(elem_BC *regle) {
    if (regle == NULL) {
        return NULL; // Retourner NULL si la règle est NULL
    }

    return regle->conclusion;
}





// Fonctions sur la base de connaissances

liste_BC* creer_base_vide() {
    liste_BC *base = (liste_BC*)malloc(sizeof(liste_BC));
    if (base) {
        base->BC = NULL;
        base->nb_elem = 0;
    }
    return base;
}



void ajouter_regle(liste_BC *base, elem_BC *nouvelle_regle) {
    if (base == NULL || nouvelle_regle == NULL) {
        return; // Ne rien faire si la base ou la règle est NULL
    }

    if (base->BC == NULL) {
        // Si la base est vide, ajoutez cette règle en tant que première règle
        base->BC = nouvelle_regle;
    } else {
        // Sinon, trouvez la fin de la liste et ajoutez la règle
        elem_BC *tmp = base->BC;
        while (tmp->prochain != NULL) {
            tmp = tmp->prochain;
        }
        tmp->prochain = nouvelle_regle;
    }

    base->nb_elem++; // Mettre à jour le compteur de règles
}



elem_BC* acceder_regle_tete(liste_BC *base) {
    if (base == NULL || base->BC == NULL) {
        return NULL; // Retourner NULL si la base est NULL ou vide
    }

    return base->BC;
}





// Fonctions complémentaires

liste_BF* creer_base_vide_BF() {
    liste_BF *base = (liste_BF*)malloc(sizeof(liste_BF));
    if (base) {
        base->BF = NULL;
        base->nb_elem = 0;
    }
    return base;
}



void ajouter_proposition_BF(liste_BF *base, char *valeur) {

    proposition *nouvelle_prop = (proposition*)malloc(sizeof(proposition));
    nouvelle_prop->value = strdup(valeur);
    nouvelle_prop->next = NULL; // Pointe directement vers la conclusion existante

    if (base != NULL){
        if (base->BF == NULL) {
            // Si la base est vide, la nouvelle proposition devient la première de la liste de faits
            base->BF = nouvelle_prop;
            nouvelle_prop->prev = NULL;
        } else {
            // Sinon, trouvez la fin de la liste et ajoutez la proposition
            proposition *tmp = base->BF;
            while (tmp->next != NULL) {
                tmp = tmp->next;
            }
            nouvelle_prop->prev = tmp;
            tmp->next = nouvelle_prop;
        }

        base->nb_elem++; // Mettre à jour le compteur de faits
    }
}



liste_BC * supprimer_regle_vide(liste_BC *base) {

    if (base == NULL || base->BC == NULL) {
        return base; // Rien à faire si la base est vide
    }

    elem_BC *regle = base->BC;
    if(premisse_est_vide(regle)){
        // Supprimer la première règle de la base
        base->BC = base->BC->prochain;
        // on libère la memoire
        if (regle->conclusion != NULL) {
            free(regle->conclusion->value);
            free(regle->conclusion);
        }
        free(regle);
        // on decremente le compteur du nombre de regles
        base->nb_elem--;
    }
    else {
        while (regle != NULL) {
            if (premisse_est_vide(regle->prochain)) {
                // Supprimer la règle de la base
                if (regle->prochain->prochain != NULL){
                    regle->prochain = regle->prochain->prochain;
                }

                // on libère la memoire
                if (regle->conclusion != NULL) {
                    free(regle->conclusion->value);
                    free(regle->conclusion);
                }
                free(regle);
                // on decremente le compteur du nombre de regles
                base->nb_elem--;
            } else {
                // Passer à la règle suivante
                regle = regle->prochain;
            }
        }

    }

    return base;
}



int charger_base_de_connaissances_et_faits(const char *nom_fichier, liste_BC *base_connaissances, liste_BF *base_faits) {
    FILE *fichier = fopen(nom_fichier, "r");
    printf("Chargement du fichier %s...\n", nom_fichier);
    char ligne[1024];
    char *token;

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 0; //indique que le chargement s'est mal passé
    }

    while (fgets(ligne, sizeof(ligne), fichier)) {
        // Enlever le saut de ligne à la fin si présent
        ligne[strcspn(ligne, "\n")] = 0;

        // Vérifier si la ligne contient une règle ou un fait
        if (strstr(ligne, "=>")) { // C'est une règle
            elem_BC *nouvelle_regle = creer_regle_vide();

            // Extraire les prémisses
            token = strtok(ligne, ",");
            while (token != NULL && strstr(token, "=>") == NULL) {
                ajouter_proposition(nouvelle_regle, token);
                token = strtok(NULL, ",");
            }

            // Extraire la conclusion (après "=>")
            if (token != NULL) {
                token = strtok(NULL, "=>");
                if (token != NULL) {
                    creer_conclusion(nouvelle_regle, token);
                }
            }

            // Ajouter la règle à la base de connaissances
            ajouter_regle(base_connaissances, nouvelle_regle);
        } else { // C'est un fait
            // Ajouter le fait à la base de faits
            ajouter_proposition_BF(base_faits, ligne);
        }
    }

    fclose(fichier);
    printf("Chargement terminé.\n");
    return 1; //indique que le chargement s'est bien passé
}
