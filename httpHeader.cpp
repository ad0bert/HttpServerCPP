/**
 * Name        : httpHeader.cpp
 * Author      : Peter Ortner
 * Version     : 1.0
 * Date        : 08.06.2016
 * Copyright   : Free to share
 * Description : Builds a httpHeader based on a http request
 */
#include <iostream>
#include <ctime>
#include <chrono>
#include <functional>

// for file information
#include <stdio.h>
#include <stdlib.h>

// string operation for file
#include <string>
#include <sstream>
#include <fstream>

#include "configParser/configParser.h"
#include "httpHeader.h"
#include "httpStatus.h"

// set status header field and http version (zb.: HTTP/1.1 200 OK)
void httpHeader::setStatus(std::string type){
  mHttpVersionLine = mHttpVersion + " " + std::to_string(sl.find(type)->second) + " " + type + "\n";
}

// returns the status header field with http version
std::string httpHeader::getStatus(){
  return mHttpVersionLine;
}

// return current system time
std::string httpHeader::getDate(){
  std::time_t today_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::string server_time(std::ctime(&today_time));
  return "Date: " + server_time;
}

// returns the modified date of an file
std::string httpHeader::getLastModified(){
  std::string file_time(ctime(&sb.st_mtime));
  std::string res = "Last-Modified: "+ file_time;
  return res;
}

// hashs the last modified date to generate an unique ETag
std::string httpHeader::getETag(){
  size_t hash = std::hash<std::string>()(getLastModified());
  std::stringstream ss;
  ss << hash;
  return "ETag: \"" + ss.str() + "\"\n";
}

// ctor set some basic informations
// TODO: read from config
httpHeader::httpHeader(std::string file):mFile(file){
  mHttpVersion = "HTTP/1.1";
  mVersion = "Server: NDS-Server/0.0.1\n";
  mContentType = "Content-Type: text/html\n";
  mConnection = "Connection: close\n";
  mRange = "Accept-Ranges: bytes\n";
}

// get MIME Type for the requested file (Content-Type)
void httpHeader::setContentType(){
  std::string extension = mFile.substr(mFile.find_last_of("."));
  ConfigParser cp("mimeConfig.txt");
  mContentType = "Content-Type: " + cp.getParameter(extension) + "\n";
}

// create header information and content for the http response
std::string httpHeader::buildHeader(){
  std::string content = "\n";
  std::string modDate = "";
  
  
  if (stat(mFile.c_str(), &sb) == -1){
    setStatus("I’m a teapot");
  }
  else{
    // we only support regular files everything else is a "Bad Request"!
    switch (sb.st_mode & S_IFMT) {
      case S_IFBLK:  printf("block device\n");  
        setStatus("Bad Request");          
        break;
      case S_IFCHR:  printf("character device\n");  
        setStatus("Bad Request");      
        break;
      case S_IFDIR:  printf("directory\n");    
        setStatus("Bad Request");           
        break;
      case S_IFIFO:  printf("FIFO/pipe\n"); 
        setStatus("Bad Request");              
        break;
      case S_IFLNK:  printf("symlink\n");   
        setStatus("Bad Request");              
        break;
      case S_IFREG: {
        printf("regular file\n");  
        setStatus("OK");
        std::ifstream f(mFile);
        if (f.good()) {
          std::stringstream buffer;
          buffer << f.rdbuf();
          content += buffer.str();
        } else {
          printf("ERROR open html file");
        }
        setContentType();
        modDate = getLastModified(); 
        break;
      }
      case S_IFSOCK: printf("socket\n");     
        setStatus("Bad Request");             
        break;
      default:       printf("unknown?\n");  
        setStatus("Bad Request");              
        break;
    }
    
  }
  
  return getStatus() + getDate() + mVersion + modDate + 
         getETag() + mContentType + "Content-Length: " + 
         std::to_string(content.length()-1) + "\n" + 
         mRange + mConnection + content;
}

