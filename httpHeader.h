/**
 * Name        : httpHeader.h
 * Author      : Peter Ortner
 * Version     : 1.0
 * Date        : 08.06.2016
 * Copyright   : Free to share
 * Description : Header for the httpHeader class
 */
#ifndef _HTTP_HEADER_H
#define _HTTP_HEADER_H

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

class httpHeader{
  std::string mFile;
  
  std::string mHttpVersion;
  std::string mHttpVersionLine;
  unsigned short mStatus;
  std::string mVersion;
  
  std::string mContentType;
  std::string mConnection;
  
  void setStatus(std::string type);
  void setContentType();
  std::string getStatus();
  std::string getDate();
  std::string getETag();
  std::string getLastModified();
  
  std::string mRange;
  struct stat sb;
  
  public:
    httpHeader(std::string file);
    std::string buildHeader();
};

#endif // _HTTP_HEADER_H
