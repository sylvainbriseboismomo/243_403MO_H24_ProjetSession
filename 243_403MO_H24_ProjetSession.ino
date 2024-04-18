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
//==================================================================================

#include "matrice.h"
#include "encodeur.h"

// Declaration d'un objet pour l'encodeur
Encodeur encodeur1;
Matrice matrice1;

void setup() {
  Serial.begin(9600);
  // Initialisation du pilote NeoPixels
  matrice1.init();
  // Initialisation du pilote de l'encodeur
  encodeur1.init();

  // Affiche un X au demarrage
  matrice1.dessinerX();
  matrice1.miseAJour();
  }

void loop() {

  // Affichage de la valeur si elle a changer
  static int oldEncodeurValue = 0;
  int actualEncoderValue = encodeur1.lireValeur();
  
  if(actualEncoderValue != oldEncodeurValue) {
    Serial.println(actualEncoderValue);
    matrice1.effacer();
    matrice1.dessinerNombre(actualEncoderValue);
    matrice1.miseAJour();
  }
  oldEncodeurValue = actualEncoderValue;



/*
  CE CODE EST DESACTIVER POUR CETTE ETAPE. NE PAS LE RE-ACTIVER AFIN QUE VOTRE LIBRARIE ENCODEUR FONCTIONNE CORRECTEMENT

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
*/


}

