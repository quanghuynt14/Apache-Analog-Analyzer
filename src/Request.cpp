#include <sstream>
#include <iostream>
using namespace std;

#include "Request.h"

Request::Request(const string &readLine) {
    istringstream iss(readLine);
    iss >> addressIP;
    iss >> userLogName;
    iss >> authenticatedUser;

    string x;
    getline(iss, x, '[');
    getline(iss, x, '/');
    timeOfRequest.day = stoi(x);
    getline(iss, timeOfRequest.month, '/');
    getline(iss, x, ':');
    timeOfRequest.year = stoi(x);
    getline(iss, x, ':');
    timeOfRequest.hour = stoi(x);
    getline(iss, x, ':');
    timeOfRequest.minute = stoi(x);
    getline(iss, x, ' ');
    timeOfRequest.second = stoi(x);
    getline(iss, x, ']');
    timeOfRequest.offset = stoi(x);

    getline(iss, x, '"');
    iss >> requestType;
    
    int firstPosition = readLine.find(requestType + " ") + requestType.size() + 1;
    int lastPosition = readLine.find("HTTP");
    requestURL = readLine.substr(firstPosition, lastPosition-firstPosition-1);
    
    iss.seekg(readLine.find(requestURL) + requestURL.size()+1);
    getline(iss, protocol, '"');
    
    iss >> statusCode;
    iss >> transferDataSize;

    string base_url = "http://intranet-if.insa-lyon.fr";
    if (readLine.find(base_url) != string::npos) {
        iss.seekg(readLine.find(base_url) + base_url.size());
    } else {
        getline(iss, x, '"');
    }
    getline(iss, refererURL, '"');

    getline(iss, x, '"');
    getline(iss, browserClient, '"');
}

Request::~Request()
{

}

ostream& operator<<(ostream& os, const Request& request)
{
    os << request.addressIP << " ";
    os << request.userLogName << " ";
    os << request.authenticatedUser << " ";
    os << "[" << request.timeOfRequest.day << "/";
    os << request.timeOfRequest.month << "/";
    os << request.timeOfRequest.year << ":";
    os << request.timeOfRequest.hour << ":";
    os << request.timeOfRequest.minute << ":";
    os << request.timeOfRequest.second << " ";
    os << request.timeOfRequest.offset << "] ";
    os << request.requestType << " ";
    os << request.requestURL << " ";
    os << request.protocol << " ";
    os << request.statusCode << " ";
    os << request.transferDataSize << " ";
    os << request.refererURL << " ";
    os << request.browserClient << endl;
    return os;
}//--------Fin de la surchage de l'operateur <<