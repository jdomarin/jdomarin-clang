#include "../headers/materiel.h"
#include "../headers/inoutTerm.h"
#include "../headers/regle.h"
#include <stdlib.h>

int estlibreouoccupeparadversaire(struct Position pos, enum Couleur macouleur){
  struct Piece *p = plateau[pos.ligne][pos.colonne];
  if(p == NULL)
   return 1;
  else
     return ((*p).couleur != macouleur);

 } // verifie si une case p est libre ou si une piece adverse (couleur != macouleur) s'y trouve

 int estvalidedeplacementcavalier(struct Deplacement d){
  int dx = d.final.colonne - d.initial.colonne;
  int dy = d.final.ligne - d.initial.ligne;
  if(dx == 2 || dx == -2)
   return (dy == 1 || dy == -1);
  else
   if(dy == 2 || dy == -2)
    return (dx == 1 || dx == -1);
   else
    return 0;
 } // verifie si un cavalier peut se déplacer depuis la position 'init' à 'final'

 int estvalidedeplacementpion(enum Couleur c,struct Deplacement d){
  int dx = d.final.colonne - d.initial.colonne;
  int dy = d.final.ligne - d.initial.ligne;
  struct Piece *p = plateau[d.final.ligne][d.final.colonne];
  //printf("dx = %d   dy = %d\n",dx,dy);

  if(dx == 0 && dy == 1-2*c)
   return (p == NULL);
  else
   if(dy == 1-2*c && (dx == 1 || dx == -1))
    return (p != NULL);
   else
    return 0;

 }

 int estvalidedeplacement(struct Deplacement d){
  struct Piece *p = plateau[d.initial.ligne][d.initial.colonne];
  if(p == NULL)
   return 0;
  else
   {
    int b = estlibreouoccupeparadversaire(d.final, (*p).couleur);
    switch((*p).type){
     case CAVALIER:
      b = b && estvalidedeplacementcavalier(d);
      break;
     case PION :
      b = b && estvalidedeplacementpion((*p).couleur, d);
    }
    return b;
   }
 } // verifie si un deplacement est valide




 // fonction de deplacement

 void deplacement2(struct Deplacement coupblanc,struct Deplacement coupnoir){
  struct Piece *pieceblanc = plateau[coupblanc.initial.ligne][coupblanc.initial.colonne];
  struct Piece *piecenoir = plateau[coupnoir.initial.ligne][coupnoir.initial.colonne];
  if((coupblanc.final.ligne == coupnoir.final.ligne) && (coupblanc.final.colonne == coupnoir.final.colonne))
    if((*piecenoir).type == (*pieceblanc).type){

     plateau[coupblanc.initial.ligne][coupblanc.initial.colonne] = NULL;
     plateau[coupnoir.initial.ligne][coupnoir.initial.colonne] = NULL;
     (*pieceblanc).zone = HORSJEU;
     (*piecenoir).zone = HORSJEU;

    } else {
      if((*piecenoir).type == CAVALIER){

        plateau[coupblanc.initial.ligne][coupblanc.initial.colonne] = NULL;
        plateau[coupnoir.initial.ligne][coupnoir.initial.colonne] = NULL;

        plateau[coupnoir.final.ligne][coupnoir.final.colonne] = piecenoir;

        (*pieceblanc).zone = HORSJEU;
        (*piecenoir).position = coupnoir.final;

      } else {

        plateau[coupblanc.initial.ligne][coupblanc.initial.colonne] = NULL;
        plateau[coupnoir.initial.ligne][coupnoir.initial.colonne] = NULL;

        plateau[coupblanc.final.ligne][coupblanc.final.colonne]= pieceblanc;

        (*piecenoir).zone = HORSJEU;
        (*pieceblanc).position = coupnoir.final;

      }
    } else {
    //modification par rapport à révision 1
      if( plateau[coupblanc.final.ligne][coupblanc.final.colonne] != NULL)
	(*plateau[coupblanc.final.ligne][coupblanc.final.colonne]).zone = HORSJEU;

      if( plateau[coupnoir.final.ligne][coupnoir.final.colonne] != NULL)
	(*plateau[coupnoir.final.ligne][coupnoir.final.colonne]).zone = HORSJEU;
      //fin modification
//if( plateau[finblanc.ligne][finblanc.colonne] != NULL)
       // (*plateau[finblanc.ligne][finblanc.colonne]).position = NULL;

      //if( plateau[finblanc.ligne][finblanc.colonne] != NULL)
        //(*plateau[finblanc.ligne][finblanc.colonne]).position = NULL;


        plateau[coupblanc.initial.ligne][coupblanc.initial.colonne] = NULL;
        plateau[coupnoir.initial.ligne][coupnoir.initial.colonne] = NULL;
	//printf("initblanc %c%c - initnoir%c%c\nfinblanc %c%c - finnoir %c%c\n",ctol(initblanc.colonne),ctoch(initblanc.ligne),ctol(initnoir.colonne),ctoch(initnoir.ligne),ctol(finblanc.colonne),ctoch(finblanc.ligne),ctol(finnoir.colonne),ctoch(finnoir.ligne));
//	affichepiece(piecenoir);printf(" --\n");

        plateau[coupnoir.final.ligne][coupnoir.final.colonne] = piecenoir;
        plateau[coupblanc.final.ligne][coupblanc.final.colonne]= pieceblanc;
       // affichepiece(plateau[finnoir.ligne][finnoir.colonne]);printf(" --\n");
 //affichepiece(plateau[1][2]);printf(" --\n");

        (*piecenoir).position = coupnoir.final;
        (*pieceblanc).position = coupblanc.final;
//affichepiece(plateau[1][2]);printf(" --\n");
    }
 
 }


