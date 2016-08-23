/**
 * Name        : configParser.h
 * Author      : Peter Ortner
 * Version     : 1.0
 * Date        : 23.03.2015
 * Copyright   : Free to share
 * Description : Header definition for the configParser.cpp
 */
 
#ifndef _CONFIG_PARSER_H
#define _CONFIG_PARSER_H

#include <iostream>
#include <map>

typedef std::map<std::string, std::string> configMap;

class ConfigParser{
  std::string mFileName;
  configMap mConfigMap;
  void parseFile();
public:
  ConfigParser(std::string fileName);
  ~ConfigParser();
  std::string getParameter(std::string name);  
};


#endif // _CONFIG_PARSER_H
