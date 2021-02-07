/*************************************************************************
                           Request  -  description
                             -------------------
    début                : 20/01/2020
    copyright            : (C) 2021 par Francine Jin et Tran Quang Huy
    e-mail               : jinfrancine@hotmail.com
*************************************************************************/

//---------- Interface de la classe <Request> (fichier Request.h) ----------------
#if ! defined ( REQUEST_H )
#define REQUEST_H

//------------------------------------------------------------------ Types
typedef struct Time{
    int day;
    string month;
    int year;
    int hour;
    int minute;
    int second;
    int offset;
} Time;

//------------------------------------------------------------------------
// Rôle de la classe <Request>
// Contient toutes les informations d'une requête du fichier log.
//
//------------------------------------------------------------------------
class Request
{
//----------------------------------------------------------------- PUBLIC

public:
//-------------------------------------------- Constructeurs - destructeur

    Request(const string &readLine);
    /*
        Mode d'emploi : 
            readLine est la ligne de fichier log contenant les informations d'une requête
        Contrat :
            Récupère les informations de readLine et les stocke dans les attributs de cette classe
    */
    virtual ~Request();

//----------------------------------------------------- Méthodes publiques

    inline string GetRequestURL() const { return requestURL; };
    /*
        Contrat : Renvoie l'URL demandée par la requête
    */

    inline string GetRefererURL() const { return refererURL; };
    /*
        Contrat : Renvoie le referer URL de la requête
    */

    inline int GetStatusCode() const { return statusCode; };
    /*
        Contrat : Renvoie la status code de la requête
    */

//------------------------------------------------- Surcharge d'opérateurs

    friend ostream& operator<<(ostream& os, const Request& request);
    /*
        Contrat : Affichage de la requête dans le flux utilisé
    */

//------------------------------------------------------------------ PRIVE

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
