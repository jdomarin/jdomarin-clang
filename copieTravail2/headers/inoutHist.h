
/* Description :initialisation du plateau et des pieces pour avoir la position initial standard
   paramètres : aucuns
   précondition : aucune
   postcondition: plateau et pièces représentent la position initial du plateau de jeu
variable retournée : 1 -> chargement effectué sans problème
                     0 -> Erreur lors du chargement
*/
int initialisation();


/* Description : Chargement d'une partie enregistrée
   paramètres : le nom du fichier de sauvegarde d'une partie
   précondition : aucune
   postcondition: plateau, pièces et l'historique représentent la partie sauvegardée dans fich
*/
int chargement(char* fich);

/* Description : Libére la mémoire allouée pour enregistrer l'historique de la partie
   paramètres : l'adresse du premier tour à libérer
   précondition : aucune
   postcondition: On ne peut plus écrire dans l'historique
*/
void freeHist(struct Tour* tour);


/* Description : sauvegarde une partie dans un fichier
   paramètres : fichInit : adresse du fichier contenant la position initial du plateau
                fichSauv : adresse du fichier où écrire la sauvegarde
   précondition : historique des tours est correctement tenu
   postcondition: fichSauv contient une sauvegarde de la partie
variable retournée : 1 -> chargement effectué sans problème
                     0 -> Erreur lors du chargement
*/
void sauve(char* fichInit, char* fichSauv);
