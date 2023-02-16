/*
 * Project: MutomcaReader
 * File:    Map.cpp
 * Author:  Altea Lorenzon < altea.lorenzon@pd.infn.it >
 *
 * Created on February 16, 2023
 */

#include "Map.h"

//_________________________________________________________________________________________
Map::Map() {
    _chmap.clear();
}

//_________________________________________________________________________________________
Map::~Map() {

}

//_________________________________________________________________________________________
void Map::fillChannelMap(std::string chMapName) {

    /// Open file with channel map and fill unordered map
    std::ifstream file;
    file.open(chMapName);
	if (!file.is_open()) {
		std::cout << "ERROR : no channel map file found - exiting ! " << std::endl;
		exit(-1);
	}

    int brd_id;
	int ch_id;
	int lay;
	int ch;

	while( file >> brd_id >> ch_id >> lay >> ch ) {
        /// Map with normal key-value
        int idTDC = this->getTDCid(brd_id, ch_id);
    	int idTube = this->getTUBEid(lay, ch);
        _chmap.insert(std::make_pair(idTDC, idTube));
	}
	return;
}

//_________________________________________________________________________________________
bool Map::findChannel(int par1, int par2) {

    bool found;
    /// Find channel in map
    auto iter = _chmap.find(this->getTDCid(par1, par2));
    if(iter == _chmap.end()) {
        found = false;
        _foundLayer = -1;
        _foundTube = -1;
    }
    else {
        found = true;
        _foundLayer = this->getLayer(iter->second);
        _foundTube  = this->getTube(iter->second);
    }

    return found;
}

//_________________________________________________________________________________________
int Map::getBoardFound() {
    return _foundBoard;
}

//_________________________________________________________________________________________
int Map::getChFound() {
    return _foundCh;
}

//_________________________________________________________________________________________
int Map::getLayerFound() {
    return _foundLayer;
}

//_________________________________________________________________________________________
int Map::getTubeFound() {
    return _foundTube;
}

//_________________________________________________________________________________________
int Map::getTDCid(int board, int ch) {
	return board*1000+ch;
}

//_________________________________________________________________________________________
int Map::getTUBEid(int layer, int tube) {
	return layer*100+tube;
}

//_________________________________________________________________________________________
int Map::getBoard(int idTDC) {
	return (int)idTDC/1000;
}

//_________________________________________________________________________________________
int Map::getCh(int idTDC) {
    int board = (int)idTDC/1000;
    return (idTDC-board*1000);
}

//_________________________________________________________________________________________
int Map::getLayer(int idTube) {
	return (int)idTube/100;
}

//_________________________________________________________________________________________
int Map::getTube(int idTube) {
    int layer = (int)idTube/100;
    return (idTube-layer*100);
}
