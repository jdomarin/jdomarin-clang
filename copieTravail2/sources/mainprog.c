#include "../headers/materiel.h"
#include "../headers/inoutTerm.h"
#include "../headers/inoutHist.h"
#include <stdio.h>

int main(int argc, char** argv){
  int b;
  b = initPartieTerm();
  if(b)  
    partieTerm();
  freeHist(premierTour);
  return 0;
}
