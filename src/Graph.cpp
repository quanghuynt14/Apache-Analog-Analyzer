/*************************************************************************
                           Graph  -  description
                             -------------------
    début                : 20/01/2021
    copyright            : (C) 2021 par Francine Jin et Tran Quang Huy
    e-mail               : jinfrancine@hotmail.com
*************************************************************************/

//---------- Réalisation de la classe <Graph> (fichier Graph.cpp) ------------

//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <set>

using namespace std;

//------------------------------------------------------ Include personnel
#include "Graph.h"

//----------------------------------------------------------------- PUBLIC
//-------------------------------------------- Constructeurs - destructeur
Graph::Graph ( )
{
#ifdef MAP
    cout << "Appel au constructeur de <Graph>" << endl;
#endif
} //----- Fin de Graph


Graph::~Graph ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Graph>" << endl;
#endif
} //----- Fin de ~Graph

//----------------------------------------------------- Méthodes publiques
void Graph::AddNode(const string &node) {
    map<string,int>::iterator itNode = nodes.find(node);
    if (itNode == nodes.end()) {
        nodes.insert(make_pair(node, 1));
    } else {
        itNode->second++;
    }
} //----- Fin de AddNode

void Graph::Top10NodeHits() {
    if (nodes.size() == 0) {
        cout << "Empty request" << endl;
        return;
    }
    multimap<int, string, greater <int>> invert;
    for (auto &it : nodes) {
        invert.insert(make_pair(it.second, it.first));
    }
    for (auto &it : invert) {
        if (distance(invert.begin(), invert.find(it.first)) == 10) {
            break;
        }
        cout << it.second << " (" << it.first << " hit" << ((it.first>1)?"s":"") << ")" << endl;
    }
} //----- Fin de Top10NodeHits

void Graph::AddEdge(const string &nodeA, const string &nodeB) {
    pair<string,string> edge = make_pair(nodeA, nodeB);
    map<pair<string,string>,int>::iterator itEdge = edges.find(edge);
    if (itEdge == edges.end()) {
        edges.insert(make_pair(edge, 1));
    } else {
        itEdge->second++;
    }
} //----- Fin de AddEdge

void Graph::CreateDotFile(const string &fileName) {
    ofstream dotFile(fileName);
    if (dotFile.is_open()) {
        dotFile << "digraph {" << endl;
        set<string> nodeName;
        for (auto &it : nodes) {
            nodeName.insert(it.first);
        }
        for (auto &it : edges) {
            if (nodeName.find(it.first.second) != nodeName.end() && 
                nodeName.find(it.first.first) == nodeName.end()) {
                nodeName.insert(it.first.first);
            }
        }
    
        for (auto &it : nodeName) {
            dotFile << "node" << distance(nodeName.begin(), nodeName.find(it));
            dotFile << " [label=\"" << it << "\"];" << endl;
        }
        for (auto &it : edges) {
            dotFile << "node" << distance(nodeName.begin(), nodeName.find(it.first.first)) << " -> ";
            dotFile << "node" << distance(nodeName.begin(), nodeName.find(it.first.second));
            dotFile << " [label=\"" << it.second << "\"];" << endl;
        }
        dotFile << "}" << endl;
    }
    dotFile.close();
    cout << "Dot-file " << fileName << " generated" << endl;
} //----- Fin de CreateDotFile

