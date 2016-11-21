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
    //STUB O(n log n) a remplacer par une fonction O(log n)
    iterator i;
    for(i=begin();i!=end();++i)
        if(!(i->first < c))break;
    return i;
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
    std::cout << "transferer_vers_la_droite" << std::endl;
    noeud *parent = p->PARENT;
    if (parent != nullptr && parent->DROITE != nullptr && (p->POIDS*3) > parent->DROITE->POIDS) {
        rotation_gauche_droite(parent);
    }
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::transferer_vers_la_gauche(noeud*& p){
    std::cout << "transferer_vers_la_gauche" << std::endl;
    noeud *parent = p->PARENT;
    if (parent != nullptr && parent->GAUCHE != nullptr && (p->POIDS*3) > parent->GAUCHE->POIDS) {
        rotation_droite_gauche(parent);
    }
}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::rotation_gauche_droite(noeud*& p){
    // WIP
    std::cout << "rotation_gauche_droite" << std::endl;
    noeud *parent = p->PARENT;
    noeud *gauche = p->GAUCHE;
    noeud *temp = p->GAUCHE;
    if (gauche != nullptr && gauche->DROITE != nullptr && gauche->GAUCHE != nullptr) {
        noeud *gaucheGauche = gauche->GAUCHE;
        noeud *gaucheDroite = gauche->DROITE;
        if (gaucheDroite != nullptr && gaucheGauche != nullptr && gaucheDroite > gaucheGauche) {
            rotation_gauche_droite(gauche);
        }
    }


}

template <typename Tclef, typename Tvaleur>
void map<Tclef,Tvaleur>::rotation_droite_gauche(noeud*& p){
    std::cout << "rotation_droite_gauche" << std::endl;
}



#endif /* map2_h */
