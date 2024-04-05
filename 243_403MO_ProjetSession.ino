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
//==================================================================================

#include "matrice.h"

void setup() {
  // Initialisation du pilote NeoPixels
  initialiserLaMatrice();

  }

void loop() {

  // Afficher une ligne verticale
  effacerTableauPixels();
  dessinerLigneVerticale();
  miseAJourDeMatrice();
  delay(1000);

  // Afficher un carre
  effacerTableauPixels();
  dessinerCarre();
  miseAJourDeMatrice();
  delay(1000);

  // Afficher un X
  effacerTableauPixels();
  dessinerX();
  miseAJourDeMatrice();
  delay(1000);

  //Affiche les nombres
  for(int i = 0 ; i < 3 ; i++) {
    effacerTableauPixels();
    dessinerNombre(i);
    miseAJourDeMatrice();
    delay(1000);
  }
}

