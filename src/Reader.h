/*
 * Project: MutomcaReader
 * File:    Reader.h
 * Author:  Altea Lorenzon < altea.lorenzon@pd.infn.it >
 *
 * Created on February 16, 2023
 */

#ifndef READER_H
#define READER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include "Map.h"
#include "Event.h"
#include "HitCollection.h"
#include "Hit.h"

//_________________________________________________________________________________________
struct RawData{
    RawData() : evn_number(-1), trg_time(-1), brd_id(0), channel(0), time(0), error(0) {};
    long evn_number;
    long trg_time;
    long brd_id;
    long channel;
    long time;
    int error;
};

//_________________________________________________________________________________________
class CmpHitTime
{
public:
    CmpHitTime() {}
    bool operator()(Hit* &alfa, Hit* &beta) {
        /// Hits are arranged with raw times in descending order
        return alfa->getRawTime() < beta->getRawTime();
    }
};

using HitQueue = std::priority_queue<Hit*, std::vector<Hit*>, CmpHitTime>;

//_________________________________________________________________________________________
class Reader {
public:
    Reader(bool debug, int maxEventNumber);
    ~Reader();

    void findFirstEvNumber(std::vector<std::string> infileName);
    void setChannelMap(Map* map);
    void readEvents(std::string infileName, int index);
    void printSummary();
    Event* getEvent(int iEvent);

private:
    RawData readCastorWord(FILE* infile);
    void fixRollover(HitCollection* hits);
    bool _debug;
    int _maxEventNumber;
    int _detNumber;
    Map* _chmap;
    std::vector<Event*> _events;
    long _firstEvent;
    int* _totEvents;

};

#endif
