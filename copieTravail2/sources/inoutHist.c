#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../headers/materiel.h"
#include "../headers/inoutTrad.h"
#include "../headers/inoutHist.h"
#include "../headers/regle.h"

int initialisation(){
  int i;
  int j;

  for(i = 0;i<5;i++)
    for(j = 0;j<5;j++)
      plateau[i][j] = NULL;

  for(i = 1; i<4;i++){
    pieces[i].type = PION;
    pieces[i].couleur = NOIR;
    pieces[i].zone = ENJEU;
    pieces[i].position.ligne = 0;
    pieces[i].position.colonne = i;

    plateau[0][i] = pieces+i;
  }//pions blancs

  for(i = 0; i<2;i++){
    pieces[4*i].type = PION;
    pieces[4*i].couleur = NOIR;
    pieces[4*i].zone = ENJEU;
    pieces[4*i].position.ligne = 1;
    pieces[4*i].position.colonne = 4*i;

    plateau[1][4*i] = pieces+4*i;

    pieces[i+5].type = CAVALIER;
    pieces[i+5].couleur = NOIR;
    pieces[i+5].zone = ENJEU;
    pieces[i+5].position.ligne = 0;
    pieces[i+5].position.colonne = i*4;

    plateau[0][i*4] = pieces+i+5;
  }//cavaliers blancs

  for(i = 1; i<4;i++){
    pieces[i+7].type = PION;
    pieces[i+7].couleur = BLANC;
    pieces[i+7].zone = ENJEU;
    pieces[i+7].position.ligne = 4;
    pieces[i+7].position.colonne = i;

    plateau[4][i] = pieces+i+7;
  }//pions noirs
  for(i = 0; i<2;i++){
    pieces[4*i+7].type = PION;
    pieces[4*i+7].couleur = BLANC;
    pieces[4*i+7].zone = ENJEU;
    pieces[4*i+7].position.ligne = 3;
    pieces[4*i+7].position.colonne = 4*i;

    plateau[3][4*i] = pieces+4*i+7;

    pieces[i+12].type = CAVALIER;
    pieces[i+12].couleur = BLANC;
    pieces[i+12].zone = ENJEU;
    pieces[i+12].position.ligne = 4;
    pieces[i+12].position.colonne = i*4;

    plateau[4][i*4] = pieces+i+12;
  }//cavaliers noirs
  return 1;
}


int chargement(char* fich){
  FILE *fin;
  char p[19];
  int i = 0;
  int n, m;
  fin = fopen(fich,"r");

  if(fin == 0){
    printf("Nom de fichier de chargement Invalide\n");
    return 0;
  } else {
    fscanf(fin,"%s",p);
    while(!feof(fin) && i<14 && p[0] != '-'){
      n = chtoc(p[4]);
      m = ltoc(p[3]);
      pieces[i].type = (p[0] == 'P') ? PION : CAVALIER;
      pieces[i].couleur = (p[1] == 'N') ? NOIR : BLANC;
      pieces[i].zone = ENJEU;
      pieces[i].position.ligne = n;
      pieces[i].position.colonne = m;
      plateau[n][m] = pieces + i;
      fscanf(fin,"%s",p);
      i++;
    }
    if(i!=14){
      printf("Une erreur est survenue : nombre de piece incorrect\nTrouvee %d Attendu 14\n",i);
      return 0;
    }

    int ni,mi,nf,mf;
    premierTour = NULL;
    tourCourant = NULL;
    i = 0;

    if(!feof(fin)){
      fscanf(fin,"%s",p);
      if(!feof(fin)){
	premierTour = (struct Tour*) malloc(sizeof(struct Tour));
	tourCourant = premierTour;
	(*tourCourant).tourSuivant = NULL;
	(*tourCourant).noTour = 0;
      }
    }
    while(!feof(fin)){
      ni = chtoc(p[1]);
      mi = ltoc(p[0]);
      nf = chtoc(p[4]);
      mf = ltoc(p[3]);
      n = chtoc(p[7]);
      m = ltoc(p[6]);
      (*tourCourant).noir.initial.ligne = ni;
      (*tourCourant).noir.initial.colonne = mi;
      (*tourCourant).noir.final.ligne = nf;
      (*tourCourant).noir.final.colonne = mf;
      (*tourCourant).promotionNoir.ligne = n;
      (*tourCourant).promotionNoir.colonne = m;

      ni = chtoc(p[11]);
      mi = ltoc(p[10]);
      nf = chtoc(p[14]);
      mf = ltoc(p[13]);
      n = chtoc(p[17]);
      m = ltoc(p[16]);
      (*tourCourant).blanc.initial.ligne = ni;
      (*tourCourant).blanc.initial.colonne = mi;
      (*tourCourant).blanc.final.ligne = nf;
      (*tourCourant).blanc.final.colonne = mf;
      (*tourCourant).promotionBlanc.ligne = n;
      (*tourCourant).promotionBlanc.colonne = m;

      (*tourCourant).etat = faitTourCourant();

      fscanf(fin,"%s",p);
      if(!feof(fin)){
	(*tourCourant).tourSuivant = (struct Tour*) malloc(sizeof(struct Tour));
	tourCourant = (*tourCourant).tourSuivant;
	(*tourCourant).tourSuivant = NULL;
	i++;
	(*tourCourant).noTour = i;
      }
    }
    fclose(fin);
    return 1;
  }
}


