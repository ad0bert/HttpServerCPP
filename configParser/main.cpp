/**
 * Name        : main.cpp
 * Author      : Peter Ortner
 * Version     : 1.0
 * Date        : 23.03.2015
 * Copyright   : Free to share
 * Description : Test module for the config parser
 */
#include <iostream>
#include "configParser.h"

int main(){
  ConfigParser *cp = 0;
  try{
    cp = new ConfigParser("config.txt");
    std::cout << "------------------------" << std::endl;
    std::string ip;
    ip = (cp->getParameter("ip") == "") ? "10.17.1.19" : cp->getParameter("ip");
    std::cout << ip << std::endl;
    ip = (cp->getParameter("ip1") == "") ? "10.17.1.20" : cp->getParameter("ip");
    std::cout << ip << std::endl;
  }catch(int e){
    if (e == -1)
      std::cerr << "key failed" << std::endl;
    else
      std::cerr << "value failed" << std::endl;
    return e;
  }
  
  if (cp != 0)
    delete cp;
  
  return 0;
}
