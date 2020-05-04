
//
// Created by edan on 2020/03/16.
//

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "Clusterer.h"
#include <fstream>
#include <set>
#include <cstdlib>
#include <array>
#include <random>
#include <chrono>
#include <dirent.h>
#include <bits/stdc++.h>

using namespace std;

//Default Constructor
TLDEDA001::Clusterer::Clusterer()
{
    this->numOfClusters = 10;
    this->inColour = false;
    this->binSize = 1;
}

//Parameter Constructor
TLDEDA001::Clusterer::Clusterer(const int binSize) : TLDEDA001::Clusterer::Clusterer(binSize, 10, false)
{
}

//Parameter Constructor
TLDEDA001::Clusterer::Clusterer(const int binSize, const int NumOfClusters) : TLDEDA001::Clusterer::Clusterer(binSize, NumOfClusters, false)
{
}

//Parameter Constructor
TLDEDA001::Clusterer::Clusterer(const int binSize, const int NumOfClusters, const bool inColour) : TLDEDA001::Clusterer::Clusterer(binSize, NumOfClusters, inColour, false)
{
}

//Parameter Constructor
TLDEDA001::Clusterer::Clusterer(const int binSize, const int NumOfClusters, const bool inColour, const bool EdgeFilter)
{
    this->binSize = binSize;
    this->numOfClusters = NumOfClusters;
    this->inColour = inColour;
    this->EdgeFilter = EdgeFilter;
}

void TLDEDA001::Clusterer::setEdge(const bool edge, const bool sobel)
{
    this->EdgeFilter = edge;
    this->sobel = sobel;
}

//Reads a single image and puts it into a vector and returns it
vector<unsigned char> TLDEDA001::Clusterer::ReadSingleImage(istream &inputStream, const int width, const int height)
{
    int size = width * height * 3;
    vector<unsigned char> buffer(size);
    inputStream.read(reinterpret_cast<char *>(&buffer[0]), size);
    return buffer;
}

//Converts image to greyscale
vector<unsigned char> TLDEDA001::Clusterer::ConvertToGreyScale(vector<unsigned char> buffer, const int width, const int height)
{
    float r = 0.21;
    float g = 0.72;
    float b = 0.07;

    for (int i = 0; i < width * height * 3; i += 3)
    {
        float greyscaleValue = (buffer[i] * r) + (buffer[i + 1] * g) + (buffer[i + 2] * b);
        buffer[i] = greyscaleValue;
        buffer[i + 1] = greyscaleValue;
        buffer[i + 2] = greyscaleValue;
    }
    return buffer;
}

//for testing use - depends on circumstances
//Prints ppm image from char array data
void TLDEDA001::Clusterer::PrintImage(ostream &outputStream, vector<unsigned char> buffer, const int width, const int height, const int colourval)
{
    outputStream << "P6"
                 << " "
                 << width << " "
                 << height << " "
                 << colourval << " ";

    outputStream.write(reinterpret_cast<char *>(&buffer[0]), width * height * 3);
}

//Read in all the images and puts them into image features.
void TLDEDA001::Clusterer::readImages(const string &dataset)
{
    cout << "Reading Images..." << endl;

    int width, height, colourval;
    //names of the images
    std::vector<std::string> filenames;

    DIR *dirpointer = opendir(dataset.c_str());
    dirent *entry = readdir(dirpointer);
    int count = 0;
    string avoid1 = ".";
    string avoid2 = "..";

    while (entry)
    {

        if (((string)entry->d_name).compare(".") == 0 || ((string)entry->d_name).compare("..") == 0)
        {
            entry = readdir(dirpointer);
            continue;
        }

        filenames.push_back(entry->d_name);

        count++;
        entry = readdir(dirpointer);
    }

    for (int i = 0; i < filenames.size(); i++)
    {

        ifstream in(dataset + filenames[i], ios::binary);

        string line;

        in >> line >> ws;

        if (line.find("P6") == std::string::npos)
        {
            cout << "This file is not a P6 PPM, the formatting might be incorrect!" << endl;
            break;
        }

        getline(in, line);

        while (line[0] == '#')
        {
            getline(in, line);
        }

        std::istringstream is(line);
        is >> width >> ws;
        is >> height >> ws;
        is >> colourval >> ws;

        if (inColour)
        {
            this->AllImagesAsFeatures.push_back(TLDEDA001::ImageFeature(filenames[i], ReadSingleImage(in, width, height), binSize, true));
        }
        else
        {
            this->AllImagesAsFeatures.push_back(TLDEDA001::ImageFeature(filenames[i], ConvertToGreyScale(ReadSingleImage(in, width, height), width, height), binSize, false));

            if (EdgeFilter)
            {
                AllImagesAsFeatures[i].RunThroughEdgeFilter(sobel);
            }
        }

        in.close();
    }
}

