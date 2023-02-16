/*
 * Project: MutomcaReader
 * File:    HitCollection.cpp
 * Author:  Altea Lorenzon < altea.lorenzon@pd.infn.it >
 *
 * Created on February 16, 2023
 */

#include "HitCollection.h"

//_________________________________________________________________________________________
HitCollection::HitCollection(bool debug) {
    _debug = debug;
}

//_________________________________________________________________________________________
HitCollection::~HitCollection() {

}

//_________________________________________________________________________________________
void HitCollection::addHit(Hit* hit) {
    _hits.push_back(hit);
    return;
}

//_________________________________________________________________________________________
void HitCollection::eraseHit(int index) {
    /// Erase hit with a given index
    std::vector<Hit*>::iterator it = _hits.begin();
    _hits.erase(it+index);
    return;
}

//_________________________________________________________________________________________
Hit* HitCollection::getHit(int index) {
    return _hits.at(index);
}

//_________________________________________________________________________________________
int HitCollection::hitSize() {
    /// Return number of hits in the collection
    return _hits.size();
}

//_________________________________________________________________________________________
void HitCollection::setDetID(int detID) {
    _detID = detID;
    return;
}

//_________________________________________________________________________________________
int HitCollection::getDetID() {
    return _detID;
}
