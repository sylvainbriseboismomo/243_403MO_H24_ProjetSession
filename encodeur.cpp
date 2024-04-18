#include "encodeur.h"
#include <Arduino.h>

static int Encodeur::valeur;

void Encodeur::init() {
  valeur = 0;
  //INITIALISER LES PORTS EN ENTREE
  ENCODER_S1_DDR &= ~(1<<ENCODER_S1_BIT); // Signal S1
  ENCODER_S2_DDR &= ~(1<<ENCODER_S2_BIT); // Signal S2
  ENCODER_KEY_DDR &= ~(1<<ENCODER_KEY_BIT); // Signal KEY

  // Activation de l'interruption pour S1
  attachInterrupt(digitalPinToInterrupt(3), interruptionS1, RISING);  
}

static void Encodeur::interruptionS1() {
  // Detection de la direction du compteur (selon la valeur de S2)
  if(ENCODER_S2_PIN & (1<<ENCODER_S2_BIT)) {
    valeur--;
  }
  else {
    valeur++;
  }
}

// Retourne la valeur de l'encodeur
int Encodeur::lireValeur() {
  return valeur;
}