//sets in colour
void TLDEDA001::Clusterer::setColour(const bool inColour)
{
    this->inColour = inColour;
}



//returns all clusters in a vector
const vector<TLDEDA001::Cluster> & TLDEDA001::Clusterer::getAllClusters() const
{
    return this->clusters;
}


//Assign Images to cluster - single iteration
bool TLDEDA001::Clusterer::AssignImageToCluster(vector<TLDEDA001::ImageFeature> ImagesAsFeatures)
{
    bool iterationDone = true;
    for (int i = 0; i < ImagesAsFeatures.size(); i++)
    {
        int index = 0;
        float min = ImagesAsFeatures[i].calculateDistance(clusters[0].getMeanFeature());

        for (int j = 1; j < this->clusters.size(); j++)
        {

            if (ImagesAsFeatures[i].calculateDistance(clusters[j].getMeanFeature()) < min)
            {
                min = ImagesAsFeatures[i].calculateDistance(clusters[j].getMeanFeature());
                index = j;
            }
        }

        if (ImagesAsFeatures[i].getClusterID() != index)
        {
            iterationDone = false;
        }

        ImagesAsFeatures[i].setClusterID(index);
        this->clusters[index].addImage(ImagesAsFeatures[i]);
    }

    for (int i = 0; i < clusters.size(); i++)
    {
        this->clusters[i].calculateNewMean();
    }

    return iterationDone;
}

//separates images into their respective clusters
void TLDEDA001::Clusterer::ClusterImages()
{

    cout << "Clustering Images..." << endl;

    srand(time(0));
    vector<int> randomIndexes;

    for (int i = 0; i < AllImagesAsFeatures.size(); i++)
    {
        randomIndexes.push_back(i);
    }

    std::random_shuffle(randomIndexes.begin(), randomIndexes.end());

    if (numOfClusters > AllImagesAsFeatures.size())
    {
        numOfClusters = AllImagesAsFeatures.size();
    }

    for (int i = 0; i < numOfClusters; i++)
    {
        this->clusters.push_back(TLDEDA001::Cluster(AllImagesAsFeatures[randomIndexes[i]]));
    }

    AssignImageToCluster(AllImagesAsFeatures);

    int iterationcounter = 1;

    bool doneIteration = false;

    while (!doneIteration)
    {

        for (int i = 0; i < this->numOfClusters; i++)
        {
            this->clusters[i].clearAllImages();
        }

        doneIteration = AssignImageToCluster(AllImagesAsFeatures);
        
        if (iterationcounter>15)
        {
           break;
        }
        
        iterationcounter++;
    }

    cout << "Completed Clustering in " << iterationcounter << " iterations" << endl;
}

//operator overloaded for input into a stream in correct format
ostream &TLDEDA001::operator<<(ostream &os, const TLDEDA001::Clusterer &clusterer)
{
    for (int i = 0; i < clusterer.numOfClusters; i++)
    {
        os << "Cluster " << i << ": ";
        for (int j = 0; j < clusterer.getAllClusters()[i].getAllClusterImages().size(); j++)
        {

            os << clusterer.getAllClusters()[i].getImage(j).getName() << " ";
        }
        os << endl;
    }

    return os;
}
