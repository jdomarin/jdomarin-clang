#include "../headers/bouton.h"

struct Bouton{
  int x0;
  int y0;
  int hauteur;
  int largeur;
};

int estdansbouton(struct Bouton b,int x, int y){

  return (x >= b.x0 && x <= b.x0 + b.largeur)
    && (y >= b.y0 && y <= b.y0 + b.hauteur);
}
