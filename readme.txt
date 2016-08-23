##########################################################
#################### HTTP-Simple-Server ##################
##########################################################
Assignment for NDS

Implemented with C-Sockets and C++11
To compile:
g++ -o httpServer main.cpp httpHeader.cpp httpRequest.cpp configParser/configParser.cpp -std=c++11

or use the makefile

port and root folder for html sites can be set in the config.txt
standard port in the file is 5050
all supported mime types can be found in mimeConfig.txt

supports HTML GET requests
Status 200 and 400 // we have a MAP with all codes but do not support more atm
