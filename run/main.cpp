#include <iostream>

#include "../src/Parameters.h"
#include "../src/Configuration.h"
#include "../src/Map.h"
#include "../src/Reader.h"
#include "../src/HitCollection.h"
#include "../src/Hit.h"

int main() {

    Parameters p;

    Configuration* cfg = new Configuration("config.ini",p);

    ////////////////////////////////////////////////////////////////////////////
    /// CHANNEL MAPS
    ////////////////////////////////////////////////////////////////////////////
    // Init Channel Maps
    Map* mapDet= new Map();
    mapDet->fillChannelMap("../utils/ChannelMapTubes.txt");
    Map* mapSL = new Map();
    mapSL->fillChannelMap("../utils/ChannelMapSL.txt");

    ////////////////////////////////////////////////////////////////////////////
    /// EVENT READING
    ////////////////////////////////////////////////////////////////////////////
    std::cout << "\n\n\n=========================================================" << std::endl;
    std::cout << "***                  EVENT READING                    ***" << std::endl;
    std::cout << "=========================================================" << std::endl;
    Reader* rdr = new Reader(p.debug, p.maxEventNumber);

    /// Find first event number of both detectors
    std::vector<std::string> infileName;
    infileName.push_back(p.rawDirName+'/'+p.rawFileNameTubes_1);
    infileName.push_back(p.rawDirName+'/'+p.rawFileNamePhi_3);
    infileName.push_back(p.rawDirName+'/'+p.rawFileNameTubes_2);
    infileName.push_back(p.rawDirName+'/'+p.rawFileNamePhi_4);

    rdr->findFirstEvNumber(infileName);

    /// Loop over input files
    for(int iDet=0; iDet<infileName.size(); ++iDet) {
        /// Fill Channel Map
        if(iDet%2==0) rdr->setChannelMap(mapDet);
        else rdr->setChannelMap(mapSL);
        /// Read Events
        rdr->readEvents(infileName.at(iDet),iDet);
    }

    if(p.debug) rdr->printSummary();

    ////////////////////////////////////////////////////////////////////////////
    /// ANALYSIS
    ////////////////////////////////////////////////////////////////////////////
    std::cout << "\n\n\n=========================================================" << std::endl;
    std::cout << "***                    ANALYSIS                       ***" << std::endl;
    std::cout << "=========================================================" << std::endl;
    /// Loop over events
    for(int iEv = 0; iEv < p.maxEventNumber; ++iEv) {

        Event* ev = rdr->getEvent(iEv);
        if(!ev) continue;

        std::cout << "\n\n---------------------------------------------------------" << std::endl;
        std::cout << " --- Processing event " << ev->getEventID() << std::endl;

        /// Loop over detectors
        for(int iDet=0; iDet<infileName.size(); ++iDet) {

            /// Get hit collection
            HitCollection* hitColl = ev->getCollection(iDet);
            if(!hitColl) continue;

            std::cout << "---------------------------------------------------------" << std::endl;
            std::cout << " --- Det " << hitColl->getDetID();
            if(iDet%2==0) std::cout << " ---> DT " << int(iDet/2) << std::endl;
            if(iDet%2==1) std::cout << " ---> SL " << int(iDet/2) << std::endl;
            std::cout << " ------ HitCollection of size " << hitColl->hitSize() << std::endl;

            /// Loop over hits and print info
            for(int iHit=0; iHit<hitColl->hitSize(); ++iHit) {
                Hit* hit = hitColl->getHit(iHit);
                std::cout << " --------- Hit " << iHit
                          << " Board " <<  hit->getBoardID()
                          << " Channel " << hit->getChID()
                          << " Lay " << hit->getLayID()
                          << " Cell " << hit->getCellID()
                          << " RawTime "  << hit->getRawTime() << std::endl;
            } // end loop on hits
        } // end loop on detectors
    } // end loop on events
    return 0;
}
