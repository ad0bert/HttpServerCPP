/**
 * Name        : configParser.cpp
 * Author      : Peter Ortner
 * Version     : 1.0
 * Date        : 23.03.2015
 * Copyright   : Free to share
 * Description : Can read key/value pairs from a file
 *               Format: key=value
 */
 
#include <iostream>
#include <fstream>
#include <string>

#include <cstring> // for strtok

#include "configParser.h"

ConfigParser::ConfigParser(std::string fileName) : mFileName(fileName){
  parseFile();
}

ConfigParser::~ConfigParser(){}

void ConfigParser::parseFile(){
  std::string key;
  std::string value;
  std::string currLine;
  
  const char delimeter[2] = "=";
  char* currPart;
  
  std::ifstream configFile; 
  configFile.open(mFileName.c_str());
  while(configFile.good()){
    getline(configFile, currLine);
    if (currLine == "")
      continue;
    
    // get duplicate for strtok
    currPart = strdup(currLine.c_str());
    if((currPart = strtok(currPart, delimeter)) == 0) continue;
    key.append(currPart);
    
    if((currPart = strtok(NULL, delimeter)) == 0){ key = ""; continue;}
    value.append(currPart);
    
    mConfigMap[key] = value;
    key = "";
    value = "";
  }
  configFile.close();  
}

std::string ConfigParser::getParameter(std::string key){
  return mConfigMap[key];
}
