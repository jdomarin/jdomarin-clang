// les types

 enum Typedepiece {CAVALIER, PION};
 enum Couleur {NOIR, BLANC};
 enum Zone {HORSJEU, ENJEU};
 enum Etat {LeJeuContinue, NoirGagne, BlancGagne, PartieNulle };

 struct Position {

  int ligne;
  int colonne;

 };

 struct Deplacement {
     struct Position initial;
     struct Position final;
 };

 struct Piece {

  enum Typedepiece type;
  enum Couleur couleur;
  enum Zone zone; // En jeu ou hors-jeu
  struct Position position;

 };

struct Tour {
  int noTour;
  struct Deplacement noir;
  struct Position promotionNoir;
  struct Deplacement blanc;
  struct Position promotionBlanc;
  enum Etat etat;
  struct Tour *tourSuivant;
};

//Les Variables globales

 //les pieces

struct Piece pieces[14];

 //le plateau de jeu

   //plateau[i][j] == NULL ssi la case est vide
struct Piece* plateau[5][5];

   //l'historique
struct Tour *premierTour;
struct Tour *tourCourant;
