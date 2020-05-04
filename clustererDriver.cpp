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

    if (argc <= 1 || argc >= 11)
    {
        cout << "Arguments were entered incorrectly" << endl;
        return 0;
    }

    string dataset, output = "";
    int bin = 1;
    int k = 10;
    dataset = (string)argv[1];
    bool colour = false;
    bool filter = false;
    bool sobel = false;

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
        else if ((string)argv[i] == "-edgefilter1")
        {
            filter = true;
            sobel = false;
        }
        else if ((string)argv[i] == "-edgefilter2")
        {
            filter = true;
            sobel = true;
        }
    }

    TLDEDA001::Clusterer clustererobj(bin, k, colour, filter);
    cout<<"Clustering will commence with the following settings: \n"<<"Amount of Clusters: "<<k<<"\n"<<"Bin Range: "<<bin<<"\n"<<"Using RGB: "<<colour<<"\n"<<"Using Edge Filters: "<<filter+sobel<<endl;
    if (sobel)
    {
        clustererobj.setEdge(true, true);
    }

    clustererobj.readImages(dataset);

    clustererobj.ClusterImages();

    if (output == "")
    {
        cout << clustererobj;
    }
    else
    {
        ofstream out(output);
        out << clustererobj;
        cout << "Results outputted to " << output << endl;
    }

    return 0;
}