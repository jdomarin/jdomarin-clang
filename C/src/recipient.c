#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
 
 
#define NB_RECIPIENTS 4 
#define MAX_VOLUME 50 
 
 
typedef struct S_recipient { 
  int capacite;        
// Capacit� totale du recipient 
  int volume;   
// Volume de ricard pr�sent dans le r�cipient 
} T_recipient; 
 
typedef struct S_transvasement { 
  T_recipient *src;              // Le recipient source // Si NULL alors fontaine 
  T_recipient *dst;              // Le recipient cible  // Si NULL alors fontaine 
  struct S_transvasement *suiv;  // Pointe vers le transvasement suivant, NULL si pas de suivant 
} T_transvasement; 
 
T_recipient tab_recipient[NB_RECIPIENTS];  // Tableau representant NB_RECIPIENTS r�cipients 
unsigned char buffer[MAX_VOLUME + 1]; 
 
 
int mini(int a,int b) // Retourne le min de 2 entiers 
{ 
  return(a<b?a:b); 
} 
 
int maxi(int a,int b) // Retourne le max de 2 entiers 
{ 
  return(a>b?a:b); 
} 
 
 
int get_capacite(T_recipient *recipient) // Retourne la capacit� totale d'un r�cipient 
{ 
  return(recipient->capacite); 
} 
 
int get_volume(T_recipient *recipient) // Retourne le volume de ricard pr�sent dans le r�cipient 
{ 
  return(recipient->volume); 
} 
 
int get_libre(T_recipient *recipient) // Quantit� de ricard pouvant encore etre vers�e 
{ 
  return(recipient->capacite - recipient->volume); 
} 
 

 
void suite_transvasement(T_transvasement *suite) // effectue une liste chain�e de tranvasements successifs 
{ 
  int a; 
 
  while (suite) // tant qu'il reste des transvasements a effectuer on continue :) 
  { 
    if (suite->src && suite->dst) // transvasement entre 2 recipients 
    { 
      a = mini(get_libre(suite->dst),get_volume(suite->src)); // on determine la quantite de liquide que l'on pourra verser de src -> dst 
      suite->src->volume -= a; // on vide la source ... 
      suite->dst->volume += a; // ... de la meme quantite que l'on remplit la destination ! 
    } 
    else if (suite->src) // transvasement entre recipient -> fontaine 
      suite->src->volume = 0; // on vide le recipient 
    else // transvasement entre fontaine -> recipient 
      suite->dst->volume = get_capacite(suite->dst); // on remplit le recipient 
 
    suite = suite->suiv; // on passe au transvasement suivant 
  } 
} 
 

void transvase(int n) 
{ 
  int a,b; 
  T_transvasement trans; 
  T_recipient save_src,save_dst; 
 
  if (n==0) // on vient de faire les n transvasements possibles :) ... on note le resultat des volumes des differents recipients dans buffer 
  { 
    for (a=0;a<NB_RECIPIENTS;a++) 
      buffer[tab_recipient[a].volume]=1; 
    return; 
  } 
 
  // il reste encore des transvasements a faire ... 
 
  for (a=0;a<=NB_RECIPIENTS;a++) // on choisit un recipient source 
  { 
    for (b=0;b<=NB_RECIPIENTS;b++) // et un recipient cible ... ensuite on va transvaser et voir ce ke ca donne :) 
    { 
      if (a != b) // on evite les transvasements d'un recipient dans lui meme parce que c pas tres efficace  :o ) 
      { 
        if (a==NB_RECIPIENTS)          // 
        {                              // Tout ce micmac 
          trans.src = NULL;            // sert juste a 
        }                              // initialiser la 
        else                           // structure trans 
        {                              // avec une source 
          trans.src = &tab_recipient[a];              // (NULL si fontaine) 
          save_src.capacite = tab_recipient[a].capacite;      // et une destination 
          save_src.volume = tab_recipient[a].volume;// (NULL si fontaine) 
        }                              // et le pointeur sur 
        if (b==NB_RECIPIENTS)                    // le transvasement suivant 
        {                              // a NULL pour ne faire 
          trans.dst = NULL;                    // qu'un transvasement par etape 
        } 
        else                            
        { 
          trans.dst = &tab_recipient[b]; 
          save_dst.capacite = tab_recipient[b].capacite;
          save_dst.volume = tab_recipient[b].volume;
        }                               
                                       
        trans.suiv = NULL; 
   
        suite_transvasement(&trans);                // Ensuite on appelle la fonction suite_transvasement() avec la structure qu'on vient d'initialiser 
   
        transvase(n-1);                        // Le transvasement a eut lieu ... on passe a un autre ... recursivite powaaa ! 
 
        if (trans.src)  
        {                              // Ici on est revenu de l'appel de fonction transvase() ! 
          tab_recipient[a].capacite = save_src.capacite;      // C'est donc que l'on est tomb� sur un etat blokant ou k'on est a la fin ... on a fait tous 
          tab_recipient[a].volume = save_src.volume;// les transvasements possible dans "une direction" ... on va revenir une etape en arriere 
        }                              // et explorer les autres possibilites 
        if (trans.dst)                        // 
        {                              // Et pour revenir une etape en arriere comme si il s'etait rien pass� on restaure 
          tab_recipient[b].capacite = save_dst.capacite;      // la table des r�cipients a la valeur qu'elle avait avant l'appel a transvase() 
          tab_recipient[b].volume = save_dst.volume;// Du coup le programme n'y voit que du feu :) ... C fou quand meme le backtracking :-P 
        }
      } 
    } 
  } 
  return; 
}

int main (int argc, char* argv[]) {
  transvase(atoi(argv[1]));

  return 0;
}
