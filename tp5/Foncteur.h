/********************************************
* Titre: Travail pratique #5 - Foncteur.h
* Date: 21 mars 2019
* Auteur: Moussa Traor� & Ryan Hardie & Wassim Khene
*******************************************/

#pragma once

#include <algorithm>
#include "Plat.h"
#include "Table.h"

using namespace std;


class FoncteurPlatMoinsCher
{
public: 
	FoncteurPlatMoinsCher() {}
	bool operator () (pair<string, Plat*> plat1_, pair<string, Plat*> plat2_) {
		if (plat2_.second->getPrix() < plat1_.second->getPrix()) {
			return true;
		}
		else {
			return false;
		}
	}


};


class FoncteurIntervalle
{
public : 
	FoncteurIntervalle(double borneInf, double borneSup) : borneInf_(borneInf), borneSup_(borneSup) {};

	bool operator () (pair<string, Plat*> plat) {
		if (plat.second->getPrix() < borneSup_&& plat.second->getPrix() > borneInf_) {
			return true;
		}
		else{
			return false;

		}
		
	}
private :
	double borneInf_;
	double borneSup_;


};

/*class FoncteurMeilleureTable
{
public:
	FoncteurMeilleureTable() {}
	bool operator () (Table* table1, Table* table2, int taille){
		if (table1->getNbPlaces() < table2->getNbPlaces() && table1->getNbPlaces() > taille && !table1->estOccupee() ) {
			return true;
		}
		else {
			return false;
		}
	}


};*/
