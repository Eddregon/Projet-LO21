#include"Projet.h"

int main(){

    // On crée une base de connaissance vide
    base_connaissances = creer_base_vide();
    // On crée une base de faits vide
    base_faits = creer_base_vide_BF();

    // on charge les valeurs de la base de connaissances et de la base de faits et on les introduits dans les bases vides à l'aide des fonctions nécessaires
    charger_base_de_connaissances_et_faits("base_de_connaissances.txt", base_connaissances, base_faits);

    //Début du moteur d'inférence

        // on crée un pointeur sur la première proposition de la base de faits
        proposition * fait = base_faits->BF;
        // on crée un pointeur sur la première regle de la base de connaissances
        regle * regle = acceder_regle_tete(base_connaissances);

        // tant qu'il y a un fait dans la base de faits
        while (fait!=NULL){
            // tant qu'il y a une regle dans la base de connaissances
            while (regle!=NULL){
                // si le fait est dans la premisse de la regle
                if (appartient_premisse(regle, fait->value)){
                    // on supprime le fait de la premisse de la regle
                    supprimer_proposition(regle, fait->value);
                    // si la premisse est vide
                    if (premisse_est_vide(regle)){
                        // on ajoute la conclusion à la base de faits
                        ajouter_proposition(base_faits, acceder_conclusion(regle)->value);
                    }
                }
                // on passe à la regle suivante
                regle = regle->next;
            }

            // On regarde si il y a un prochain fait dans la base de faits sinon on retourne null et on arrete le moteur d'inference
            fait = fait->next;
        }

    // On affiche la base de faits (qui affichera donc la base de faits avec les nouveaux faits ajoutés après l'éxecution du moteur d'inference)
    proposition * liste_fait = base_faits->BF;
    while (liste_fait!=NULL){
        printf("%s\n", liste_fait->value);
        liste_fait = liste_fait->next;
    }
}

// moteur d'inférence
    // on a une base de faits, avec des propositions de faits certains
    // on a une base de connaissances, avec des propositions etant la premisse et une conclusion

    // on va prendre les propositions de faits certains un par un jusqu'il y en a plus
    // puis regarder dans chaque regle si cette proposition est present, jusqu'a la dernière règle
    // s'il est present on enleve cette propositon de la premisse de la regle en question
    // si il n'y a plus de premisse alors on ajoute la conclusion a la base de faits
        // besoin de fonction ajout proposition a la base de faits, et verifier si la proposition n'appartient pas déja a la base de faits
    // si next du fait different de null alors le fait qu'on verifie, prend la valeur de next de fait
    // sinon fin du programme on affiche la base de faits