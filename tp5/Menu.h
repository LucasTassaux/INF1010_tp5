


//////////// A SUPPRIMER ///////////////////
//Menu a ete remplace par le gestionnaire









/*
* Date : 25 février 2019
* Auteur : AbdeB
*/

/*#ifndef MENU_H
#define MENU_H 

//#include "Plat.h"
#include "PlatBio.h"
#include "PlatBioVege.h"
#include "PlatVege.h"
#include "pointers.h"
#include "def.h"
#include <fstream>
#include "GestionnairePlats.h"

#include <vector>
//////////////////// A
/*using std::vector;  //? On ne devrait normalement pas faire de "using" global dans un .h, mais c'est accepté en INF1010.

class Menu {
public: 
	// Constructeurs.

	Menu(); 
	Menu(string fichier, TypeMenu type);
	Menu(const Menu& menu);// TODO
	~Menu();// TODO
	// Getters.
	GestionnairePlats* getGestionnaire() const;

	// Autres méthodes.;
	Menu& operator+=(owner<Plat*> plat);  // TODO //? Le parametre est indique "owner" pour montrer que cette methode prend possession du pointeur qui lui est passe, mais owner<Plat*> est equivalent à Plat*; voir pointers.h .
	Menu& operator=(const Menu& menu); // TODO
	//void lireMenu(const string& fichier); 
	//Plat* trouverPlatMoinsCher() const;
    //Plat* lirePlatDe(LectureFichierEnSections& fichier);
	friend ostream& operator<<(ostream& os, const Menu& menu); // TODO

private : 
	//vector<owner<Plat*>> listePlats_; //? "owner" est juste un indicateur que la classe est propriétaire des plats (et devra faire un "delete"), mais owner<Plat*> est équivalent à Plat*; voir pointers.h .
	//vector<owner<Vege*>> listePlatsVege_;

	GestionnairePlats* gestionnairePlats_;
	TypeMenu type_;
};

#endif // !MENU_H*/
