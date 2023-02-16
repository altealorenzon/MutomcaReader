/*
 * Project: MutomcaReader
 * File:    Configuration.cpp
 * Author:  Altea Lorenzon < altea.lorenzon@pd.infn.it >
 *
 * Created on February 16, 2023
 */

#include "Configuration.h"

//_________________________________________________________________________________________
Configuration::Configuration(std::string configFileName, Parameters &p) {
    init(configFileName,p);
    print(p);
}

//_________________________________________________________________________________________
Configuration::~Configuration() {

}

//_________________________________________________________________________________________
void Configuration::init(std::string configFileName, Parameters &p) {
    std::string line, dummy;
    std::ifstream myfile (configFileName.c_str());
    if(myfile.is_open()) {
        size_t found;
        while(getline(myfile,line)) {
            if(line.find("#")!=std::string::npos) continue; //skipping comment lines

            found=line.find("rawDirName");
            if(found!=std::string::npos) { std::istringstream iss(line); iss >> dummy >> p.rawDirName; }

            found=line.find("rawFileNameTubes_1");
            if(found!=std::string::npos) { std::istringstream iss(line); iss >> dummy >> p.rawFileNameTubes_1; }

            found=line.find("rawFileNamePhi_3");
            if(found!=std::string::npos) { std::istringstream iss(line); iss >> dummy >> p.rawFileNamePhi_3; }

            found=line.find("rawFileNameTubes_2");
            if(found!=std::string::npos) { std::istringstream iss(line); iss >> dummy >> p.rawFileNameTubes_2; }

            found=line.find("rawFileNamePhi_4");
            if(found!=std::string::npos) { std::istringstream iss(line); iss >> dummy >> p.rawFileNamePhi_4; }

            found=line.find("maxEventNumber");
            if(found!=std::string::npos) { std::istringstream iss(line); iss >> dummy >> p.maxEventNumber; }

            found=line.find("debug");
            if(found!=std::string::npos) { std::istringstream iss(line); iss >> dummy >> p.debug; }
        }
        myfile.close();
    } else {
        std::cout << "The configuration file " << configFileName << " does not exist!" << std::endl;
        exit(-1);
    }
    return;
}

//_________________________________________________________________________________________
void Configuration::print(Parameters &p) {
    std::cout << "\n=========================================================" << std::endl;
    std::cout << "***                  CONFIG FILE READING              ***" << std::endl;
    std::cout << "=========================================================" << std::endl;
    std::cout << "Requested number of events : " << p.maxEventNumber << std::endl;
    std::cout << "*** MODULE 0" << std::endl;
    std::cout << "Input file Tubes :" << "\t" << p.rawDirName << "/" << p.rawFileNameTubes_1 << std::endl;
    std::cout << "Input file Phi   :" << "\t" << p.rawDirName << "/" << p.rawFileNamePhi_3  << std::endl;
    std::cout << "*** MODULE 1" << std::endl;
    std::cout << "Input file Tubes :" << "\t" << p.rawDirName << "/" << p.rawFileNameTubes_2 << std::endl;
    std::cout << "Input file Phi   :" << "\t" << p.rawDirName << "/" << p.rawFileNamePhi_4  << std::endl;
    std::cout << "\n -> Running with debug flag activated." << std::endl;

    return;
}
