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
typename map<Tclef,Tvaleur>::iterator map<Tclef,Tvaleur>::lower_bound(const Tclef& c)const{
    // DJDUBE : NEED TO TEST IF THIS WORKS EVERYTIME
    noeud* p = RACINE();
    noeud* lastNotLess = nullptr;
    Tclef key = p->CONTENU->first;
    while (p != nullptr) {
        if (c < key) {
            lastNotLess = p;
            if (p->GAUCHE == nullptr) {
                break;
            }
            p = p->GAUCHE;
        } else if (key < c) {
            if (p->DROITE == nullptr) {
                break;
            }
            p = p->DROITE;
        } else {
            lastNotLess = p;
            break;
        }
        key = p->CONTENU->first;
    }
    /*if (lastNotLess != nullptr) {
        std::cout << lastNotLess->CONTENU->first << std::endl;
    } else {
        std::cout << "NULLPTR" << std::endl;
    }*/
    return iterator(lastNotLess);
}

///////////////////////////////////////////////////////////////////////////
// fonctions supplementaires de la class iterator
// ce sont des fonctions statiques, qui n'ont pas de paramètre imlicite
// STUBS qui prennent toujours un temps O(log n)
// a remplacer par des fonctions O(1) amorti

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::iterator::avancer(noeud*& p){
    //AVANCER le pointeur p vers le prochain noeud en inordre
    //cette fonction fait automatiquement exception
    //si on avance au-dela de la fin
    assert(p->DROITE!=p);
    const Tclef& a_suivre=p->CONTENU->first;
    //trouver la cellule suivant=APRES en remontant
    for(p=p->PARENT;p->POIDS!=0;p=p->PARENT);
    noeud *q=p->GAUCHE; //la racine
    while(q!=nullptr)
        if(a_suivre < q->CONTENU->first){
            p=q;
            q=q->GAUCHE;
        }
        else
            q=q->DROITE;
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::iterator::reculer(noeud*& p){
    //RECULER le pointeur p vers le noeud precedent en inordre
    //si on est a la fin, descendre a droite
    if(p->POIDS==0){
        for(p=p->GAUCHE;p->DROITE!=nullptr;p=p->DROITE);
        return;
    }
    //trouver la cellule suivant=APRES en remontant
    const Tclef& a_preceder=p->CONTENU->first;
    for(;p->POIDS!=0;p=p->PARENT);
    noeud *q=p->GAUCHE; //la racine
    while(q!=nullptr)
        if(q->CONTENU->first < a_preceder){
            p=q;
            q=q->DROITE;
        }
        else
            q=q->GAUCHE;
    assert(p->DROITE!=p);
    //cette fonction plante
    //si on recule du debut
}


///////////////////////////////////////////////////////////////////////////
// equilibretransferer_vers_la_droite


template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::transferer_vers_la_droite(noeud*& p){
    std::cout << "transferer_vers_la_droite : " << p->CONTENU->first << std::endl; 
    if (p->DROITE != nullptr) {
        if (p->GAUCHE->POIDS > (p->DROITE->POIDS*3)) {
            rotation_gauche_droite(p);
        }
    } else {
        if (p->GAUCHE->POIDS > 3) {
            rotation_gauche_droite(p);
        }
    }
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::transferer_vers_la_gauche(noeud*& p){
    if (p->GAUCHE != nullptr) {
        if (p->DROITE->POIDS > (p->GAUCHE->POIDS*3)) {
            rotation_droite_gauche(p);
        }
    } else {
        if (p->DROITE->POIDS > 3) {
            rotation_droite_gauche(p);
        }
    }
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::rotation_gauche_droite(noeud*& p){
    // CAN'T ROTATE IF THE LEFT->RIGHT >= (LEFT->LEFT*2)-1  ------- DJDUBE : CHECK IF IT'S RIGHT!!!!!!!!
    if (p->GAUCHE->DROITE != nullptr 
        && p->GAUCHE->GAUCHE != nullptr 
        && p->GAUCHE->DROITE->POIDS >= ((p->GAUCHE->GAUCHE->POIDS*2))) {
        rotation_droite_gauche(p->GAUCHE);
    }
    noeud *temp = p;
    p = p->GAUCHE;
    temp->GAUCHE = p->DROITE;
    p->DROITE = temp;

    balancer_poids(p);
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::rotation_droite_gauche(noeud*& p){
    // CAN'T ROTATE IF THE RIGHT->LEFT >= (RIGHT->RIGHT*2)-1  ------- DJDUBE : CHECK IF IT'S RIGHT!!!!!!!!
    if (p->DROITE->GAUCHE != nullptr 
        && p->DROITE->DROITE != nullptr 
        && p->DROITE->GAUCHE->POIDS >= ((p->DROITE->DROITE->POIDS*2))) {
        rotation_gauche_droite(p->DROITE);
    }
    noeud *temp = p;
    p = p->DROITE;
    temp->DROITE = p->GAUCHE;
    p->GAUCHE = temp;
    
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
