httpServer: main.cpp httpHeader.cpp httpRequest.cpp configParser/configParser.cpp
	g++ -o httpServer main.cpp httpHeader.cpp httpRequest.cpp configParser/configParser.cpp -std=c++11