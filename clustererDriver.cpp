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
            sobel= true;
        }
    }
    
    TLDEDA001::Clusterer clustererobj(bin,k);
    if (colour == true)
    {
        clustererobj.setColour(true);
    }

    clustererobj.readImages(dataset);
    
    if (filter)
    {
        clustererobj.RunThroughEdgeFilter(sobel);
    
    }
    
    clustererobj.ClusterImages();
      
    if (output == "")
    {
        cout << clustererobj;
    }
    else
    {
        ofstream out(output);
        out << clustererobj;
        cout<<"Results outputted to "<<output<<endl;
    }

    return 0;
}