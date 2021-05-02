
/* Description : verifie si une case est libre ou occup�e par un adversaire
   param�tres : pos est la position de la case a tester
                macouleur est la couleur du joueur courant
   pr�condition : aucune
   variable retourn�e : boolean (==int) 0 -> pos est occup� par une piece dont la couleur est macouleur
                                        non 0 -> pos est une case libre ou occup� par une piece de la couleur adverse � macouleur
*/
int estlibreouoccupeparadversaire(struct Position pos, enum Couleur macouleur);

/* Description :verifie que d est un d�placement valide pour un cavalier
                ATTENTION : CETTE FONCTION NE GERE PAS LES COMPORTEMENTS FRATRICIDES:
                cette fonction renverra vrai si le deplacement est bon mais conduit � une case qui serait d�j� occup�e par une de nos pi�ces
   param�tres : d deplacement � tester
   pr�condition : aucune
   variable retourn�e : boolean (==int) 0 -> d n'est pas un d�placement en L
                                        non 0 -> d est un d�placement en L
*/
int estvalidedeplacementcavalier(struct Deplacement d);

/* Description :verifie que d est un d�placement valide pour un pion
                ATTENTION : CETTE FONCTION NE GERE PAS LES COMPORTEMENTS FRATRICIDES:
                cette fonction renverra vrai si le deplacement est bon mais conduit � une case qui serait d�j� occup�e par une de nos pi�ces
   param�tres : d deplacement � tester
                c couleur du pion
   pr�condition : aucune
   variable retourn�e : boolean (==int) 0 -> d n'est pas possible pour un pion
                                        non 0 -> d est un d�placement possible pour un pion
*/
int estvalidedeplacementpion(enum Couleur c,struct Deplacement d);

/* Description : verifie si un deplacement est l�gal
   param�tres : d le deplacement � tester
   pr�condition : le deplacement d ne fait pas intervenir de case inexistante comme (-1,2)
                  la case d.initial ne doit pas �tre libre
                  la couleur du joueur qui veut faire le deplacement est la couleur de la piece qui se trouve en d.initial
   variable retourn�e : boolean (==int) 0 -> d est un d�placement l�gal
                                        non 0 -> d n'est pas un d�placement l�gal
*/
int estvalidedeplacement(struct Deplacement d);


/* Description : effectue un tour du jeu
   param�tres : coupblanc le deplacement � effectuer par les blancs
                coupnoir le deplacement � effectuer par les noirs
   pr�condition : les deplacements coupblanc et coupnoir ne font pas intervenir de case inexistante comme (-1,2)
                  les cases coupblanc.initial et coupnoir.initial ne doivent pas �tre libres
                  coupblanc.initial contient une pi�ce blanche
                  coupnoir.initial contient une pi�ce noire
   variable retourn�e : boolean (==int) 0 -> impossible
                                        non 0 -> tour de jeu effectu�e correctement
*/
void deplacement(struct Deplacement coupblanc,struct Deplacement coupnoir);


/* Description : Effectue la promotion des pions concern�s 
   param�tre : Aucun
   pr�condition : Le plateau est valide
   postcondition : Il n'y a plus de pion coinc� en bout de plateau
*/
void promotionDuPion();

/* Description : Constate et renvoie l'�tat du jeu 
   param�tre : Aucun
   pr�condition : Le plateau est valide
   variable retourn�e : LeJeuContinue -> Tant que la partie n'est pas fini
                        NoirGagne -> Les blancs n'ont plus de pion
                        BlancGagne -> Les noirs n'ont plus de pion
                        PartieNulle -> Il n'y a plus de pion en jeu
*/
enum Etat estFini();


/* Description : Applique les r�gles bas�es sur l'�tat du jeu (promotion du pion et fin du jeu) 
   param�tre : Aucun
   pr�condition : Le plateau est valide
   variable retourn�e : LeJeuContinue -> Tant que la partie n'est pas fini
                        NoirGagne -> Les blancs n'ont plus de pion
                        BlancGagne -> Les noirs n'ont plus de pion
                        PartieNulle -> Il n'y a plus de pion en jeu
*/
enum Etat regleDEtat();

/* Description : Effectue la promotion des pions concern�s 
   param�tre : Aucun
   pr�condition : Le plateau est valide
                  Les champs de *tourCourant sont renseign�s correctement
   postcondition : Il n'y a plus de pion coinc� en bout de plateau
*/
void promotionDuPionCourant();

/* Description : effectue le tour courant
   param�tres : aucun
   pr�condition : Le tour courant est correct
   variable retourn�e : l'�tat du jeu apr�s le tour courant
*/
enum Etat faitTourCourant();

/* Description : effectue un tour en ligne de commande
   param�tres : aucun
   pr�condition : Le tour courant est en partie renseign�
   variable retourn�e : l'�tat du jeu apr�s le tour
*/
enum Etat faitTourTerm();

