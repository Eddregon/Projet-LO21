#include"Projet.h"

int main(){

    return 1;
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