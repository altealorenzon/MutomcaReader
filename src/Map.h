/*
 * Project: MutomcaReader
 * File:    Map.h
 * Author:  Altea Lorenzon < altea.lorenzon@pd.infn.it >
 *
 * Created on February 16, 2023
 */

#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

class Map {

public:
    Map();
    ~Map();

    void fillChannelMap(std::string chMapName);
    bool findChannel(int par1, int par2);
    int getBoardFound();
    int getChFound();
    int getLayerFound();
    int getTubeFound();

private:
    int getTDCid(int board, int ch);
    int getTUBEid(int layer, int tube);
    int getBoard(int idTDC);
    int getCh(int idTDC);
    int getLayer(int idTube);
    int getTube(int idTube);
    std::unordered_map<int, int> _chmap;
    int _foundBoard;
    int _foundCh;
    int _foundLayer;
    int _foundTube;
};

#endif
