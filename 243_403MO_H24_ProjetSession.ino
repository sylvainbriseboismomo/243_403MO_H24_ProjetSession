//==================================================================================
// Projet session
// 
// Le projet de session consiste a une application utilisant comme afficheur une
// matrice de DEL RGB
//
// Ce programme de base permet d'afficher un nombre nombre sur une matrice 8x8
//
// Par: Sylvain Brisebois
// 2024-04-04
// 243-403-H24 MO
//
// Base du projet de session
// Version 1.0 : Debut du projet
// Version 1.1 : Ajout des libraries : encodeur et matrice en C
// Version 1.2 : Conversion des libraries en classe
// Version 2.0 : Modification de la classe Matrice
//                  - Remplacer par une librarie plus efficace
//                  - Ajout du support de multiples panneau de DEL
//                  - Ajout d'une machine a etats
//==================================================================================

#include "matrice.h"
#include "encodeur.h"

// Declaration des classes pour ce projet
Encodeur encodeur1;
Matrice matrice1;
// Creer une classe pour lire les boutons

// Creation des etats pour la machine a etats
enum etats { etatLogo, etatLogoDelais, etatMenuPrincipal, etatMenuSecondaire};

// Variable qui contient l'etat en cours
enum etats etatActuel = etatLogo;

void machineEtat();
void afficherLogo();
void afficherMenuPrincipal();
void afficherMenuSecondaire();

void machineEtat() {
  switch(etatActuel) {
    case etatLogo:
    default:
      afficherLogo();

    break;

    case etatLogoDelais:
      // Trouver un meilleur moyen d'attendre 3 sec avant d'aller au menu principal
      delay(3000);   // A REMPLACER !!!!!
      etatActuel = etatMenuPrincipal;
    break;

    case etatMenuPrincipal:
      afficherMenuPrincipal();
    break;

    case etatMenuSecondaire:
      afficherMenuSecondaire();
    break;
  }
}

void afficherLogo() {
  matrice1.effacer();
  
  // Remplis le tableau avec des pixels aleatoires
  for(int x = 0 ; x < matrice1.largeur() ; x++) {
    for(int y = 0 ; y < matrice1.hauteur() ; y++) {
      matrice1.ecrirePixelXY(x, y, random(2), random(2), random(2));
    }
  }

  // Cree un rectangle noir au centre
  for(int x = 13 ; x < 20 ; x++) {
    for(int y = 4 ; y < 12 ; y++) {
      matrice1.ecrirePixelXY(x, y, 0,0,0);
    }
  }


  // Dessine une forme
  matrice1.ecrirePixelXY(16,8,20,0,0);
  matrice1.ecrirePixelXY(15,8,0,0,20);
  matrice1.ecrirePixelXY(17,8,0,0,20);
  matrice1.ecrirePixelXY(16,7,0,0,20);
  matrice1.ecrirePixelXY(16,9,0,0,20);

  matrice1.miseAJour();

  // Place la machine a etat a l'etape d'attendre un delais avant de continuer
  etatActuel = etatLogoDelais;
}

void afficherMenuPrincipal() {
  static uint8_t valeurTest = 0;

  matrice1.effacer();
 
  matrice1.ligneH(0, 0, 32, 2,2,2);
  matrice1.ligneH(0, 15, 32, 2,2,2);  
  matrice1.ligneV(15, 1, 14, 4,4,0);
  
  matrice1.afficherNombre(2,2,2,(valeurTest/10)%10,5,0,0);
  matrice1.afficherNombre(8,2,3,(valeurTest/1)%10,0,5,0);
  matrice1.miseAJour();

  valeurTest++;

  // Pause de 1 secondes... A AMELIORER
  delay(1000);

  //Sur une condition (Ex: un bouton appuye...), allez au menu secondaire
  //etatActuel = etatMenuSecondaire;
}

void afficherMenuSecondaire() {
  matrice1.effacer();
  matrice1.miseAJour();
  // Rien dans ce menu pour le moment, retourne au menu principal

  // Pause de 1 secondes... A AMELIORER
  delay(1000);

  //Sur une condition (Ex: un bouton appuye...), allez au menu primaire
  etatActuel = etatMenuPrincipal;
}

void setup() {
  Serial.begin(9600);
  matrice1.init();  // Initialisation du pilote NeoPixels
  //encodeur1.init();  // Initialisation du pilote de l'encodeur
  // Ajouter la methode pour initialiser les boutons
  }

void loop() {

  // Executer la machine a etat
  machineEtat();

  // Appeler la methode pour lire les boutons...
  
}
