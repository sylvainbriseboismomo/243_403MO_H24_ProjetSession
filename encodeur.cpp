#include "encodeur.h"
#include <Arduino.h>

// Definitions des broches

// Encoder signal S1 on PE3
#define ENCODER_S1_DDR  DDRE
#define ENCODER_S1_PIN  PINE
#define ENCODER_S1_BIT  3

// Encoder signal S2 on PE3
#define ENCODER_S2_DDR  DDRE
#define ENCODER_S2_PIN  PINE
#define ENCODER_S2_BIT  5

// Encoder signal KEY on PE4
#define ENCODER_KEY_DDR  DDRE
#define ENCODER_KEY_PIN  PINE
#define ENCODER_KEY_BIT  4

int valeurEncodeur;

void initialiserEncodeur() {
  valeurEncodeur = 0;
  //INITIALISER LES PORTS EN ENTREE
  ENCODER_S1_DDR &= ~(1<<ENCODER_S1_BIT); // Signal S1
  ENCODER_S2_DDR &= ~(1<<ENCODER_S2_BIT); // Signal S2
  ENCODER_KEY_DDR &= ~(1<<ENCODER_KEY_BIT); // Signal KEY
}

void gestionEncodeur() {
  //DETECTER UN FRONT MONTANT SUR S1 (broche de l'encodeur)
  //DETERMINER SI ON INCREMENTE ou DECREMENTE la variable valeurEncodeur selon la broche S2 (broche de l'encodeur)
  static byte valeurPecedenteS1 = 0;
  byte valeurCouranteS1;

  // Lit la valeur de S1 actuellement  
  if(ENCODER_S1_PIN & (1<<ENCODER_S1_BIT)) {
    valeurCouranteS1 = 1;
  }
  else {
    valeurCouranteS1 = 0;
  }

  // Detection front montant sur S1
  if(valeurCouranteS1 == 1 && valeurPecedenteS1 == 0) {
    // Detection de la direction du compteur (selon la valeur de S2)
    if(ENCODER_S2_DDR & (1<<ENCODER_S2_BIT)) {
      valeurEncodeur--;
    }
    else {
      valeurEncodeur++;
    }
  }


  // Met a jour la valeur precedente
  valeurPecedenteS1 = valeurCouranteS1;
}


// Retourne la valeur de l'encodeur
int lireValeurEncodeur() {
  return valeurEncodeur;
}
