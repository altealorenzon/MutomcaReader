/*
 * Project: MutomcaReader
 * File:    Reader.cpp
 * Author:  Altea Lorenzon < altea.lorenzon@pd.infn.it >
 *
 * Created on February 16, 2023
 */

#include "Reader.h"
#include <string.h>

//_________________________________________________________________________________________
Reader::Reader(bool debug, int maxEventNumber) {
    /// Setting debug flag
    _debug = debug;
    /// Setting max event number to be read
    _maxEventNumber = maxEventNumber;
    /// Initialize vector of events
    for(int i=0; i<_maxEventNumber; ++i) {
        _events.push_back(0);
    }
    /// Initialize number of detectors
    _detNumber=0;
}

//_________________________________________________________________________________________
Reader::~Reader() {

}

//_________________________________________________________________________________________
void Reader::findFirstEvNumber(std::vector<std::string> infileName) {
	if(_debug){
        std::cout << "\n******* Reader::findFirstEvNumber *******" << std::endl;
    }

    _detNumber = infileName.size();

    /// Initialize useful variables
    _totEvents = new int(_detNumber);
    long firstEvent[_detNumber];

    /// Loop over detectors
    for(int iDet=0; iDet<_detNumber; ++iDet) {
        if(_debug) {
            std::cout << "Reading from file: " << infileName.at(iDet) << std::endl;
        }
        /// Open file
        FILE* file;
        file = fopen(infileName.at(iDet).c_str(), "r");
        if(file == nullptr) {
            std::cout << "ERROR: Unable to open file " << infileName.at(iDet) << std::endl;
            exit(-1);
        }
        else {
            long numEvent = 0;
            firstEvent[iDet] = 0;
            /// Loop over events
            while( numEvent < _maxEventNumber ) {
                RawData rdata = readCastorWord(file);
                if (rdata.error == 1) {
                    /// Reached EOF
                    break;
                } else if (rdata.error > 1) {
                    /// Errors
                    continue;
                } else if (rdata.evn_number >= 0) {
                    /// Header
                    firstEvent[iDet] = rdata.evn_number;
                    ++numEvent;
                    break;
                }
            }
        }
    }

    long minEv = std::numeric_limits<long>::max();
    for(int iDet=0; iDet<_detNumber; ++iDet) {
        if(firstEvent[iDet]<minEv) minEv = firstEvent[iDet];
    }

    _firstEvent = minEv;

    if(_debug) {
        for(int iDet=0; iDet<_detNumber; ++iDet) {
            std::cout << "\n - First event from " << infileName.at(iDet) << " " << firstEvent[iDet] << std::endl;
        }
        std::cout << "\n---> First event number = " << _firstEvent << std::endl;
    }

	return;

}

//_________________________________________________________________________________________
void Reader::setChannelMap(Map* map) {
    _chmap = map;
	return;
}

//_________________________________________________________________________________________
void Reader::readEvents(std::string infileName, int index) {
    if(_debug){
        std::cout << "\n******* Reader::readEvents *******" <<std::endl;
    }

    /// Initialize event object to store data
    Event* ev;

    FILE* file_in;
    file_in = fopen(infileName.c_str(), "r");
    if(file_in == nullptr) {
        std::cout << "Unable to open file " << infileName << std::endl;
        exit(-1);
    } else {
        std::cout << "\nReading from file: " << infileName  << std::endl;
        int newEvent=0;
        int savedEvent=0;
        int nHits=0;
        bool header=false;

        while( newEvent < _maxEventNumber ) {

            RawData rdata = readCastorWord(file_in);

            if (rdata.error == 1) {
                break;
            }
            else if (rdata.error > 1) {
                continue;
            }
            else if (rdata.evn_number >= 0) {
                /******************************************************************************
                close previous event
                ************************************************************************** */
                if(header) {

                    this->fixRollover(ev->getCollection(index));

                    if( ((ev->getEventID() - _firstEvent) < _maxEventNumber) && (nHits != 0)) {
                        if(!_events[ev->getEventID() - _firstEvent]) {
                            _events[ev->getEventID() - _firstEvent] = ev;
                        }
                    	else {
                    	    _events[ev->getEventID() - _firstEvent]->addCollection(ev->getCollection(index),index);
                    	}
                    	++savedEvent;
                    }
                    else if((ev->getEventID() - _firstEvent) >= _maxEventNumber) {
                        std::cout << "!!! Reached end of array to store data -> increase maxEventNumber if you want to read more" << std::endl;
                        break;
                    }
                    header=false;
                }
                /******************************************************************************
                initialize new event
                ************************************************************************** */
                ev = new Event(_detNumber);
                ev->addCollection(new HitCollection(_debug),index);
                ev->getCollection(index)->setDetID(index);
                newEvent++;

                header=true;
                nHits=0;

                ev->setEventID(rdata.evn_number);
            }
            else if(rdata.trg_time >= 0) {
                if(header) {
                    ev->setTriggerTime(rdata.trg_time);
                }
            }
            else {
                /******************************************************************************
                hits
                ************************************************************************** */
                if(!header) {
                    std::cout << "Discarded hit: missing header" << std::endl;
                    continue;
                }

                bool found = _chmap->findChannel(rdata.brd_id, rdata.channel);
                if(!found) {
                    std::cout << "Channel not found! "<< rdata.brd_id << " " <<  rdata.channel << std::endl;
                    continue;
                }
                //filling hit info
                Hit* hit = new Hit();
                hit->setBoardID(rdata.brd_id);
                hit->setChID(rdata.channel);
                int layer = _chmap->getLayerFound();
                hit->setLayID( layer );
                int tube = _chmap->getTubeFound();
                hit->setCellID( (index%2==0 && rdata.brd_id<3) ? 30-tube-layer%2 : tube );
                hit->setRawTime( rdata.time );

                /// Add hits to hit collections
                if((index%2==0 && hit->getBoardID()<6 && hit->getLayID()<6 && hit->getCellID() < 31) ||
                    (index%2==1 && hit->getBoardID()<5 && hit->getLayID()<5 && hit->getCellID() < 73)   ) {
                    ev->getCollection(index)->addHit(hit);
                    nHits++;
                }
                else {
                    std::cout << "ERROR Det " << index << std::endl;
                    std::cout << "Board ID " << hit->getBoardID() << std::endl;
                    std::cout << "Layer ID " << hit->getLayID() << std::endl;
                    std::cout << "Tube ID " << hit->getCellID() << std::endl;
                }
            }
        } // end loop on entries

        _totEvents[index] = savedEvent;

        std::cout << "\n*** Number of events read from file " << index << " " << infileName << " = " << newEvent << std::endl;
        std::cout << "*** Number of events with hits in file " << index << " " << infileName << " = " << savedEvent << std::endl;

    }

	return;
}

