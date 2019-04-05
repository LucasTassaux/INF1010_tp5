/********************************************
* Titre: Travail pratique #5 - gestionnairePlats.cpp
* Date: 21 mars 2019
* Auteur: Moussa Traor� & Ryan Hardie & Wassim Khene
*******************************************/

#include "GestionnairePlats.h"
#include "LectureFichierEnSections.h"
#include "PlatBio.h"
#include "PlatVege.h"
#include "PlatBioVege.h"




void GestionnairePlats::lirePlats(const string& nomFichier, TypeMenu type)
{
	LectureFichierEnSections fichier{ nomFichier };
	fichier.allerASection(entetesDesTypesDeMenu[static_cast<int>(type)]);
	while (!fichier.estFinSection())
		ajouter(lirePlatDe(fichier));
}

pair<string, Plat*> GestionnairePlats::lirePlatDe(LectureFichierEnSections& fichier)
{
	auto lectureLigne = fichier.lecteurDeLigne();
	Plat* plat;
	string nom, typeStr;
	TypePlat type;
	double prix, coutDeRevient;
	lectureLigne >> nom >> typeStr >> prix >> coutDeRevient;
	type = TypePlat(stoi(typeStr));
	double ecotaxe, vitamines, proteines, mineraux;
	switch (type) {
	case TypePlat::Bio:
		lectureLigne >> ecotaxe;
		plat = new PlatBio{ nom, prix, coutDeRevient, ecotaxe };
		break;
	case TypePlat::BioVege:
		lectureLigne >> ecotaxe >> vitamines >> proteines >> mineraux;
		plat = new PlatBioVege(nom, prix, coutDeRevient, ecotaxe, vitamines, proteines, mineraux);
		break;
	case TypePlat::Vege:
		lectureLigne >> vitamines >> proteines >> mineraux;
		plat = new PlatVege(nom, prix, coutDeRevient, vitamines, proteines, mineraux);
		break;
	default:
		plat = new Plat{ nom, prix, coutDeRevient };
	}
	return pair<string, Plat*>(plat->getNom(), plat);
}

void GestionnairePlats::afficherPlats(ostream & os)
{
	map<string, Plat*>::iterator debut = getConteneur().begin();
	map<string, Plat*>::iterator fin = getConteneur().end();
	for (debut; debut != fin; debut++) {
		(*debut).second->afficherPlat(os);
	}
}

GestionnairePlats::GestionnairePlats(){}

GestionnairePlats::GestionnairePlats(const string& nomFichier, TypeMenu type) : type_(type) {
	lirePlats(nomFichier, type);
}

GestionnairePlats::GestionnairePlats(GestionnairePlats* gestionnaire) : type_(gestionnaire->getType()) {
	map<string, Plat*> c = gestionnaire->getConteneur();
	map<string, Plat*>::iterator debut = c.begin();
	map<string, Plat*>::iterator fin = c.end();
	for (debut; debut != fin; debut++) {
		ajouter(*debut);
	}
}

GestionnairePlats::~GestionnairePlats()
{
	map<string, Plat*>::iterator fin = getConteneur().end();
	for (map<string, Plat*>::iterator debut = getConteneur().begin(); debut != fin; debut++) {
		delete (*debut).second;
	}
}


TypeMenu GestionnairePlats::getType() const
{
	return type_;
}


Plat * GestionnairePlats::allouerPlat(Plat * plat)
{
	Plat* ptrplat = new Plat(*plat);
		return ptrplat;
}

Plat * GestionnairePlats::trouverPlatMoinsCher() const
{
	map<string, Plat*>::iterator debut = getConteneur().begin();
	map<string, Plat*>::iterator fin = getConteneur().end();

	return (*min_element(debut, fin, FoncteurPlatMoinsCher())).second;
}

Plat * GestionnairePlats::trouverPlatPlusCher() const
{
	
	auto plusCher = [](pair<string, Plat*> plat1, pair<string, Plat*> plat2) -> bool {
		if (plat2.second->getPrix() > plat1.second->getPrix()) {
			return true;
		}
		else {
			return false;
		}
	};

	map<string, Plat*>::iterator debut = getConteneur().begin();
	map<string, Plat*>::iterator fin = getConteneur().end();
	return (*max_element(debut, fin, plusCher)).second;
	
}

Plat * GestionnairePlats::trouverPlat(const string & nom) const
{
	auto comparaison = [nom](pair<string, Plat*> plat) -> bool {
		if (plat.first == nom) {
			return true;
		}
		else {
			return false;
		}
		

	};
	map<string, Plat*>::iterator debut = getConteneur().begin();
	map<string, Plat*>::iterator fin = getConteneur().end();

	auto variable = find_if(debut, fin, comparaison);

	if (variable == fin) {
		return nullptr;
	}

	return (*find_if(debut, fin, comparaison)).second;

}

vector<pair<string, Plat*>> GestionnairePlats::getPlatsEntre(double borneInf, double borneSup)
{
	FoncteurIntervalle intervalle(borneInf, borneSup);
	vector<pair<string, Plat*>> retour;
	map<string, Plat*>::iterator debut = getConteneur().begin();
	map<string, Plat*>::iterator fin = getConteneur().end();
	copy_if(debut, fin, back_inserter(retour), intervalle);
	return retour;

}



