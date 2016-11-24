//
//  map2.h
//  Map-WBT
//
//  Jean Goulet
//  Copyleft 2016 UdeS
//

#ifndef map2_h
#define map2_h

///////////////////////////////////////////////////////////////////////////
// lower_bound

template <typename Tclef, typename Tvaleur>
typename map<Tclef, Tvaleur>::iterator map<Tclef, Tvaleur>::lower_bound(const Tclef& c)const {
	// DJDUBE : NEED TO TEST IF THIS WORKS EVERYTIME
	noeud* p = RACINE();
	noeud* lastNotLess = APRES;
	Tclef key = p->CONTENU->first;
	while (p != nullptr) {
		if (c < key) {
			lastNotLess = p;
			if (p->GAUCHE == nullptr) {
				break;
			}
			p = p->GAUCHE;
		}
		else if (key < c) {
			if (p->DROITE == nullptr) {
				break;
			}
			p = p->DROITE;
		}
		else {
			lastNotLess = p;
			break;
		}
		key = p->CONTENU->first;
	}
	return iterator(lastNotLess);


}

///////////////////////////////////////////////////////////////////////////
// fonctions supplementaires de la class iterator
// ce sont des fonctions statiques, qui n'ont pas de paramètre imlicite
// STUBS qui prennent toujours un temps O(log n)
// a remplacer par des fonctions O(1) amorti

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::iterator::avancer(noeud*& p){
	assert(p != nullptr);
	noeud *ici;
	if (p->DROITE == nullptr){
		for (ici = p->PARENT; ici != nullptr && ici->GAUCHE != p; p = ici, ici = ici->PARENT);
	}
	else {
		for (ici = p->DROITE; ici->GAUCHE != nullptr; ici = ici->GAUCHE);
	}
	p = ici;
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::iterator::reculer(noeud*& p){
	assert(p != nullptr);
	noeud *ici;
	if (p->GAUCHE == nullptr) {
		for (ici = p->PARENT; ici != nullptr && ici->DROITE != p; p = ici, ici = ici->PARENT);
	}
	else {
		for (ici = p->GAUCHE; ici->DROITE != nullptr; ici = ici->DROITE);
	}
	p = ici;
}


///////////////////////////////////////////////////////////////////////////
// equilibretransferer_vers_la_droite


template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::transferer_vers_la_droite(noeud*& p) {
	std::cout << "transferer_vers_la_droite : " << p->CONTENU->first << std::endl;

//	if (p->POIDS > 3) {
	if (p->DROITE != nullptr && p->GAUCHE->POIDS > (p->DROITE->POIDS * 3)) {
		if (p->GAUCHE->DROITE != nullptr
			&& p->GAUCHE->GAUCHE != nullptr
			&& p->GAUCHE->DROITE->POIDS >= ((p->GAUCHE->GAUCHE->POIDS * 2))) {
			rotation_droite_gauche(p->GAUCHE);
		}
		rotation_gauche_droite(p);
	}else if (p->DROITE == nullptr && p->POIDS > 3) {
		rotation_gauche_droite(p);
	}

}


template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::transferer_vers_la_gauche(noeud*& p){
	if (p->GAUCHE != nullptr && p->DROITE->POIDS > (p->GAUCHE->POIDS * 3)) {
		if (p->DROITE->GAUCHE != nullptr
			&& p->DROITE->DROITE != nullptr
			&& p->DROITE->GAUCHE->POIDS >= ((p->DROITE->DROITE->POIDS * 2))) {
			rotation_gauche_droite(p->DROITE);
		}
		rotation_droite_gauche(p);
	}
		else if (p->GAUCHE == nullptr && p->DROITE->POIDS > 3 && p->POIDS > 3) {
		rotation_droite_gauche(p);
	}

}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::rotation_gauche_droite(noeud*& p){
    // CAN'T ROTATE IF THE LEFT->RIGHT >= (LEFT->LEFT*2)  ------- DJDUBE : CHECK IF IT'S RIGHT!!!!!!!!


    noeud *temp = p;
    p = p->GAUCHE;
    temp->GAUCHE = p->DROITE;
    p->DROITE = temp;

	p->PARENT = temp->PARENT;
	p->DROITE->PARENT = p;
	if (p->DROITE->GAUCHE != nullptr) {
		p->DROITE->GAUCHE->PARENT = p->DROITE;
	}

    balancer_poids(p);
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::rotation_droite_gauche(noeud*& p){

	noeud *temp = p;
    p = p->DROITE;
    temp->DROITE = p->GAUCHE;
    p->GAUCHE = temp;

	p->PARENT = temp->PARENT;
	p->GAUCHE->PARENT = p;
	if (p->GAUCHE->DROITE != nullptr) {
		p->GAUCHE->DROITE->PARENT = p->GAUCHE;
	}

    balancer_poids(p);
}



/*


            !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            DJDUBE : THIS NEEDS TO BE ERASED AND REPLACED IN rotation_... !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



*/
template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::balancer_poids(noeud*& p){
    noeud *gaucheGauche = p->GAUCHE->GAUCHE;
    size_t poidsGaucheGauche = (gaucheGauche != nullptr) ? gaucheGauche->POIDS : 0;

    noeud *gaucheDroite = p->GAUCHE->DROITE;
    size_t poidsGaucheDroite = (gaucheDroite != nullptr) ? gaucheDroite->POIDS : 0;

    noeud *droiteGauche = p->DROITE->GAUCHE;
    size_t poidsDroiteGauche = (droiteGauche != nullptr) ? droiteGauche->POIDS : 0;

    noeud *droiteDroite = p->DROITE->DROITE;
    size_t poidsDroiteDroite = (droiteDroite != nullptr) ? droiteDroite->POIDS : 0;

    p->DROITE->POIDS = poidsDroiteDroite + poidsDroiteGauche + 1;
    p->GAUCHE->POIDS = poidsGaucheDroite + poidsGaucheGauche + 1;
    p->POIDS = p->DROITE->POIDS + p->GAUCHE->POIDS + 1;
}



#endif /* map2_h */
