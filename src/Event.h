/*
 * Project: MutomcaReader
 * File:    Event.h
 * Author:  Altea Lorenzon < altea.lorenzon@pd.infn.it >
 *
 * Created on February 16, 2023
 */

#ifndef EVENT_H
#define EVENT_H

#include <vector>
#include <string>
#include <limits>
#include <cmath>
#include "HitCollection.h"
#include "Hit.h"

class Event {
public:
    Event(int detNumber);
    ~Event();

    void setEventID(long eventID);
    void setTriggerTime(long triggerTime);
    void addCollection(HitCollection* hitColl, int index);

    long getEventID();
    int getDetNumber();
    HitCollection* getCollection(int index);

private:
    int _detNumber;
    long _eventID;
    long _triggerTime;
    float _t0[2];
    std::vector<HitCollection*> _hitColl;

};

#endif
