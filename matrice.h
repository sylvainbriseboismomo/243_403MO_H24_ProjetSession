#ifndef _MATRICE_H
#define _MATRICE_H

#include <Adafruit_NeoPixel.h>

class Matrice {

  
  // Declaration de tout ce qui est prive
  private:
    // Definitions des broches
    #define PIN        A0   // Numero de broche Arduino pour controller la matrice

    // Definitions des parametres d'utilisation du programme
    // Nombre de del par panneau
    #define PANNEL_LED_W 16
    #define PANNEL_LED_H 16

    // Nombre de panneau sur le produit final
    #define PANNEL_COUNT_W 2
    #define PANNEL_COUNT_H 1

    // Calculs du nombre de dels
    #define PANNEL_W (PANNEL_COUNT_W * PANNEL_LED_W)
    #define PANNEL_H (PANNEL_COUNT_H * PANNEL_LED_H)
    #define NUMPIXELS (PANNEL_W * PANNEL_H)

    // Declaration d'un objet pour communiquer avec la matrice de DEL
    Adafruit_NeoPixel pixels;

    // Tableau de correspondance pour les pixels entre le mode X-Y et le pilote
    uint16_t pixelMap[PANNEL_W][PANNEL_H];

    void lirePixel(uint16_t pxlCnt, uint8_t *r, uint8_t *g, uint8_t *b);
    void ecrirePixel(uint16_t pxlCnt, uint8_t r, uint8_t g, uint8_t b);
    float calculEstimeCourant();
    void diminuerCourant();

  // Declaration de tout ce qui est public
  public:
    uint16_t largeur();
    uint16_t hauteur();
    void init();
    void effacer();
    void lirePixelXY(uint16_t x, uint16_t y, uint8_t *r, uint8_t *g, uint8_t *b);
    void ecrirePixelXY(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b);
    void ligneH(uint8_t startX, uint8_t startY, uint8_t len, uint8_t r, uint8_t g, uint8_t b);
    void ligneV(uint8_t startX, uint8_t startY, uint8_t len, uint8_t r, uint8_t g, uint8_t b);
    void afficherNombre(uint8_t posX, uint8_t posY, uint8_t segLen, uint8_t value, uint8_t r, uint8_t g, uint8_t b, uint8_t thick = 1);
    void miseAJour();    
};

#endif