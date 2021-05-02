
/* Description :fonction qui affiche l'�tat courrant du plateau
   param�tres : aucun
   pr�condition : la variable globale plateau est valide
   postcondition: le plateau s'affiche sur la console
*/
void afficheplateau();

/* Description : saisie du coup choisi par un joueur
   param�tres : c = couleur du joueur dont c'est le tour,
                coup = pointe vers la variable de type Deplacement qui doit recevoir le coup choisi par le joueur
   pr�condition : aucune
   postcondition: *coup contient le coup que veut jouer le joueur de couleur c
*/
void coupjoueur(enum Couleur c, struct Deplacement *coup);


/* Description : Affiche de fa�on intelligible un entier c entendu comme un enum Couleur
   param�tres : c : la couleur � afficher
   pr�condition :  Le curseur courant pointe vers le point o� d�bute l'affichage
   postcondition: Affiche "BLANC" ou "NOIR"
*/
void affichecouleur(enum Couleur c);

/* Description : Affiche de fa�on intelligible le type et la couleur d'une pi�ce
   param�tres : p : la pi�ce � afficher
   pr�condition :  Le curseur courant pointe vers le point o� d�bute l'affichage
   postcondition: Affiche "PN", "PB", "CN" ou "CB"
*/
void affichepiece(struct Piece *p);

/* Description : Affiche de fa�on intelligible un entier c entendu comme un enum Etat.
   param�tres : e : l'�tat � afficher.
   pr�condition :  Le curseur courant pointe vers le point o� d�bute l'affichage
   postcondition: Affiche "Le jeu continue","Noir gagne", "Blanc gagne" ou "Ex aequo"
*/
void afficheetat(enum Etat e);


/* Description : saisie du d�placement d'un pion pour sa promotion
   param�tres : pion : le pion � d�placer
   pr�condition : Pion != NULL
                  La promotion du pion s'applique
                  Il existe une case libre dans le plateau pour d�placer ce pion
   postcondition: Le pion 'pion' a �ffectu� sa promotion
*/
void replacementPion(struct Piece *pion);

/* Description : Demande et charge le fichier d'initialisation de la partie
   param�tres : aucun
   pr�condition :
   Variable retourn�e: 1 -> Le plateau est initalis�
                       0 -> Erreur lors du chargement
*/
int initPartieTerm();

/* Description : Lance une partie en ligne de commande dans le terminal
   param�tres : aucun
   pr�condition : Plateau est initialis�
   postcondition: Le programme est termin�
*/
void partieTerm();
