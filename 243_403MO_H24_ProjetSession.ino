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
#include "encodeur.h"

void setup() {
  Serial.begin(9600);
  // Initialisation du pilote NeoPixels
  initialiserLaMatrice();
  // Initialisation du pilote de l'encodeur
  initialiserEncodeur();

  }

void loop() {
  // Gestion de l'encodeur (lecture des signaux et traitement)
  gestionEncodeur();

  // Affichage de la valeur si elle a changer
  static int oldEncodeurValue = 0;
  int actualEncoderValue = lireValeurEncodeur();
  
  if(actualEncoderValue != oldEncodeurValue) {
    Serial.println(actualEncoderValue);
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

