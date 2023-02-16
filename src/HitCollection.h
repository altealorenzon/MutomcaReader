/*
 * Project: MutomcaReader
 * File:    HitCollection.h
 * Author:  Altea Lorenzon < altea.lorenzon@pd.infn.it >
 *
 * Created on February 16, 2023
 */

#ifndef HITCOLLECTION_H
#define HITCOLLECTION_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include "Map.h"
#include "Hit.h"

class HitCollection {

public:
    HitCollection(bool debug);
    ~HitCollection();

    void addHit(Hit* hit);
    void eraseHit(int index);
    Hit* getHit(int index);
    int hitSize();
    void setDetID(int detID);
    int getDetID();

private:
    int _detID;
    std::vector<Hit*> _hits;
    bool _debug;
};

#endif
