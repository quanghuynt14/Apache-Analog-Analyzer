#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cstdlib>
using namespace std;

#include <regex>
#include "Request.h"
#include "Graph.h"


int main(int argc, char *argv[]) {

    string logFileName = "";
    string dotFileName = "";
    set<string> fileExtenstion = {".css", ".png", ".bmp", ".jpg", ".gif", ".ico", ".js"};
    string dotExtenstion = ".dot";
    string check_parametre = "";
    string prendreExtenstion = "";
    bool exclude = false;
    string timeSelected = "";
    if (argc < 2 || argc > 9) {
        cerr << "Error - Not correct number of arguments provided" << endl;
        return 1;
    } else {
        int i = 0;
        while (++i < argc) {
            //cout << i << " " << argv[i] << endl;
            if (argv[i][0] == '-') {
                switch (argv[i][1])
                {
                case 'e':
                    exclude = true;
                    break;
                case 'g':
                    if (++i < argc) {
                        check_parametre = argv[i];
                        if (dotExtenstion.compare(check_parametre.substr(check_parametre.size() - dotExtenstion.size())) == 0) {
                            dotFileName = argv[i];
                        } else {
                            cerr << "Error - Missing dot file name after -g option" << endl;
                            return 2;
                        }
                    } else {
                        cerr << "Error - Missing dot file name after -g option and apache log file name" << endl;
                        return 3;
                    }
                    break;
                case 't':
                    if (++i < argc && argv[i][0] != '-' && argv[i][0] != '.') {
                        timeSelected = argv[i];
                        
                        try {
                            int x = stoi(timeSelected);
                            if (x > 23) {
                                cerr << "Error - Hour must be number integer between 0 and 23" << endl;
                                return 4;
                            }
                            if (timeSelected.size() == 1) timeSelected = "0" + timeSelected;
                        } catch (invalid_argument& e) {
                            cerr << "Error - Hour must be number integer between 0 and 23" << endl;
                            return 4;
                        }
                    } else {
                        cerr << "Error - Missing hour to analyze" << endl;
                        return 5;
                    }
                    break;
                case 'p':
                    if (++i < argc) {
                        check_parametre = argv[i];
                        for (auto &it : fileExtenstion) {
                            if (it == check_parametre) {
                                prendreExtenstion = argv[i];
                            }
                        }
                        if (check_parametre == ".html") {
                            prendreExtenstion = argv[i];
                        }
                        if (prendreExtenstion == "") {
                            cerr << "Error - Missing type extension file after -p option" << endl;
                            return 9;
                        }
                    } else {
                        cerr << "Error - Missing type extension file after -p option and apache log file name" << endl;
                        return 10;
                    }
                    break;
                default:
                    cerr << "Error command" << endl;
                    return 6;
                    break;
                }
            } else {
                logFileName = argv[i];
            }
        }
    }
    
    if (logFileName == "") {
        cerr << "Error - Missing apache log file name to analyze" << endl;
        return 7;
    }

    ifstream fileStream(logFileName);
    string readLine = "";

    if (fileStream.is_open()) {
        //cout << "Opened file: " << logFileName << endl;
        // IP dois etre integer 0-255
        string ip_0_255 = "([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
        // day dois etre integer 0-31
        string day = "(0?[1-9]|[12]\\d|3[01])";
        // hour dois etre integer 00-23 ou == timeSelected 
        string hour = (timeSelected != "")?timeSelected:"([01][0-9]|2[0-3])";
        
        // minute et second doivent etre integer 00-59
        string mi_se = "([0-5][0-9])";

        regex regLine("^" + ip_0_255 + "\\." + ip_0_255 + "\\." + ip_0_255 + "\\." + ip_0_255 + " [^ ]+ [^ ]+ " + 
                      "\\[" + day + "\\/\\w{3}\\/\\d{4}\\:" + hour + "\\:" + mi_se + "\\:" + mi_se + " (\\+|\\-)\\d+\\] " +
                      "\"\\w+" + "(.*)" + prendreExtenstion + " HTTP/\\d+\\.\\d+\" \\d+ (\\d+|-) \"[^ |\"]+\" \"[^\"]+\"$");

        //int dem = 0;
        Graph graph;

        //ofstream f("huy2.txt");
        while (getline(fileStream, readLine)) {
            if (regex_match(readLine, regLine)) {
                //dem++;
                Request r(readLine);
                bool ok = true;
                if (exclude) {
                    string rURL = r.GetRequestURL();
                    string rReferer = r.GetRefererURL();
                    for (auto &it : fileExtenstion) 
                        if (it.compare(prendreExtenstion) != 0) {
                            ok &= it.compare(rURL.substr(rURL.size() - it.size()));
                            ok &= it.compare(rReferer.substr(rReferer.size() - it.size()));
                        }
                }

                if (r.GetStatusCode() < 200 || r.GetStatusCode() > 300) {
                    ok = false;
                }

                if (ok) {
                    graph.AddNode(r.GetRequestURL());
                    graph.AddEdge(r.GetRefererURL(), r.GetRequestURL());
                }
                //f << dem << " " << r.GetRequestURL() << " " << r.GetRefererURL() << endl;
            } else {
                //cout << readLine << endl;
            }
        }
        //f.close();
        //cout << dem << endl;
        //cout << (stoi(timeSelected)+1) << endl;
        if (dotFileName != "") graph.CreateDotFile(dotFileName);
        if (timeSelected != "") {
            cout << "Warning : only hits between " << timeSelected << "h to ";
            if (timeSelected == "23") 
                cout << "0";
            else
                cout << (stoi(timeSelected)+1);
            cout << "h have been taken into account" << endl;
        }
        graph.Top10NodeHits();
    } else {
        cerr << "Error - Reading file: " << logFileName << endl;
        fileStream.close();
        return 8;
    }


    return 0;
}