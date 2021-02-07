/*************************************************************************
                           Graph  -  description
                             -------------------
    début                : 20/01/2020
    copyright            : (C) 2021 par Francine Jin et Tran Quang Huy
    e-mail               : jinfrancine@hotmail.com
*************************************************************************/

//---------- Interface de la classe <Graph> (fichier Graph.h) ----------------
#if ! defined ( GRAPH_H )
#define GRAPH_H

//------------------------------------------------------------------------
// Rôle de la classe <Graph>
// Générer les fichiers .dot et afficher le top 10 des hits du  
// apache log sur la sortie standard.
//------------------------------------------------------------------------
class Graph
{
//----------------------------------------------------------------- PUBLIC

public:
//-------------------------------------------- Constructeurs - destructeur

    Graph();
    virtual ~Graph();

//----------------------------------------------------- Méthodes publiques

    void AddNode(const string &node);
    /*
        Contrat : 
    */

    void Top10NodeHits();
    /*
        Contrat : 
    */

    void AddEdge(const string &nodeA, const string &nodeB);
    /*
        Contrat : 
    */

    void CreateDotFile(const string &fileName);
    /*
        Contrat : 
    */

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    map<string,int> nodes;
    map<pair<string,string>,int> edges;
};

#endif // GRAPH_H