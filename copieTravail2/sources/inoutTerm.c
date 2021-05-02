#include <stdio.h>
#include <stdlib.h>
#include "../headers/materiel.h"
#include "../headers/regle.h"
#include "../headers/inoutTrad.h"
#include "../headers/inoutHist.h"
#include "../headers/inoutTerm.h"


 // Fonction d'affichage

void afficheetat(enum Etat e){
  switch(e){
  case LeJeuContinue :
    printf("Le jeu continue");
    break;
  case PartieNulle :
    printf("Ex aequo");
    break;
  case NoirGagne:
    printf("Noir gagne");
    break;
  case BlancGagne:
    printf("Blanc gagne");
      break;
  }
}


 void affichecouleur(enum Couleur c){
  if(c)
   printf("BLANC");
  else
   printf("NOIR");
 }

 void affichepiece(struct Piece *p){
  char tmp[3];
  if(p == NULL){
   tmp[0] = ' ';
   tmp[1] = ' ';
  } else {
   switch((*p).type){
    case PION :
     tmp[0] = 'P';
     if((*p).couleur == NOIR)
      tmp[1] = 'N';
     else
      tmp[1] = 'B';
     break;
    case CAVALIER :
     tmp[0] = 'C';
     tmp[1] = ((*p).couleur == NOIR) ? 'N' : 'B';
     break;
   }
  }
  tmp[2] = '\0';
  printf(".%s",tmp);

 } // affiche une piece

 void afficheplateau(){
  int i, j;

   //affiche la premiere ligne de point
  printf("  ");
  printf("  ");
  printf("  ");
  for(j = 0; j<5; j++){
   printf(".  ");
  };
  printf(".\n");

  //affiche le plateau
  for(i = 0; i<5; i++){
   printf("  ");
   printf(" %c",ctoch(i));
   printf("  ");
   for(j = 0; j<5; j++){
    affichepiece(plateau[i][j]);
   };
   printf("\n");
  };
  printf("\n");
  printf("  ");
  printf("  ");
  printf("  ");
  for(j = 0; j<5; j++){
   printf("  %c",ctol(j));
  };
  printf("\n");

 }
// fonction de saisie des deplacements

 void coupjoueur(enum Couleur c, struct Deplacement *coup){
  int i0,j0,iif,jf;
  char deb[3], arr[3], ans[2];
  int b;
  int bb = 0;
  while(!bb){
   affichecouleur(c);
   printf(" (c pour continuer à jouer | p pour passer) \n $>");
   scanf("%s",ans);
   if(ans[0] == 'p' || ans[0] == 'P'){
     (*coup).initial.ligne = -1;
     (*coup).initial.colonne = -1;
     (*coup).final.ligne = -1;
     (*coup).final.colonne = -1;
     bb = 1;
   } else if(ans[0] == 'c' || ans[0] == 'C'){
     b =0;
     while(!b){
       printf(" $ Votre coups : \n");
       printf("\tcase de depart : ");
       scanf("%s",deb);
       j0 = ltoc(deb[0]);
       i0 = chtoc(deb[1]);
       b = (i0!=-1) && (j0!=-1) && (plateau[i0][j0] != NULL) && ((* plateau[i0][j0]).couleur == c);
       if(!b)
	 printf("\n Erreur case de depart invalide\nRecommencez\n");
     }
     (*coup).initial.ligne = i0;
     (*coup).initial.colonne = j0;
     printf("\n\tcase d'arrivee : ");
     scanf("%s",arr);
     jf = ltoc(arr[0]);
     iif = chtoc(arr[1]);
     (*coup).final.ligne = iif;
     (*coup).final.colonne = jf;
     //printf("col = %c   lig = %c\n",arr[0],arr[1]);
     //printf("iif = %d   jf = %d\n",iif,jf);
     bb = (iif != -1) && (jf != -1) && estvalidedeplacement(*coup);
     if(!bb)
       printf("\nErreur case d'arrivee invalide\nRecommencez\n");
   }
  }
 }

