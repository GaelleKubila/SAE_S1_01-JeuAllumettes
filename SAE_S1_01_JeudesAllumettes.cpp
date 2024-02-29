#include <stdio.h>
#include <iostream>
using namespace std;
#include <cstring>
#include <stdlib.h>
#include <time.h>



///// FONCTION N°1

int Saisie(char nom[21], char* niv, int* nballumettes, char preums)
{

    // on initialise plusieurs variables de stockage pour se simplifier la vie.
    // explications un peu + tard dans le code source

    int ValeurPrem;
    char idordi[] = "Ordinateur";

    // début réel du paramétrage


    cout << "Saisir votre nom - 20 caractères max" << endl;
    cin >> nom;


    do {

        cout << "Choississez la difficulté de l'ordinateur | N = mode naif, E = mode expert" << endl;
        cin >> *niv;

    }


    while (*niv == (!('n') && !('N') && !('e') && ('E')));

    if (*niv == 'e') { /// harmonisation de la casse pour éviter de se compliquer la vie dans le reste du programme

        *niv = 'E';
    }

    if (*niv == 'n') {

        *niv = 'N';
    }


    do {

        cout << "Saisir le nombre d'allumettes" << endl;
        cin >> *nballumettes;
    }

    while ((*nballumettes <= 0) && (*nballumettes > 30));


    // choix du premier joueur

    do {

        cout << "Qui sera votre premier joueur? - J = joueur | O - ordinateur" << endl;
        cin >> preums;

    }

    while ((!(preums == 'J') && !(preums == 'O') && !(preums == 'j') && !(preums == 'o'))); // donc, si preums est différent de (J ou O)


    switch (preums) {

    case 'J': ValeurPrem = 0; break;
    case 'j': ValeurPrem = 0; break;
    case 'O': ValeurPrem = 1; break;
    case 'o': ValeurPrem = 1; break;
    }

    return ValeurPrem;

}




///// FONCTION N°2

void Affiche(int nb_allumettes) {

    int i;

    for (i = 1; i <= nb_allumettes; i++) {

        cout << "-------";
        cout << "\n";

        if (i % 5 == 0) {

            cout << endl;
        }
    }


}

//// sera utilisé dans la fonction n°3

int miseAjour(int nb_allumettes, int nb) {

    nb_allumettes = nb_allumettes - nb;

    return nb_allumettes;

}

//// sera utilisé dans la fonction n°4

int generationExpert() {

    int nb;

    //initialise l'aléatoire

    srand(time(NULL));

    nb = (4 * rand()) + 1;

    return nb;

}

int determineCoup(char mode, int nbAllumettes) {

    int final;

    final = 0;

    //initialise l'aléatoire

    do {

        switch (mode) {

        case 'N':  final = rand() % 3; break; // choix du hasard naïf
        case 'E':  final = (generationExpert() % 3) + 1; break; // formule 4k+1 gagnante

        }
    }

    while ((final >= 30) || (final <= 0)); // le tout en respectant les règles

    return final;


}


///// FONCTION N°4 - terminée

int joueOrdi(char niv, int nbAllumettes) {

    int choix;

    cout << "ORDI joue" << endl;

    choix = determineCoup(niv, nbAllumettes);

    cout << "Ordi a retiré " << choix << " allumettes!" << endl;

    return choix;

}

/////à utiliser dans

///// FONCTION N°5 - terminée

int joueJoueur(char nom[21], int nbAllumettes)
{
    int coupValide, nbDemande;

    cout << nom << " joue!" << endl;
    coupValide = 0;


    do

    {
        cout << "Saisir nombre d'allumettes" << endl;
        cin >> nbDemande;

        switch (nbDemande) {

        case 0:
            cout << "Abandon du joueur" << endl;
            coupValide = 1;
            break;
        case 1:
        case 2:
        case 3:
            cout << "OK!" << endl;
            coupValide = 1;
            break;
        default:
            cout << "Erreur : saisir un nombre entre 0 et 3" << endl;
            break;

        }

    }

    while (coupValide != 1);

    return nbDemande;


}

///// FONCTION N°3

int JeuAlterne(int tour, int* nb_allumettes, char nom[21], char* niv) {

    int retire, total;

    total = *nb_allumettes;
    retire = 0;

    /// c'est là que le tour défini comme 0 ou 1 dans la fonction Saisie prend tout son sens

    switch (tour) {

    case 0: retire = joueJoueur(nom, *nb_allumettes); tour = 1; break;
    case 1: retire = joueOrdi(*niv, *nb_allumettes); tour = 0; break;
    }

    *nb_allumettes = miseAjour(total, retire);

    return tour;

}


///// procédure principale

int main()
{
    //initialise l'aléatoire

    srand(time(NULL));

    // paramètres de saisie 

    int Nombre_Allumettes;
    char NomJoueur[21];
    char QuiCommence, NiveauOrdi;


    // initialisation des variables de départ (pour ne pas qu'elles soient indéfinies au tout début)

    Nombre_Allumettes = 12;
    NiveauOrdi = 'A';
    QuiCommence = 'A';


    int TourID;


    TourID = Saisie(NomJoueur, &NiveauOrdi, &Nombre_Allumettes, QuiCommence);

    // boucle de jeu

    do {

        Affiche(Nombre_Allumettes);
        TourID = JeuAlterne(TourID, &Nombre_Allumettes, NomJoueur, &NiveauOrdi);

    }

    while (Nombre_Allumettes > 0);


    // détermine le vainqueur

    if (TourID == 1)
    {

        cout << "L'ordinateur a gagné!";
    }

    else

    {

        cout << NomJoueur << " a gagné!";
    }

    return 0;

}