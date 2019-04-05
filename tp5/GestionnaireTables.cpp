/********************************************
* Titre: Travail pratique #5 - gestionnaireTables.cpp
* Date: 21 mars 2019
* Auteur: Moussa Traor� & Ryan Hardie & Wassim Khene
*******************************************/


#include "GestionnaireTables.h"
#include "LectureFichierEnSections.h"

GestionnaireTables::GestionnaireTables(){

}

Table * GestionnaireTables::getTable(int id) const
{
	auto trouveTable = [id](Table* table) -> bool {
		if (table->getId()==id) {
			return true;
		}
		else {
			return false;
		}
	};

	set<Table*>::iterator debut = getConteneur().begin();
	set<Table*>::iterator fin = getConteneur().end();
	return (*find_if(debut, fin, trouveTable));

}

Table * GestionnaireTables::getMeilleureTable(int tailleGroupe) const
{
	set<Table*>::iterator debut = getConteneur().begin();
	set<Table*>::iterator fin = getConteneur().end();
	Table* meilleurTable = new Table(-1, 10000);
	
	for (debut; debut != fin; debut++) {
		if ((*debut)->getNbPlaces() < meilleurTable->getNbPlaces() && (*debut)->getNbPlaces() > tailleGroupe && !(*debut)->estOccupee()) {
			meilleurTable = (*debut);
		}
	}
	return meilleurTable;

}

void GestionnaireTables::lireTables(const string& nomFichier)
{
	LectureFichierEnSections fichier{ nomFichier };
	fichier.allerASection("-TABLES");
	while (!fichier.estFinSection()) {
		int id, nbPlaces;
		fichier >> id >> nbPlaces;

		ajouter(new Table(id, nbPlaces));
	}
}

GestionnaireTables::~GestionnaireTables()
{
	set<Table*>::iterator fin = getConteneur().end();
	for (set<Table*>::iterator debut = getConteneur().begin(); debut != fin; debut++) {
		delete (*debut);
	}

}

void GestionnaireTables::afficherTables(ostream & os) const
{
	set<Table*>::iterator debut = getConteneur().begin();
	set<Table*>::iterator fin = getConteneur().end();
	for (debut; debut != fin; debut++) {
		os << (*debut);
	}
}

GestionnaireTables& GestionnaireTables::operator+=(Table* table)
{
	ajouter(table);
	return *this;
}