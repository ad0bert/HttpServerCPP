/**
 * Name        : main.cpp
 * Author      : Peter Ortner
 * Version     : 1.0
 * Date        : 06.06.2016
 * Copyright   : Free to share
 * Description : Main module for creating a http server
 *               port binding and forking and error management
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>

// include parser for our config file
#include "configParser/configParser.h"
#include "httpRequest.h"

// modul global for easy memory management
static httpRequest *hr = new httpRequest();
static ConfigParser *cp = new ConfigParser("config.txt");

// handle child signals to avoid zomibies
void handler(int sig){
  pid_t pid;
  pid = wait(NULL);
  printf("Pid %d exited.\n", pid);
}

// in case of an error free our resources and exit with an error
void handleError(int error, const char* msg){
  delete hr;
  delete cp;
  perror(msg);
  exit(error);
}

// main method
int main(int argc, char *argv[])
{
  int sockfd, newsockfd, portno, pid, error = 0;
  // grap root path to our html sites
  std::string rootPath = cp->getParameter("rootPath");
  hr->setRootPath(rootPath);
  
  socklen_t clilen;
  struct sockaddr_in serv_addr, cli_addr;
  
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  
  if (sockfd < 0) 
    handleError(sockfd, "ERROR opening socket");
    
  bzero((char *) &serv_addr, sizeof(serv_addr));
  // grap port number from config
  portno = atoi(cp->getParameter("port").c_str());

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);
  
  printf("Starting server listen on port: %d\n root directory points to: %s\n",
  portno, rootPath.c_str());
  
  // bind socket
  if ((error = bind(sockfd, (struct sockaddr *) &serv_addr,
          sizeof(serv_addr))) < 0) 
          handleError(error, "ERROR on binding");
  listen(sockfd,5);
  clilen = sizeof(cli_addr);
  
  // set signal handler
  signal(SIGCHLD, handler);
 
  // wait for connections
  while (1) {
     newsockfd = accept(sockfd, 
           (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0) 
         handleError(newsockfd, "ERROR on accept");
         
        
     pid = fork();
     if (pid < 0)
         handleError(pid, "ERROR on fork");

     if (pid == 0)  {
         close(sockfd);
         // handle incomming requests
         error = hr->handleRequest(newsockfd);
         if (error < 0)
            handleError(error, "ERROR on handleRequest");
         exit(0);
     }
     else close(newsockfd);
  }
  
  // we never come here but just in case
  close(sockfd);
  delete hr;
  delete cp;
  return 0; 
}
