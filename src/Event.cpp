/*
 * Project: MutomcaReader
 * File:    Event.cpp
 * Author:  Altea Lorenzon < altea.lorenzon@pd.infn.it >
 *
 * Created on February 16, 2023
 */

#include "Event.h"

//_________________________________________________________________________________________
Event::Event(int detNumber) {
    _detNumber = detNumber;
    /// Init vector for hitCollections
    for(int iColl=0; iColl<_detNumber; ++iColl) {
        _hitColl.push_back(0);
    }
}

//_________________________________________________________________________________________
Event::~Event() {

}

//_________________________________________________________________________________________
void Event::setEventID(long eventID) {
    _eventID = eventID;
    return;
}

//_________________________________________________________________________________________
void Event::setTriggerTime(long triggerTime) {
    _triggerTime = triggerTime;
    return;
}

//_________________________________________________________________________________________
void Event::addCollection(HitCollection* hitColl, int index) {
    _hitColl.at(index) = hitColl;
    return;
}

//_________________________________________________________________________________________
long Event::getEventID() {
    return _eventID;
}

//_________________________________________________________________________________________
int Event::getDetNumber() {
    return _detNumber;
}

//_________________________________________________________________________________________
HitCollection* Event::getCollection(int index) {
    return _hitColl.at(index);
}
