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

//_________________________________________________________________________________________
void HitCollection::keepFirstHit(int nBoard, int nLayer, int nCell) {
    /// Keep only the first hit in each tube
    if(_debug) {
        std::cout << "\n******* HitCollection::keepFirstHit *******" <<std::endl;
        std::cout << " * Initial hit collection size : " << _hits.size() << std::endl;
    }
    /// Define array to find equal channels
    int hitNum[nBoard][nLayer][nCell];
    /// Init array to find equal channels
    for(int iBoard=0; iBoard<nBoard; ++iBoard) {
        for(int iLayer=0; iLayer<nLayer; ++iLayer) {
            for(int iCell=0; iCell<nCell; ++iCell) {
                hitNum[iBoard][iLayer][iCell] = -1;
            }
        }
    }
    /// Define vector to store indices of hits to be erased
    std::vector<int> index;
    for(int iHit=0; iHit<_hits.size(); ++iHit){
        Hit* hit = _hits.at(iHit);
        int b = hit->getBoardID();
        int l = hit->getLayID();
        int c = hit->getCellID();
        float dt = hit->getRawTime();

        if(hitNum[b][l][c] == -1) {
            hitNum[b][l][c] = iHit;
        }
        else{
            Hit* hitRep = _hits.at(hitNum[b][l][c]); //previous hit
            if(hitRep->getRawTime() < dt) {
                index.push_back(iHit);
            }
            else {
                index.push_back(hitNum[b][l][c]);
            }
        }
    }// end hit loop

    /// Erasing hits
    std::sort(index.rbegin(),index.rend());
    for(int i=0; i<index.size(); ++i) {
        this->eraseHit(index.at(i));
    }

    if(_debug){
        std::cout << "* Keeping 1 hit with smaller drift time in each cell -> new hit collection size : " << _hits.size() << std::endl;
        this->printCollection();
    }

    return;
}