void deplacement1(struct Deplacement d){
  struct Piece *p;
  p = plateau[d.final.ligne][d.final.colonne];
  if(p!=NULL)
    (*p).zone = HORSJEU;
  p = plateau[d.initial.ligne][d.initial.colonne];
  (*p).position = d.final;
  plateau[d.initial.ligne][d.initial.colonne] = NULL;
  plateau[d.final.ligne][d.final.colonne] = p;

}

void deplacement(struct Deplacement coupblanc,struct Deplacement coupnoir){
  if(coupblanc.initial.ligne == -1){
    if(coupnoir.initial.ligne == -1){
    } else {
      deplacement1(coupnoir);
    }
  } else {
    if(coupnoir.initial.ligne == -1){
      deplacement1(coupblanc);
    } else {
      deplacement2(coupblanc,coupnoir);
    }
  }
}


void promotionDuPionTerm(){
  int i,j,k;
  struct Piece *p;
  int nbCavalierBlanc = 0;
  int nbCavalierNoir = 0;
  //On compte les cavaliers blancs et noirs
  for(k=0;k<14;k++){
    if(pieces[k].zone == ENJEU){
      if(pieces[k].type == CAVALIER){
	if(pieces[k].couleur == BLANC)
	  nbCavalierBlanc++;
	else
	  nbCavalierNoir++;
      }
    }
  }


  //Promotion des Blancs
  i = 0;
  for(j=0;j<5;j++){
    p = plateau[i][j];
    if(p != NULL){
      if((*p).type == PION && (*p).couleur == BLANC){
	if(nbCavalierBlanc < 2)
	  (*p).type = CAVALIER;
	else {
	  replacementPion(p);
	}
      }
    }
  }
//Promotion des Noirs
  i = 4;
  for(j=0;j<5;j++){
    p = plateau[i][j];
    if(p != NULL){
      if((*p).type == PION && (*p).couleur == NOIR){
	if(nbCavalierNoir < 2){
	  (*p).type = CAVALIER;
	} else {
	  replacementPion(p);
	}
      }
    }
  }

}



enum Etat estFini(){
  int nbPionBlanc = 0;
  int nbPionNoir = 0;
  int k;

  //On compte nbPionBlanc et nbPionNoir
  for(k=0;k<14;k++)
    if(pieces[k].zone == ENJEU){
      if(pieces[k].type==PION){
	if(pieces[k].couleur == BLANC)
	  nbPionBlanc++;
	else
	  nbPionNoir++;
      }
    }

  //On determine l'etat du jeu
  if(nbPionBlanc == 0)
    if(nbPionNoir == 0)
      return PartieNulle;
    else
      return NoirGagne;
  else
    if(nbPionNoir == 0)
      return BlancGagne;
    else
      return LeJeuContinue;
}


enum Etat regleDEtat() {

  promotionDuPionTerm();
  return estFini();

}


void promotionDuPionCourant(){
  int i,j,k;
  struct Piece *p;
  int nbCavalierBlanc = 0;
  int nbCavalierNoir = 0;
  //On compte les cavaliers blancs et noirs
  for(k=0;k<14;k++){
    if(pieces[k].zone == ENJEU){
      if(pieces[k].type == CAVALIER){
	if(pieces[k].couleur == BLANC)
	  nbCavalierBlanc++;
	else
	  nbCavalierNoir++;
      }
    }
  }


  //Promotion des Blancs
  i = 0;
  for(j=0;j<5;j++){
    p = plateau[i][j];
    if(p != NULL){
      if((*p).type == PION && (*p).couleur == BLANC){
	if(nbCavalierBlanc <= 2)
	  (*p).type = CAVALIER;
	else {
	  (*p).position = (*tourCourant).promotionBlanc;
	  plateau[i][j] = NULL;
	  plateau[(*tourCourant).promotionBlanc.ligne][(*tourCourant).promotionBlanc.colonne] = p;
	}
      }
    }
  }

  i = 4;
  for(j=0;j<5;j++){
    p = plateau[i][j];
    if(p != NULL){
      if((*p).type == PION && (*p).couleur == NOIR){
	if(nbCavalierNoir <= 2)
	  (*p).type = CAVALIER;
	else {
	  (*p).position = (*tourCourant).promotionNoir;
	  plateau[i][j] = NULL;
	  plateau[(*tourCourant).promotionNoir.ligne][(*tourCourant).promotionNoir.colonne] = p;
	}
      }
    }
  }
	
}

enum Etat faitTourCourant(){
  deplacement((*tourCourant).blanc,(*tourCourant).noir);
  promotionDuPionCourant();
  return estFini(); 
}

enum Etat faitTourTerm(){
  deplacement((*tourCourant).blanc,(*tourCourant).noir);
  promotionDuPionTerm();
  return estFini(); 
}
