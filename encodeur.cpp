#include "encodeur.h"
#include <Arduino.h>

int valeurEncodeur;

void initialiserEncodeur() {
  valeurEncodeur = 0;
  //INITIALISER LES PORTS EN ENTREE

}

void gestionEncodeur() {
  //DETECTER UN FRONT MONTANT SUR S1 (broche de l'encodeur)
  //DETERMINER SI ON INCREMENTE ou DECREMENTE la variable valeurEncodeur selon la broche S2 (broche de l'encodeur)
}


// Retourne la valeur de l'encodeur
int lireValeurEncodeur() {
  return valeurEncodeur;
}
