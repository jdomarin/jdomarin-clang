
/* Description :fonction qui affiche l'état courrant du plateau
   paramètres : aucun
   précondition : la variable globale plateau est valide
   postcondition: le plateau s'affiche sur la console
*/
void afficheplateau();

/* Description : saisie du coup choisi par un joueur
   paramètres : c = couleur du joueur dont c'est le tour,
                coup = pointe vers la variable de type Deplacement qui doit recevoir le coup choisi par le joueur
   précondition : aucune
   postcondition: *coup contient le coup que veut jouer le joueur de couleur c
*/
void coupjoueur(enum Couleur c, struct Deplacement *coup);


/* Description : Affiche de façon intelligible un entier c entendu comme un enum Couleur
   paramètres : c : la couleur à afficher
   précondition :  Le curseur courant pointe vers le point où débute l'affichage
   postcondition: Affiche "BLANC" ou "NOIR"
*/
void affichecouleur(enum Couleur c);

/* Description : Affiche de façon intelligible le type et la couleur d'une pièce
   paramètres : p : la pièce à afficher
   précondition :  Le curseur courant pointe vers le point où débute l'affichage
   postcondition: Affiche "PN", "PB", "CN" ou "CB"
*/
void affichepiece(struct Piece *p);

/* Description : Affiche de façon intelligible un entier c entendu comme un enum Etat.
   paramètres : e : l'état à afficher.
   précondition :  Le curseur courant pointe vers le point où débute l'affichage
   postcondition: Affiche "Le jeu continue","Noir gagne", "Blanc gagne" ou "Ex aequo"
*/
void afficheetat(enum Etat e);


/* Description : saisie du déplacement d'un pion pour sa promotion
   paramètres : pion : le pion à déplacer
   précondition : Pion != NULL
                  La promotion du pion s'applique
                  Il existe une case libre dans le plateau pour déplacer ce pion
   postcondition: Le pion 'pion' a éffectué sa promotion
*/
void replacementPion(struct Piece *pion);

/* Description : Demande et charge le fichier d'initialisation de la partie
   paramètres : aucun
   précondition :
   Variable retournée: 1 -> Le plateau est initalisé
                       0 -> Erreur lors du chargement
*/
int initPartieTerm();

/* Description : Lance une partie en ligne de commande dans le terminal
   paramètres : aucun
   précondition : Plateau est initialisé
   postcondition: Le programme est terminé
*/
void partieTerm();
