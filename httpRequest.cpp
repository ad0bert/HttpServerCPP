/**
 * Name        : httpRequest.cpp
 * Author      : Peter Ortner
 * Version     : 1.0
 * Date        : 06.06.2016
 * Copyright   : Free to share
 * Description : Reads the request information (GET,POST, usw) and the
 *               requested source
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "httpHeader.h"
#include "httpRequest.h"

httpRequest::httpRequest(){}

int httpRequest::handleRequest(int sock){
  int n;
  char buffer[MAX_REQUEST_LEN];

  char *request;
  char *resource;

  std::string response, pathToFile;

  bzero(buffer,MAX_REQUEST_LEN);
  
  if ((n = read(sock,buffer,MAX_REQUEST_LEN-1)) < 0) return n;
  request  = strtok (buffer," "); // parse GET POST DELETE usw.
  resource = strtok (NULL, " ");
  
  // get index.html on root request
  if (strcmp(resource, "/") == 0) resource = (char*)"index.html";
  // we just support GET so if anything else we set the path to /dev/null
  if (strcmp(request, "GET") != 0) pathToFile = "/dev/null";
  else pathToFile = mRootPath+resource;
  
  httpHeader *hh = new httpHeader(pathToFile);
  response = hh->buildHeader();
  delete hh;
  return write(sock,response.c_str(),response.length());
}

void httpRequest::setRootPath(std::string rootPath){
  mRootPath = rootPath;
}
