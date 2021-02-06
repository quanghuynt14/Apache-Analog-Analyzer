#if ! defined ( REQUEST_H )
#define REQUEST_H

#include <string>
using namespace std;

typedef struct Time{
    int day;
    string month;
    int year;
    int hour;
    int minute;
    int second;
    int offset;
} Time;

class Request
{

public:
    Request(const string &readLine);
    virtual ~Request();

    inline string GetRequestURL() const { return requestURL; };

    inline string GetRefererURL() const { return refererURL; };

    inline int GetStatusCode() const { return statusCode; };

    friend ostream& operator<<(ostream& os, const Request& request);

protected:
//----------------------------------------------------- Attributs protégés

    string addressIP;
    string userLogName;
    string authenticatedUser;
    Time timeOfRequest;
    string requestType;
    string requestURL;
    string protocol;
    int statusCode;
    string transferDataSize;
    string refererURL;
    string browserClient;
};

#endif // REQUEST_H
