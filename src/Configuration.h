/*
 * Project: MutomcaReader
 * File:    Configuration.h
 * Author:  Altea Lorenzon < altea.lorenzon@pd.infn.it >
 *
 * Created on February 16, 2023
 */

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <iostream>
#include <fstream>
#include <sstream>

#include "Parameters.h"

 class Configuration {

 public:
     Configuration(std::string configFileName, Parameters &p);
     ~Configuration();

 private:
     void init(std::string configFileName, Parameters &p);
     void print(Parameters &p);
 };

 #endif