//_________________________________________________________________________________________
void Reader::fixRollover(HitCollection* hitColl) {
    bool isRollover = false;
    HitQueue hitsQueue;
    Hit* previousHit = nullptr;
    if(hitColl) {
        /// Fill the queue
        for(int iHit=0; iHit<hitColl->hitSize(); ++iHit) {
            hitsQueue.push(hitColl->getHit(iHit));
        }
        /// Loop on the queue elements
        while(!hitsQueue.empty()) {
            /// Get the top hit and then remove it from queue
            Hit* currentHit = hitsQueue.top();
            hitsQueue.pop();
            /// Check the difference in time with the previous hit in memory
            if(previousHit!=nullptr && (previousHit->getRawTime()-currentHit->getRawTime() > 65536/2)) {
                isRollover=true;
            }
            /// If the rollover condition is satisfied, change the hit raw time
            if(isRollover) {
                if(_debug) {
                    std::cout << "Fix Rollover for hit of board " << currentHit->getBoardID()
                              << " layer " << currentHit->getLayID()
                              << " tube " << currentHit->getCellID()
                              << ": RawTime " << currentHit->getRawTime() << " is set to " << currentHit->getRawTime()+65536 << std::endl;
                }
                currentHit->setRawTime(currentHit->getRawTime()+65536);
            }
            previousHit = currentHit;
        } // end loop on queue elements
    } // end if

    return;
}

//_________________________________________________________________________________________
RawData Reader::readCastorWord(FILE* infile) {

	RawData result;

	long eword = 0x00000000;

	if (fread(&eword, 4, 1, infile) == 0) {
		// end of file
		result.error = 1;
		return result;
	}

	long code = eword & 0xE0000000;

	if (code == 0x00000000) {
		/// payload
		result.brd_id = (eword & 0x07C00000) >> 22;
		result.channel = (eword & 0x003F0000) >> 16;
		result.time = eword & 0x0000FFFF;
	}
    else if (code == 0x60000000) {
        /// trigger time
        result.trg_time = eword & 0x0000FFFF;
    }
    else if (code == 0x20000000) {
		/// header
		result.evn_number = eword & 0x1FFFFFFF;
	}
    else if (code == 0xE0000000) {
		/// no operation
		result.error = 2;
	}
    else {
		/// malformed word (recoverable error)
		result.error = 3;
	}

	return result;
}

//_________________________________________________________________________________________
void Reader::printSummary() {
	std::cout << "\n\n\n=========================================================" << std::endl;
	std::cout << "***                  EVENTS READ                      ***" << std::endl;
    std::cout << "=========================================================" << std::endl;

    for(int iDet=0; iDet<_detNumber; ++iDet) {
        std::cout << "Total Number of Events read from file: " << iDet << " = " << _totEvents[iDet] << std::endl;
    }

	return;
}

//_________________________________________________________________________________________
Event* Reader::getEvent(int iEvent) {
    return _events.at(iEvent);
}
