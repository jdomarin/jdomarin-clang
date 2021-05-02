
/* Description : verifie si une case est libre ou occupée par un adversaire
   paramètres : pos est la position de la case a tester
                macouleur est la couleur du joueur courant
   précondition : aucune
   variable retournée : boolean (==int) 0 -> pos est occupé par une piece dont la couleur est macouleur
                                        non 0 -> pos est une case libre ou occupé par une piece de la couleur adverse à macouleur
*/
int estlibreouoccupeparadversaire(struct Position pos, enum Couleur macouleur);

/* Description :verifie que d est un déplacement valide pour un cavalier
                ATTENTION : CETTE FONCTION NE GERE PAS LES COMPORTEMENTS FRATRICIDES:
                cette fonction renverra vrai si le deplacement est bon mais conduit à une case qui serait déjà occupée par une de nos pièces
   paramètres : d deplacement à tester
   précondition : aucune
   variable retournée : boolean (==int) 0 -> d n'est pas un déplacement en L
                                        non 0 -> d est un déplacement en L
*/
int estvalidedeplacementcavalier(struct Deplacement d);

/* Description :verifie que d est un déplacement valide pour un pion
                ATTENTION : CETTE FONCTION NE GERE PAS LES COMPORTEMENTS FRATRICIDES:
                cette fonction renverra vrai si le deplacement est bon mais conduit à une case qui serait déjà occupée par une de nos pièces
   paramètres : d deplacement à tester
                c couleur du pion
   précondition : aucune
   variable retournée : boolean (==int) 0 -> d n'est pas possible pour un pion
                                        non 0 -> d est un déplacement possible pour un pion
*/
int estvalidedeplacementpion(enum Couleur c,struct Deplacement d);

/* Description : verifie si un deplacement est légal
   paramètres : d le deplacement à tester
   précondition : le deplacement d ne fait pas intervenir de case inexistante comme (-1,2)
                  la case d.initial ne doit pas être libre
                  la couleur du joueur qui veut faire le deplacement est la couleur de la piece qui se trouve en d.initial
   variable retournée : boolean (==int) 0 -> d est un déplacement légal
                                        non 0 -> d n'est pas un déplacement légal
*/
int estvalidedeplacement(struct Deplacement d);


/* Description : effectue un tour du jeu
   paramètres : coupblanc le deplacement à effectuer par les blancs
                coupnoir le deplacement à effectuer par les noirs
   précondition : les deplacements coupblanc et coupnoir ne font pas intervenir de case inexistante comme (-1,2)
                  les cases coupblanc.initial et coupnoir.initial ne doivent pas être libres
                  coupblanc.initial contient une pièce blanche
                  coupnoir.initial contient une pièce noire
   variable retournée : boolean (==int) 0 -> impossible
                                        non 0 -> tour de jeu effectuée correctement
*/
void deplacement(struct Deplacement coupblanc,struct Deplacement coupnoir);


/* Description : Effectue la promotion des pions concernés 
   paramètre : Aucun
   précondition : Le plateau est valide
   postcondition : Il n'y a plus de pion coincé en bout de plateau
*/
void promotionDuPion();

/* Description : Constate et renvoie l'état du jeu 
   paramètre : Aucun
   précondition : Le plateau est valide
   variable retournée : LeJeuContinue -> Tant que la partie n'est pas fini
                        NoirGagne -> Les blancs n'ont plus de pion
                        BlancGagne -> Les noirs n'ont plus de pion
                        PartieNulle -> Il n'y a plus de pion en jeu
*/
enum Etat estFini();


/* Description : Applique les règles basées sur l'état du jeu (promotion du pion et fin du jeu) 
   paramètre : Aucun
   précondition : Le plateau est valide
   variable retournée : LeJeuContinue -> Tant que la partie n'est pas fini
                        NoirGagne -> Les blancs n'ont plus de pion
                        BlancGagne -> Les noirs n'ont plus de pion
                        PartieNulle -> Il n'y a plus de pion en jeu
*/
enum Etat regleDEtat();

/* Description : Effectue la promotion des pions concernés 
   paramètre : Aucun
   précondition : Le plateau est valide
                  Les champs de *tourCourant sont renseignés correctement
   postcondition : Il n'y a plus de pion coincé en bout de plateau
*/
void promotionDuPionCourant();

/* Description : effectue le tour courant
   paramètres : aucun
   précondition : Le tour courant est correct
   variable retournée : l'état du jeu après le tour courant
*/
enum Etat faitTourCourant();

/* Description : effectue un tour en ligne de commande
   paramètres : aucun
   précondition : Le tour courant est en partie renseigné
   variable retournée : l'état du jeu après le tour
*/
enum Etat faitTourTerm();

