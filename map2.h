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
	noeud* p = RACINE();
	noeud* lastNotLess = APRES;
	if (p == nullptr) {
		return iterator(lastNotLess);
	}
	Tclef key = p->CONTENU->first;
	while (c != key) {
		if (c < key) {
			if (p->GAUCHE == nullptr) {		
				return iterator(p);
			}
			lastNotLess = p;
			p = p->GAUCHE;
		}
		else if (key < c) {
			if (p->DROITE == nullptr) {
				return iterator(lastNotLess);
			}
			p = p->DROITE;
		}
		key = p->CONTENU->first;
	}
	return iterator(p);
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
	noeud *pDroite = p->DROITE;
	noeud *pGauche = p->GAUCHE;
	noeud *pGaucheGauche = pGauche->GAUCHE;
	noeud *pGaucheDroite = pGauche->DROITE;
	if (pDroite != nullptr && (pDroite->POIDS * 3) < pGauche->POIDS) {
		if (pGaucheGauche == nullptr ||
			(pGaucheDroite != nullptr && 
				pGaucheGauche != nullptr && 
				!(pGaucheDroite->POIDS < pGaucheGauche->POIDS * 2))
		) {
			rotation_droite_gauche(pGauche);
		}
		rotation_gauche_droite(p);
	} else if (pDroite == nullptr && p->POIDS > 3) {
		rotation_gauche_droite(p);
	}

}
template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::transferer_vers_la_gauche(noeud*& p){
	noeud *pDroite = p->DROITE;
	noeud *pGauche = p->GAUCHE;
	noeud *pDroiteGauche = pDroite->GAUCHE;
	noeud *pDroiteDroite = pDroite->DROITE;
	if (pGauche != nullptr && (pGauche->POIDS * 3) < pDroite->POIDS) {
		if (pDroiteDroite == nullptr ||
			(pDroiteGauche != nullptr && 
				pDroiteDroite != nullptr && 
				!(pDroiteGauche->POIDS < pDroiteDroite->POIDS * 2))
		) {
			rotation_gauche_droite(pDroite);
		}
		rotation_droite_gauche(p);
	} else if (pGauche == nullptr && p->POIDS > 3) {
		rotation_droite_gauche(p);
	}

}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::rotation_gauche_droite(noeud*& p){
    noeud *temp = p;
    p = p->GAUCHE;
    temp->GAUCHE = p->DROITE;
    p->DROITE = temp;

	if (temp->PARENT->GAUCHE == temp) {
		temp->PARENT->GAUCHE = p;
	}
	else if (temp->PARENT->DROITE == temp) {
		temp->PARENT->DROITE = p;
	}

    noeud *pDroite = p->DROITE;
    noeud *droiteGauche = pDroite->GAUCHE;
    noeud *droiteDroite = pDroite->DROITE;
	p->PARENT = temp->PARENT;
	pDroite->PARENT = p;
	if (droiteGauche != nullptr) {
		droiteGauche->PARENT = pDroite;
	}
    pDroite->POIDS = ((droiteDroite != nullptr) ? droiteDroite->POIDS : 0) 
    				+ ((droiteGauche != nullptr) ? droiteGauche->POIDS : 0) + 1;
    p->POIDS = pDroite->POIDS + ((p->GAUCHE != nullptr) ? p->GAUCHE->POIDS : 0) + 1;
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::rotation_droite_gauche(noeud*& p){
	noeud *temp = p;
    p = p->DROITE;
    temp->DROITE = p->GAUCHE;
    p->GAUCHE = temp;

	if (temp->PARENT->GAUCHE == temp) {
		temp->PARENT->GAUCHE = p;
	}
	else if (temp->PARENT->DROITE == temp) {
		temp->PARENT->DROITE = p;
	}

    noeud *pGauche = p->GAUCHE;
    noeud *pGaucheGauche = pGauche->GAUCHE;
    noeud *pGaucheDroite = pGauche->DROITE;
	p->PARENT = temp->PARENT;
	pGauche->PARENT = p;
	if (pGaucheDroite != nullptr) {
		pGaucheDroite->PARENT = pGauche;
	}
    pGauche->POIDS = ((pGaucheDroite != nullptr) ? pGaucheDroite->POIDS : 0) 
    				+ ((pGaucheGauche != nullptr) ? pGaucheGauche->POIDS : 0) + 1;
    p->POIDS = ((p->DROITE != nullptr) ? p->DROITE->POIDS : 0) + pGauche->POIDS + 1;
}

#endif /* map2_h */