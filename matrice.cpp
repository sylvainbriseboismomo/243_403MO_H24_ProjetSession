#include "matrice.h"
#include <Adafruit_NeoPixel.h>


uint16_t Matrice::largeur() {
  return PANNEL_W;
}

uint16_t Matrice::hauteur() {
  return PANNEL_H;
}

void Matrice::init()
{
  pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
  pixels.begin();
  pixels.clear();
  pixels.show();

  uint16_t idPixel, idPixelInverse;

  // Create an address map for a pannel
  for(uint16_t y=0 ; y < PANNEL_LED_H ; y++) {
    for(uint16_t x=0 ; x<PANNEL_LED_W; x++) {
      if(x & 0x01) {
        idPixel = (x * PANNEL_LED_H) + y;
        idPixelInverse = (((PANNEL_LED_W-1) - x) * PANNEL_LED_H) + y;
      }
      else {
        idPixel = (x * PANNEL_LED_H) + ((PANNEL_LED_H-1)-y);
        idPixelInverse = (((PANNEL_LED_W - 1) - x) * PANNEL_LED_H) + ((PANNEL_LED_H-1)-y);  
      }

      pixelMap[x+(0*PANNEL_LED_W)][y + (0*PANNEL_LED_H)] = idPixel + (0 * PANNEL_LED_W * PANNEL_LED_H);
      pixelMap[x+(1*PANNEL_LED_W)][y + (0*PANNEL_LED_H)] = idPixel + (1 * PANNEL_LED_W * PANNEL_LED_H);
/*
      pixelMap[x+(1*PANNEL_LED_W)][y  + (1*PANNEL_LED_H)] = idPixel + (2 * PANNEL_LED_W * PANNEL_LED_H);
      pixelMap[x+(0*PANNEL_LED_W)][y + (1*PANNEL_LED_H)] = idPixelInverse + (3 * PANNEL_LED_W * PANNEL_LED_H);
      pixelMap[x+(1*PANNEL_LED_W)][y + (1*PANNEL_LED_H)] = idPixelInverse + (4 * PANNEL_LED_W * PANNEL_LED_H);
      pixelMap[x+(0*PANNEL_LED_W)][y + (1*PANNEL_LED_H)] = midPixelInverse + (5 * PANNEL_LED_W * PANNEL_LED_H);
*/          
    }
  }
}

// Fonction qui efface le contenu du tableau de pixels en X-Y
void Matrice::effacer() {
  pixels.clear();
}

// Fonction qui effectuer la mise a jour des pixels
// Cette fonction effectuer le transfert de donnes
// entre le tableau de pixels en 2D et le pilote de DEL NeoPixels
// et affiche la nouvelle valeur des DELS
void Matrice::miseAJour() {
  //  Limite le courant total
  while(calculEstimeCourant() > 0.5) // While it too high
  {
    diminuerCourant();
  }
  // Declenche l'envoie des nouvelles valeurs sur les DEL
  pixels.show();
}

void Matrice::lirePixel(uint16_t pxlCnt, uint8_t *r, uint8_t *g, uint8_t *b) {
  uint32_t pixelColor = pixels.getPixelColor(pxlCnt);
  *r = 0x000000FF & (pixelColor >> (3*8));
  *g = 0x000000FF & (pixelColor >> (2*8));
  *b = 0x000000FF & (pixelColor >> (1*8));
}

void Matrice::lirePixelXY(uint16_t x, uint16_t y, uint8_t *r, uint8_t *g, uint8_t *b) {
  lirePixel(pixelMap[x][y], r, g,b);
}

void Matrice::ecrirePixel(uint16_t pxlCnt, uint8_t r, uint8_t g, uint8_t b) {
  pixels.setPixelColor(pxlCnt,pixels.Color(r,g,b));
}

void Matrice::ecrirePixelXY(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b) {
  ecrirePixel(pixelMap[x][y], r, g,b);
}

float Matrice::calculEstimeCourant() {
  float current = 0;
  uint8_t r,g,b;

  for(uint16_t pxlCnt = 0 ; pxlCnt < NUMPIXELS ; pxlCnt++ )
  {
      lirePixel(pxlCnt, &r, &g, &b);
      current += (float)(r) * 0.0125 / 255.0;
      current += (float)(g) * 0.0125 / 255.0;
      current += (float)(b) * 0.0125 / 255.0;
  }

  return current;
}

void Matrice::diminuerCourant() {
  uint8_t r,g,b;
  
  // Drop each color of 1
  for(uint16_t pxlCnt = 0 ; pxlCnt < NUMPIXELS ; pxlCnt++ )
    {
      lirePixel(pxlCnt, &r, &g, &b);
      if(r) {
        r--;
      }
      if(g) {
        g--;
      }
      if(b) {
        b--;
      }  

      ecrirePixel(pxlCnt, r, g, b);
    }
}

void Matrice::ligneH(uint8_t startX, uint8_t startY, uint8_t len, uint8_t r, uint8_t g, uint8_t b)
{
    for(uint8_t x = 0 ; x < len ; x++)
    {
      ecrirePixelXY(startX + x , startY, r, g, b);
    }
}

void Matrice::ligneV(uint8_t startX, uint8_t startY, uint8_t len, uint8_t r, uint8_t g, uint8_t b)
{
    for(uint8_t y = 0 ; y < len ; y++)
    {
      ecrirePixelXY(startX, startY+y, r, g, b);
    }
}

void Matrice::afficherNombre(uint8_t posX, uint8_t posY, uint8_t segLen, uint8_t value, uint8_t r, uint8_t g, uint8_t b, uint8_t thick = 1)
{
  // Segment definition
  //   -----1-----
  //   |         |
  //   2         0
  //   |         |
  //   -----3-----
  //   |         |
  //   6         4
  //   |         |
  //   -----5-----
  const int digitSegmentDecoding[10][7] =  { 
  { 1,1,1,0,1,1,1 },  // 0
  { 1,0,0,0,1,0,0 },  // 1
  { 1,1,0,1,0,1,1 },  // 2
  { 1,1,0,1,1,1,0 },  // 3
  { 1,0,1,1,1,0,0 },  // 4
  { 0,1,1,1,1,1,0 },  // 5
  { 0,1,1,1,1,1,1 },  // 6
  { 1,1,0,0,1,0,0 },  // 7
  { 1,1,1,1,1,1,1 },  // 8
  { 1,1,1,1,1,0,0 } };// 9

  if(value > 9) return;


  unsigned int tCnt = thick;

  while(tCnt > 0) 
  {
    tCnt--;
  // Draw segments
    if(digitSegmentDecoding[value][5])
    {
      ligneH(posX+thick, posY+tCnt,segLen,r,g,b);
    }
    if(digitSegmentDecoding[value][3])
    {
      ligneH(posX+thick, posY+segLen+thick+tCnt,segLen,r,g,b);
    }
    if(digitSegmentDecoding[value][1])
    {
      ligneH(posX+thick, posY+2*segLen+2*thick+tCnt,segLen,r,g,b);
    }
    if(digitSegmentDecoding[value][6])
    {
      ligneV(posX+tCnt, posY+thick,segLen,r,g,b);
    }
    if(digitSegmentDecoding[value][4])
    {
      ligneV(posX+segLen+thick+tCnt, posY+thick,segLen,r,g,b);
    }
    if(digitSegmentDecoding[value][2])
    {
      ligneV(posX+tCnt, posY+segLen+2*thick,segLen,r,g,b);
    }
    if(digitSegmentDecoding[value][0])
    {
      ligneV(posX+segLen+thick+tCnt, posY+segLen+2*thick,segLen,r,g,b);
    }
  }
}
