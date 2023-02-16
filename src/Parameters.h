/*
 * Project: MutomcaReader
 * File:    Parameters.h
 * Author:  Altea Lorenzon < altea.lorenzon@pd.infn.it >
 *
 * Created on February 16, 2023
 */

#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <string>

struct Parameters {
    /// Input files
    std::string rawDirName;             // Path of directory of input files
    std::string rawFileNameTubes_1;     // Name of the input file for DET 0 (file 1_)
    std::string rawFileNamePhi_3;       // Name of the input file for  SL 0 (file 3_)
    std::string rawFileNameTubes_2;     // Name of the input file for DET 1 (file 2_)
    std::string rawFileNamePhi_4;       // Name of the input file for  SL 1 (file 4_)
    int maxEventNumber;                 // Maximum number of events to be read
    /// Debugging
    bool debug;

};

#endif
