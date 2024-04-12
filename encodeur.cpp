#include "encodeur.h"
#include <Arduino.h>

// Definitions des broches

// Encoder signal S1 on PE5
#define ENCODER_S1_DDR  DDRE
#define ENCODER_S1_PIN  PINE
#define ENCODER_S1_BIT  5

// Encoder signal S2 on PE3
#define ENCODER_S2_DDR  DDRE
#define ENCODER_S2_PIN  PINE
#define ENCODER_S2_BIT  3

// Encoder signal KEY on PE4
#define ENCODER_KEY_DDR  DDRE
#define ENCODER_KEY_PIN  PINE
#define ENCODER_KEY_BIT  4

int valeurEncodeur;

void interruptionEncodeurS1();

void initialiserEncodeur() {
  valeurEncodeur = 0;
  //INITIALISER LES PORTS EN ENTREE
  ENCODER_S1_DDR &= ~(1<<ENCODER_S1_BIT); // Signal S1
  ENCODER_S2_DDR &= ~(1<<ENCODER_S2_BIT); // Signal S2
  ENCODER_KEY_DDR &= ~(1<<ENCODER_KEY_BIT); // Signal KEY

  // Activation de l'interruption pour S1
  attachInterrupt(digitalPinToInterrupt(3), interruptionEncodeurS1, RISING);  
}

void interruptionEncodeurS1() {
  // Detection de la direction du compteur (selon la valeur de S2)
  if(ENCODER_S2_PIN & (1<<ENCODER_S2_BIT)) {
    valeurEncodeur--;
  }
  else {
    valeurEncodeur++;
  }
}

// Retourne la valeur de l'encodeur
int lireValeurEncodeur() {
  return valeurEncodeur;
}
