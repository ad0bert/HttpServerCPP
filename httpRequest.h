/**
 * Name        : httpRequest.cpp
 * Author      : Peter Ortner
 * Version     : 1.0
 * Date        : 06.06.2016
 * Copyright   : Free to share
 * Description : Header for httpRequest.cpp
 */
#ifndef _HTTP_REQUEST_H
#define _HTTP_REQUEST_H

#include <iostream>

class httpRequest{
  static const int MAX_REQUEST_LEN = 2048;
  std::string mRootPath = "";
  
  public:
    httpRequest();
    int handleRequest(int sock);
    void setRootPath(std::string rootPath);
};

#endif // _HTTP_REQUEST_H
