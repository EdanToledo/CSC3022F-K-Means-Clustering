//
// Created by edan on 2020/03/16.
//

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include "Clusterer.h"

using namespace std;

int main(int argc, char *argv[])
{

    if (argc <= 1 || argc >= 9)
    {
        cout << "Arguments were entered incorrectly" << endl;
        return 0;
    }

    string dataset, output = "";
    int bin = 1;
    int k = 10;
    dataset = (string)argv[1];
    bool colour = false;

    for (int i = 1; i < argc; i++)
    {

        if ((string)argv[i] == "-o")
        {
            output = (string)argv[i + 1];
        }
        else if ((string)argv[i] == "-k")
        {

            k = stoi((string)argv[i + 1]);
        }
        else if ((string)argv[i] == "-bin")
        {

            bin = stoi((string)argv[i + 1]);
        }
        else if ((string)argv[i] == "-color")
        {
            colour = true;
        }
    }
    
    TLDEDA001::Clusterer clustererobj(k);
    if (colour == true)
    {
        clustererobj.setColour(true);
    }

    clustererobj.readImages(dataset);
    clustererobj.ClusterImages(bin);
    
    if (output == "")
    {
        cout << clustererobj;
    }
    else
    {
        ofstream out(output);
        out << clustererobj;
    }

    return 0;
}