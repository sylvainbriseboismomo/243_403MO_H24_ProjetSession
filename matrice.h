#ifndef _MATRICE_H
#define _MATRICE_H

#include <Adafruit_NeoPixel.h>

// Definitions des broches
#define PIN        13   // Numero de broche Arduino pour controller la matrice

// Definitions des parametres d'utilisation du programme
#define NB_LIGNE   8    // Nombre de ligne
#define NB_COL     8    // nombre de colones
#define NUMPIXELS  (NB_LIGNE*NB_COL) // Calcul du nombre total de pixels

//Prototype des fonctions
void initialiserLaMatrice();
void effacerTableauPixels();
void miseAJourDeMatrice();
void dessinerLigneVerticale();
void dessinerCarre();
void dessinerX();
void dessinerNombre(unsigned char nombre);


#endif