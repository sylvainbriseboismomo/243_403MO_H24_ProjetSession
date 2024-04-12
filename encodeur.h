#ifndef _ENCODEUR_H_
#define _ENCODEUR_H_

class Encodeur {

  // Declaration de tout ce qui est prive
  private:
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
    
    static int valeur;
    static void interruptionS1();
  // Declaration de tout ce qui est public
  public:
    void init();
    int lireValeur();
};

#endif