#include "matrice.h"
#include <Adafruit_NeoPixel.h>

// Declaration d'un objet pour communiquer avec la matrice de DEL
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Declaration d'un tableau 2D pour controller les DEL en mode X-Y
unsigned char tableauPixels[NB_COL][NB_LIGNE];

void initialiserLaMatrice()
{
  pixels.begin();
}

// Fonction qui efface le contenu du tableau de pixels en X-Y
void effacerTableauPixels() {
  // Boucle sur les colones (X)
  for(int x = 0 ; x < NB_COL ; x++) {
    // Boucle sur les lignes (Y)
    for(int y = 0 ; y < NB_LIGNE ; y++) {
      tableauPixels[x][y] = 0;
    }
  }
}

// Fonction qui effectuer la mise a jour des pixels
// Cette fonction effectuer le transfert de donnes
// entre le tableau de pixels en 2D et le pilote de DEL NeoPixels
// et affiche la nouvelle valeur des DELS
void miseAJourDeMatrice() {
  // Remise a zero des DELS sur le pilote NeoPixels
  pixels.clear();

  // Boucle sur les colones (X)
  for(int x = 0 ; x < NB_COL ; x++) {
    // boucles sur les lignes (Y)
    for(int y = 0 ; y < NB_LIGNE ; y++) {
      // Transfert des pixels du tableau 2D vers le pilote NeoPixel (comme un tableau 1D)
      // Il faut faire un calcul pour convertir les coordonnes X et Y en une seule valeur
      // correspondante au pixels dans la matrice: x + ( Y * NB_COL)

      // Detection des lignes impairs
      if(y & 0x01) {
        // Pour les lignes impairs, il faut faire un mirroir des pixels (gauche-droite)
        pixels.setPixelColor((NB_COL-1) - x + (y * NB_COL), pixels.Color(0, tableauPixels[x][y], 0));
      }
      else {
        // Transfert direct du tableau 2D en 1D
        pixels.setPixelColor(x + (y * NB_COL), pixels.Color(0, tableauPixels[x][y], 0));
      }        
    }
  }

  // Declenche l'envoie des nouvelles valeurs sur les DEL
  pixels.show();
}

// Fonction qui dessine une ligne verticale dans le tableau de pixels X-Y
void dessinerLigneVerticale() {
// Tracer une lignes verticale a la colone 0
  for(int y = 0 ; y < NB_LIGNE ; y++) {
    tableauPixels[0][y] = 10;
  }
}

// fonction qui dessine un carre dans le tableau de pixels X-Y
void dessinerCarre() {
  // Tracer les lignes horizontales du carre
  for(int x = 0 ; x < NB_COL ; x++) {
    tableauPixels[x][0] = 10;
    tableauPixels[x][NB_LIGNE-1] = 10;
  }

// Tracer les lignes verticales du carre
  for(int y = 0 ; y < NB_LIGNE ; y++) {
    tableauPixels[0][y] = 10;
    tableauPixels[NB_COL-1][y] = 10;
  }
}

// fonction qui dessine un X dans le tableau de pixels X-Y
void dessinerX() {
  // Tracer la premiere diagonale
  for(int x = 0 ; x < NB_COL ; x++) {
    tableauPixels[x][x] = 10;
  }

  // Tracer la seconde diagonale
  for(int x = 0 ; x < NB_COL ; x++) {
    tableauPixels[x][(NB_COL-1) - x] = 10;
  }
}

// fonction qui dessine les nombres de 0 a 9 dans le tableau de pixels X-Y
void dessinerNombre(unsigned char nombre) {
  unsigned char intensite = 10;

  switch(nombre) {
    case 0:
      tableauPixels[1][0] = intensite;
      tableauPixels[2][0] = intensite;
      tableauPixels[3][0] = intensite;
      tableauPixels[4][0] = intensite;
      tableauPixels[1][6] = intensite;
      tableauPixels[2][6] = intensite;
      tableauPixels[3][6] = intensite;
      tableauPixels[4][6] = intensite;
      tableauPixels[0][1] = intensite;
      tableauPixels[0][2] = intensite;
      tableauPixels[0][3] = intensite;
      tableauPixels[0][4] = intensite;
      tableauPixels[0][5] = intensite;
      tableauPixels[5][1] = intensite;
      tableauPixels[5][2] = intensite;
      tableauPixels[5][3] = intensite;
      tableauPixels[5][4] = intensite;
      tableauPixels[5][5] = intensite;
    break;
    case 1:
      tableauPixels[2][0] = intensite;
      tableauPixels[2][1] = intensite;
      tableauPixels[2][2] = intensite;
      tableauPixels[2][3] = intensite;
      tableauPixels[2][4] = intensite;
      tableauPixels[2][5] = intensite;
      tableauPixels[2][6] = intensite;
    break;
    case 2:
      tableauPixels[1][0] = intensite;
      tableauPixels[2][0] = intensite;
      tableauPixels[3][0] = intensite;
      tableauPixels[4][0] = intensite;
      tableauPixels[1][3] = intensite;
      tableauPixels[2][3] = intensite;
      tableauPixels[3][3] = intensite;
      tableauPixels[4][3] = intensite;
      tableauPixels[1][6] = intensite;
      tableauPixels[2][6] = intensite;
      tableauPixels[3][6] = intensite;
      tableauPixels[4][6] = intensite;
      tableauPixels[0][1] = intensite;
      tableauPixels[0][2] = intensite;
      tableauPixels[5][4] = intensite;
      tableauPixels[5][5] = intensite;
    break;
    default:
      dessinerX();
    break;
  }
}
