#ifndef _MATRICE_H
#define _MATRICE_H

#include <Adafruit_NeoPixel.h>

class Matrice {

  
  // Declaration de tout ce qui est prive
  private:
    // Definitions des broches
    #define PIN        13   // Numero de broche Arduino pour controller la matrice

    // Definitions des parametres d'utilisation du programme
    #define NB_LIGNE   8    // Nombre de ligne
    #define NB_COL     8    // nombre de colones
    #define NUMPIXELS  (NB_LIGNE*NB_COL) // Calcul du nombre total de pixels

    // Declaration d'un objet pour communiquer avec la matrice de DEL
    Adafruit_NeoPixel pixels;//(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

    // Declaration d'un tableau 2D pour controller les DEL en mode X-Y
    unsigned char tableauPixels[NB_COL][NB_LIGNE];

  // Declaration de tout ce qui est public
  public:
    void init();
    void effacer();
    void miseAJour();
    void dessinerLigneVerticale();
    void dessinerCarre();
    void dessinerX();
    void dessinerNombre(unsigned char nombre);

    
};

#endif