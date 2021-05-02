/*
Bouton
Description : 
x0 : abscisse de l'origine du bouton (en bas à gauche)
y0 : ordonnée de l'origine du bouton
longueur : longueur du bouton (horizontale)
hauteur : hauteur du bouton (verticale)
 */
struct Bouton{
  int x0;
  int y0;
  int hauteur;
  int largeur;
};

/*
estdansbouton
Vérifie si le point de coordonnées (x,y) est sur le bouton
renvoie 0 si c'est le cas, 1 sinon
 */
int estdansbouton(int x, int y);
