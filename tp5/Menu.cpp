/*
* Date : 25 février 2019
* Auteur : AbdeB
*/

#include "Menu.h"
#include "LectureFichierEnSections.h"
#include <cassert>  //? Contient "assert" qui permet de s'assurer qu'une expression est vraie, et terminer le programme avec un message d'erreur en cas contraire.
using namespace std;

// Constructeurs.

/*Menu::Menu() :
	type_{TypeMenu::Matin},
	gestionnairePlats_{ new GestionnairePlats() }
{
}

Menu::Menu(string fichier, TypeMenu type) :
	type_{type},
	gestionnairePlats_{new GestionnairePlats()}
{
	gestionnairePlats_->lirePlats(fichier, type_); 
}

Menu::~Menu() // TODO
{
	delete gestionnairePlats_;
}

GestionnairePlats * Menu::getGestionnaire() const
{
	return gestionnairePlats_;
}

// DEPLACE
//Plat* Menu::allouerPlat(Plat* plat) {
//    return plat->clone();
//}

//TODO
Menu::Menu(const Menu & menu) : type_(menu.type_), gestionnairePlats_(new GestionnairePlats(menu.gestionnairePlats_))
{   
}
//TODO
Menu & Menu::operator=(const Menu & menu)
{
	if (this != &menu)
	{
		delete gestionnairePlats_;
		*gestionnairePlats_ = new GestionnairePlats(*menu.gestionnairePlats_);
		type_ = menu.type_;
	}
	return *this;
}

// Autres methodes.
//PLUS UTILE AVEC LE FONCTEUR AJOUTER DU GESTIONNAIRE
//Menu& Menu::operator+=(owner<Plat*> plat) {
//	gestionnairePlats_->ajouter(pair<string, Plat*>(plat->getNom(), plat));
//	return *this;
//}

// déplacé dans gestionnairePlat
/*void Menu::lireMenu(const string& nomFichier) {
	LectureFichierEnSections fichier{nomFichier};
	fichier.allerASection(entetesDesTypesDeMenu[static_cast<int>(type_)]);
	while (!fichier.estFinSection())
		*this += lirePlatDe(fichier);
}*/

// déplacé dans gestionnairePlat
/*Plat* Menu::trouverPlatMoinsCher() const
{
	assert(!listePlats_.empty() && "La liste de plats de doit pas etre vide pour trouver le plat le moins cher.");
	Plat* minimum = listePlats_[0];
	for (Plat* plat : listePlats_)
		if (*plat < *minimum)
			minimum = plat;

	return minimum;
}*/

// déplacé dans gestionnairePlat
/*Plat* Menu::trouverPlat(string_view nom) const
{
	for (Plat* plat : listePlats_)
		if (plat->getNom() == nom)
			return plat; 

	return nullptr; 
}*/

// déplacé dans gestionnairePlat
/*Plat* Menu::lirePlatDe(LectureFichierEnSections& fichier)
{
    auto lectureLigne = fichier.lecteurDeLigne();
    
    string nom, typeStr;
    TypePlat type;
    double prix, coutDeRevient;
    lectureLigne >> nom >> typeStr >> prix >> coutDeRevient;
    type = TypePlat(stoi(typeStr));
    double ecotaxe, vitamines, proteines, mineraux;
    switch (type) {
        case TypePlat::Bio :
            lectureLigne >> ecotaxe;
            return new PlatBio{ nom, prix, coutDeRevient, ecotaxe };
        case TypePlat::BioVege:
            lectureLigne >> ecotaxe >> vitamines >> proteines >> mineraux;
            return new PlatBioVege(nom, prix, coutDeRevient, ecotaxe, vitamines, proteines, mineraux);
        case TypePlat::Vege:
            lectureLigne >> vitamines >> proteines >> mineraux;
            return new PlatVege(nom, prix, coutDeRevient, vitamines, proteines, mineraux);
        default:
            return new Plat{nom, prix, coutDeRevient};
    }
    
}*/

// Fonctions globales.

/*ostream& operator<<(ostream& os, const Menu& menu)
{   
	menu.gestionnairePlats_->afficherPlats(os);
	/*for (size_t i = 0; i < menu.listePlats_.size(); ++i)
		 menu.listePlats_[i]->afficherPlat(os);
    os<<endl;
	os << "MENU ENTIEREMENT VEGETARIEN\n";
	if (menu.listePlatsVege_.size() == 0)
		os << "Il n'y a malheureusement pas de plat vegetarien, nous sommes sincerement desole";
    else
    {  for (unsigned i = 0; i < menu.listePlatsVege_.size(); ++i)
          menu.listePlatsVege_[i]->afficherVege(os);
	}
	return os;
}*/
