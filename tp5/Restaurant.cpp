/*
* Date : 25 f�vrier 2019
* Auteur : AbdeB
*/

#include "Restaurant.h"
#include "LectureFichierEnSections.h"
#include "debogageMemoire.hpp"
#include <cassert>
using namespace std;

//constructeurs 
Restaurant::Restaurant() :
	Restaurant{"menu.txt", "Inconnu", TypeMenu::Matin}
{
}

Restaurant::Restaurant(const string& nomFichier, string_view nom, TypeMenu moment) :
	nom_{nom},
	momentJournee_{moment},
	chiffreAffaire_{0},
	menuMatin_{new GestionnairePlats(nomFichier, TypeMenu::Matin)},
	menuMidi_ {new GestionnairePlats(nomFichier, TypeMenu::Midi )},
	menuSoir_ {new GestionnairePlats(nomFichier, TypeMenu::Soir )},
	fraisLivraison_{}
{
	tables_ = new GestionnaireTables();
	tables_->lireTables(nomFichier); 
	lireAdresses(nomFichier);
}

// Destructeur.
Restaurant::~Restaurant()
{
	delete menuMatin_;
	delete menuMidi_;
	delete menuSoir_;
	delete tables_;
	
}


// Setters.

void Restaurant::setMoment(TypeMenu moment)
{
	momentJournee_ = moment; 
}

void Restaurant::setNom(string_view nom)
{
	nom_ = nom;
}

 void  Restaurant::setChiffreAffaire( double chiffre)
{ chiffreAffaire_ = chiffre;
}
// Getters.

string Restaurant::getNom() const
{
	return nom_; 
}

TypeMenu Restaurant::getMoment() const
{
	return momentJournee_; 
}



// Autres methodes.

void Restaurant::libererTable(int id){
		chiffreAffaire_ += tables_->getTable(id)->getChiffreAffaire();
		chiffreAffaire_ += calculerReduction(tables_->getTable(id)->getClientPrincipal(), tables_->getTable(id)->getChiffreAffaire(), id == tables_->getTable(INDEX_TABLE_LIVRAISON)->getId());
		tables_->getTable(id)->libererTable();
	}

ostream& operator<<(ostream& os, const Restaurant& restaurent)
{
	os << "Le restaurant " << restaurent.getNom();
	if (restaurent.chiffreAffaire_ != 0)
		os << " a fait un chiffre d'affaire de : " << restaurent.chiffreAffaire_ << "$" << endl;
	else
		os << " n'a pas fait de benefice ou le chiffre n'est pas encore calcule." << endl;

	os << "-Voici les tables : " << endl;

	restaurent.tables_->afficherTables(os);
	

	os << "-Voici son menu : " << endl;
	for (TypeMenu typeMenu : { TypeMenu::Matin, TypeMenu::Midi, TypeMenu::Soir }) {
		GestionnairePlats* menu = restaurent.getMenu(typeMenu);
		os << restaurent.getNomTypeMenu(typeMenu) << " : " << endl;
		menu->afficherPlats(os); 
		os << endl
			<< "Le plat le moins cher est : ";
		menu->trouverPlatMoinsCher()->afficherPlat(os);
		os << endl;
	}
	return os;
}

void Restaurant::commanderPlat(string nom, int idTable)
{
	if (tables_->getTable(idTable) && tables_->getTable(idTable)->estOccupee())
		if (Plat* plat = menuActuel()->trouverPlat(nom)) {
			tables_->getTable(idTable)->commander(plat);
			return;
		}
	cout << "Erreur : table vide ou plat introuvable." << endl << endl;
}

bool Restaurant::operator <(const Restaurant& autre) const 
{
	return chiffreAffaire_ < autre.chiffreAffaire_;
}
//
//void Restaurant::lireTables(const string& nomFichier)
//{
//	LectureFichierEnSections fichier{nomFichier};
//	fichier.allerASection("-TABLES");
//	while (!fichier.estFinSection()) {
//		int id, nbPlaces;
//		fichier >> id >> nbPlaces;
//		*this += new Table(id, nbPlaces);
//	}
//}

//Restaurant& Restaurant::operator+=(owner<Table*> table)
//{
//	tables_->ajouter(table); 
//	return *this;
//}
bool Restaurant::placerClients(Client* client)
{
	const int tailleGroupe = client->getTailleGroupe();
	Table* table = tables_->getMeilleureTable(tailleGroupe);
	if (table->getId()!=-1) {
		table->placerClients(client->getTailleGroupe());
		return true;
	}
	else return false;

	//TODO : trouver la table la plus adaptée pour le client. Fait
	//TODO : Si possible assigner la table au client sinon retourner false. Fait
}

bool Restaurant::livrerClient(Client* client, const vector<string>& commande)
{
	if (dynamic_cast<ClientPrestige*>(client)) {
		// TODO: Placer le client principal a la table fictive en utilisant la classe GestionnaireTables.
		tables_->getTable(INDEX_TABLE_LIVRAISON)->setClientPrincipal(client);
		// TODO: Placer client à la table fictive en utilisant la classe GestionnaireTables.
		tables_->getTable(INDEX_TABLE_LIVRAISON)->placerClients(client->getTailleGroupe());
		// Placer la commande
		for (unsigned int i = 0; i < commande.size(); i++)
			commanderPlat(commande[i], INDEX_TABLE_LIVRAISON);
		// Liberer la table fictive.
		libererTable(INDEX_TABLE_LIVRAISON);
		return true;
	}
	else {
		return false;
	}
}

double Restaurant::calculerReduction(Client* client, double montant, bool estLivraison)
{
    return client->getReduction(*this, montant, estLivraison);
}

double Restaurant::getFraisLivraison(ZoneHabitation zone) const
{
	return fraisLivraison_[static_cast<int>(zone)];
}

GestionnairePlats* Restaurant::getMenu(TypeMenu typeMenu) const
{
	switch (typeMenu) {
	case TypeMenu::Matin : return menuMatin_;
	case TypeMenu::Midi  : return menuMidi_;
	case TypeMenu::Soir  : return menuSoir_;
	}
	assert(false && "Le type du menu est invalide");
	return nullptr;  // On ne devrait jamais se rendre � cette ligne.
}

GestionnairePlats* Restaurant::menuActuel() const
{
	return getMenu(momentJournee_);
}

/*Table* Restaurant::getTable(int id) const
{
	for (Table* table : tables_)
		if (table->getId() == id)
			return table;
	return nullptr;
}*/

void Restaurant::lireAdresses(const string& nomFichier)
{
	LectureFichierEnSections fichier{nomFichier};
	fichier.allerASection("-ADDRESSES");
	while (!fichier.estFinSection()) {
		int zone; double frais;
		fichier >> zone >> frais;
		fraisLivraison_[zone] = frais;
	}
}

double Restaurant::getChiffreAffaire() {
	return chiffreAffaire_;
}

GestionnaireTables * Restaurant::getTables() const
{

	return tables_;
}

string Restaurant::getNomTypeMenu(TypeMenu typeMenu) const
{
	return string{nomsDesTypesDeMenu[static_cast<int>(typeMenu)]};
}
