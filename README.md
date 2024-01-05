# Projet-LO21

Projet LO21 - Système Expert

Ce projet, réalisé dans le cadre de l'unité de valeur LO21 à l'Université de Technologie, consiste à développer un système expert capable de réaliser des inférences logiques. Le système se base sur une base de connaissances et une base de faits, avec un moteur d'inférence pour traiter et déduire de nouvelles informations.

# Prérequis
    Compilateur C (GCC recommandé)
    GNU Make (Pour les utilisateurs de Windows, MinGW ou Cygwin avec mingw32-make est nécessaire)
    Structure du Projet
    main.c : Point d'entrée du programme.
    projet.c : Contient la logique du système expert.
    projet.h : Fichier d'en-tête pour projet.c.
    Makefile : Fichier pour automatiser la compilation.
    Sauvegarde.txt : Fichier exemple contenant les règles et faits initiaux.
    Compilation

    Pour compiler le programme, ouvrez votre terminal ou PowerShell (Windows) et naviguez vers le répertoire du projet. Exécutez la commande suivante :

    make

Cela générera un exécutable nommé "Projet" (ou un autre nom si modifié dans le Makefile).

# Exécution
Après la compilation, exécutez le programme en utilisant la commande :


    ./Projet

Sur Windows, si vous utilisez MinGW ou Cygwin, la commande sera similaire.

# Nettoyage
Pour supprimer les fichiers objets et l'exécutable, utilisez la commande :


make clean