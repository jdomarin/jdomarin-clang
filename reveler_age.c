#include <stdio.h>
#include <stdlib.h>

#define NUM_JOURS_MAX 31
#define NUM_JOURS_MIN 28
#define NUM_MOIS 12


//date de naissance (la mienne ;) )
const unsigned int jdn = 24;//jour de naissance
const unsigned int mdn = 6;//mois de naissance
const unsigned int adn = 1990;//année de naissance

//calculer mon âge à partir d'une date donnée
void calcul(int jour, int mois, int annee)
{
	#ifndef between_months(n,p)
	#define between_months(n,p) ((mois == (n) && jour > jdn) || (mois == (p) && jour < jdn))
	#ifndef QUANTIEME(x)
	#define QUANTIEME(x) (x-jdn+jour) % (x)
	int ares, mres, jres; //nombre d'années, de mois et de jours à afficher en sortie standard
	//PARTIE 1: Calcul de l'année
	if(mois < mdn || (mois == mdn && jour < jdn))
	{	//retourne le nombre d'années moins un puisque l'anniversaire n'a pas eu lieu
		ares = annee - adn - 1;
	}
	else
	{
		ares = annee - adn;
	}
	//PARTIE 2: Calcul du mois
	if(mois < mdn)
	{
		mres = mois + NUM_MOIS - mdn;
		if(jour < jdn) 
			mres--;
	}
	else if(mois == mdn)
	{
		if(jour < jdn)
			mres = NUM_MOIS - 1;
		else
			mres = 0;
	}
	else
	{
		mres = mois - mdn;
		if(jour < jdn) mres--;
	}
	//PARTIE 3: Calcul du jour
	if(between_months(2,3)) // 24 février- 23 mars
	{
		if(annee%4 == 0)
		{	//année bissextile
			jres = QUANTIEME(NUM_JOURS_MIN + 1);
		}
		else
		{	//année non bissextile
			jres = QUANTIEME(NUM_JOURS_MIN);
		}
	}
	else if (between_months(4,5) || between_months(6,7) || between_months(9,10) || between_months(11,12)) 
	{	// 24 avril-23 mai; 24 juin-23 juillet; 24 sept-23 oct; 24 nov-23 déc  
		jres = QUANTIEME(NUM_JOURS_MAX - 1);
	}
	else
	{	// autres périodes d'un mois commençant le 24 d'un mois de 31 jours
		jres = QUANTIEME(NUM_JOURS_MAX);
	}
	printf("Mon âge : %d ans, %d mois, %d jour(s).\n", ares, mres, jres);
	#endif
	#endif
}

int main(int argc, char* argv[])
{
	unsigned int jcour, mcour, acour;//jour, mois, année courantes
	if(argc != 4)
	{
		printf("Usage: calc_age jour mois année\n");
		return 1;
	}
	jcour = atoi(argv[1]);
	mcour = atoi(argv[2]);
	acour = atoi(argv[3]);
	if(jcour < 1 || jcour > NUM_JOURS_MAX)
	{
		printf("Numéro de jour invalide.\n");
		return 2;
	}
	if(mcour < 1 || mcour > NUM_MOIS)
	{
		printf("Numéro de mois invalide.\n");
		return 3;
	}
	if(acour<adn || (acour==adn && mcour<mdn) || (acour==adn && mcour==mdn && jcour<jdn))
	{
		printf("Erreur : risque d'âge négatif.\n");
		return 4;
	}
	calcul(jcour, mcour, acour);
	return 0;
}