void freeHist(struct Tour* tour){
  if(tour != NULL){
    freeHist((*tour).tourSuivant);
    free(tour);
  }
}

void sauve(char* fichInit, char* fichSauv){
  FILE *fin, *fout;
  char p[19];
  int i = 0;
  char a,b;
  int n = strlen(fichSauv);
  char comm[n +3];
  comm[0] = 'r';
  comm[1] = 'm';
  comm[2] = ' ';
  comm[3] = '\0';
  strcat(comm,fichSauv);

  fin = fopen(fichInit,"r");
  if(fin == NULL){
    printf("Nom de fichier de chargement Invalide:\n\t%s",fichInit);
    return ;
  }
  fout = fopen(fichSauv,"w");
  if(fout == NULL){
    printf("Nom de fichier de chargement Invalide:\n\t%s",fichSauv);
    fclose(fin);
    return ;
  }

  fscanf(fin,"%s",p);
  while(!feof(fin) && i<14 && p[0] != '-'){
    fprintf(fout,"%s\n",p);
    fscanf(fin,"%s",p);
    i++;
  }
  if(i != 14){
      printf("Erreur dans %s",fichInit);
      fclose(fin);
      fclose(fout);
      system(comm);
      return ;
  }

  fprintf(fout,"-------------------\n");
  struct Tour *t;
  t = premierTour;

  while(t!=NULL){
    a = ctol((*t).noir.initial.colonne);
    b = ctoch((*t).noir.initial.ligne);
    fprintf(fout,"%c%c-",(a == '\0')?'#': a,(b == '\0')?'#': b);
    a = ctol((*t).noir.final.colonne);
    b = ctoch((*t).noir.final.ligne);
    fprintf(fout,"%c%c|",(a == '\0')?'#': a,(b == '\0')?'#': b);
    a = ctol((*t).promotionNoir.colonne);
    b = ctoch((*t).promotionNoir.ligne);
    fprintf(fout,"%c%c-",(a == '\0')?'#': a,(b == '\0')?'#': b);

    a = ctol((*t).blanc.initial.colonne);
    b = ctoch((*t).blanc.initial.ligne);
    fprintf(fout,"-%c%c-",(a == '\0')?'#': a,(b == '\0')?'#': b);
    a = ctol((*t).blanc.final.colonne);
    b = ctoch((*t).blanc.final.ligne);
    fprintf(fout,"%c%c|",(a == '\0')?'#': a,(b == '\0')?'#': b);
    a = ctol((*t).promotionBlanc.colonne);
    b = ctoch((*t).promotionBlanc.ligne);
    fprintf(fout,"%c%c\n",(a == '\0')?'#': a,(b == '\0')?'#': b);

    t = (*t).tourSuivant;
  }

  fclose(fin);
  fclose(fout);

}