void replacementPion(struct Piece *pion) {
 char ans[3];
  int n,m;

  affichecouleur((*pion).couleur);
  printf(", Votre pion en %c%c doit subir la promotion du pion\n",ctol((*pion).position.colonne),ctoch((*pion).position.ligne));
  printf("Où doit-il être replacé? ");
  scanf("%s",ans);
  m = chtoc(ans[1]);
  n = ltoc(ans[0]);

  while(n == -1 || m == -1 || m == (*pion).position.ligne|| plateau[m][n] != NULL){
    printf("Impossible de replacer votre pion en %s\n",ans);
    printf("Où doit-il être replacé? ");
    scanf("%s",ans);
    m = chtoc(ans[1]);
    n = ltoc(ans[0]);
  }

  plateau[(*pion).position.ligne][(*pion).position.colonne] = NULL;
  (*pion).position.ligne = m;
  (*pion).position.colonne = n;
  plateau[m][n] = pion;

  if((*pion).couleur == ! NOIR){
    (*tourCourant).promotionNoir.ligne = n;
    (*tourCourant).promotionNoir.colonne = m;
  } else {
    (*tourCourant).promotionBlanc.ligne = n;
    (*tourCourant).promotionBlanc.colonne = m;
  }


}

int initPartieTerm(){

  char ans[2];
  char fich[32];
  printf("(n pour commencer une nouvelle partie - l pour charger une partie enregistrée)\n$>");
  scanf("%s",ans);
  if(ans[0] == 'n' || ans[0] == 'N'){
    return initialisation();
  } else if(ans[0] == 'l' || ans[0] == 'L'){
    printf("Quelle partie voullez-vous charger?\n$>");
    scanf("%s",fich);
    return chargement(fich);
  } else {
    printf("Reponse invalide");
    return 0;
  }

}

void partieTerm(){
  int b = 1;
  char ans[2];
  char fichSauv[32];
  int i;

  afficheplateau();

  while((tourCourant == NULL || (*tourCourant).etat == LeJeuContinue) && b){
    printf(" (c pour continuer à jouer | s pour sauvegarder la partie | q pour quitter le jeu) \n $>");
    scanf("%s",ans);
    if(ans[0] == 'q' || ans[0] == 'Q'){
      b = 0;
    } else if(ans[0] == 's' || ans[0] == 'S'){
      printf("Où mettre la sauvegarde \n$>");
      scanf("%s",fichSauv);
      sauve("./annexe/initial.apo",fichSauv);
    } else if(ans[0] == 'c' || ans[0] == 'C'){
      if(premierTour == NULL){
	premierTour = (struct Tour*) malloc(sizeof(struct Tour));
	tourCourant = premierTour;
	(*tourCourant).noTour = 0;
      } else {
	(*tourCourant).tourSuivant = (struct Tour*) malloc(sizeof(struct Tour));
	i = (*tourCourant).noTour;
	tourCourant = (*tourCourant).tourSuivant;
	(*tourCourant).noTour = i+1;
      }
      (*tourCourant).tourSuivant = NULL;
      (*tourCourant).promotionNoir.ligne = -1;
      (*tourCourant).promotionNoir.colonne = -1;
      (*tourCourant).promotionBlanc.ligne = -1;
      (*tourCourant).promotionBlanc.colonne = -1;

      coupjoueur(NOIR, &((*tourCourant).noir));
      afficheplateau();
      coupjoueur(BLANC, &((*tourCourant).blanc));
      (*tourCourant).etat = faitTourTerm();
      afficheplateau();
    } else {
      printf("Commande inconnue");
    }
  }

  printf("\n\nLa partie est Terminée dans l'état :\n\n\t -------------------------------\n\t|\t");
  afficheetat((*tourCourant).etat);
  printf("\t\t|\n\t -------------------------------\n\n");

  if(b){
    printf(" (s pour sauvegarder la partie | q pour quitter le jeu) \n $>");
    scanf("%s",ans);
    if(ans[0] == 's' || ans[0] == 'S'){
      printf("Où mettre la sauvegarde \n$>");
      scanf("%s",fichSauv);
      sauve("./annexe/initial.apo",fichSauv);
    }
  }
}
