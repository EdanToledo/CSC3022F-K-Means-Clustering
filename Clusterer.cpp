
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

using namespace std;

//Default Constructor
TLDEDA001::Clusterer::Clusterer()
{
    this->numOfClusters = 10;
    this->inColour = false;
}

//Parameter Constructor
TLDEDA001::Clusterer::Clusterer(const int NumOfClusters)
{
    this->numOfClusters = NumOfClusters;
    this->inColour = false;
}

//Parameter Constructor
TLDEDA001::Clusterer::Clusterer(const int NumOfClusters, const bool inColour)
{
    this->numOfClusters = NumOfClusters;
    this->inColour = inColour;
}

//Reads a single image and puts it into a char ptr and returns it
unsigned char *TLDEDA001::Clusterer::ReadSingleImage(istream &inputStream, const int width, const int height)
{
    int size = width * height * 3;
    unsigned char *ptr = new unsigned char[size];
    inputStream.read(reinterpret_cast<char *>(ptr), size);
    return ptr;
}

//Converts image to greyscale
unsigned char *TLDEDA001::Clusterer::ConvertToGreyScale(unsigned char *ptr, const int width, const int height)
{
    float r = 0.21;
    float g = 0.72;
    float b = 0.07;

    for (int i = 0; i < width * height * 3; i += 3)
    {
        float greyscaleValue = (ptr[i] * r) + (ptr[i + 1] * g) + (ptr[i + 2] * b);
        ptr[i] = greyscaleValue;
        ptr[i + 1] = greyscaleValue;
        ptr[i + 2] = greyscaleValue;
    }
    return ptr;
}

//Prints ppm image from char array data
void TLDEDA001::Clusterer::PrintImage(ostream &outputStream, unsigned char *ptr, const int width, const int height, const int colourval)
{
    outputStream << "P6"
                 << " "
                 << width << " "
                 << height << " "
                 << colourval << " ";

    outputStream.write(reinterpret_cast<char *>(ptr), width * height * 3);
}

//Read in images in colour
void TLDEDA001::Clusterer::readImages(const string &dataset)
{
    int width, height, colourval;

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

        getline(in, line);

        if (line != "P6")
        {
            break;
        }

        while (line.at(0) == '#')
        {
            getline(in, line);
        }

        in >> width >> ws >> height;
        getline(in, line);
        in >> colourval >> ws;

        if (inColour)
        {
            this->AllImages.push_back(ReadSingleImage(in, width, height));
        }
        else
        {
            this->AllImages.push_back(ConvertToGreyScale(ReadSingleImage(in, width, height), width, height));
        }

        in.close();
    }
}

//sets in colour
void TLDEDA001::Clusterer::setColour(const bool inColour)
{
    this->inColour = inColour;
}

//returns all images in dataset
vector<unsigned char *> TLDEDA001::Clusterer::getAllImages() const
{
    return this->AllImages;
}

//returns all clusters in a vector
vector<TLDEDA001::Cluster *> TLDEDA001::Clusterer::getAllClusters() const
{
    return this->clusters;
}

//get specific cluster
TLDEDA001::Cluster *TLDEDA001::Clusterer::getCluster(const int index) const
{
    return this->clusters[index];
}

//separates images into their respective clusters
void TLDEDA001::Clusterer::ClusterImages(const int binSize)
{

    vector<TLDEDA001::ImageFeature *> ImagesAsFeatures;

    for (int i = 0; i < filenames.size(); i++)
    {
        if (!inColour)
        {
            ImagesAsFeatures.push_back(new TLDEDA001::ImageFeature(filenames[i], this->AllImages[i], binSize));
        }
        else
        {
            ImagesAsFeatures.push_back(new TLDEDA001::ImageFeature(filenames[i], this->AllImages[i], binSize, true));
        }
    }

    srand(time(0));
    vector<int> randomIndexes;

    for (int i = 0; i < ImagesAsFeatures.size(); i++)
    {
        randomIndexes.push_back(i);
    }

    std::random_shuffle(randomIndexes.begin(), randomIndexes.end());

    for (int i = 0; i < numOfClusters; i++)
    {
        this->clusters.push_back(new TLDEDA001::Cluster(*ImagesAsFeatures[randomIndexes[i]]));
    }

    for (int i = 0; i < ImagesAsFeatures.size(); i++)
    {
        float min = ImagesAsFeatures[i]->calculateDistance(clusters[0]->getMean());

        int index = 0;
        for (int j = 0; j < this->clusters.size(); j++)
        {

            if (ImagesAsFeatures[i]->calculateDistance(clusters[j]->getMean()) < min)
            {
                min = ImagesAsFeatures[i]->calculateDistance(clusters[j]->getMean());
                index = j;
            }
        }

        this->clusters[index]->addImage(ImagesAsFeatures[i]);

        this->clusters[index]->calculateNewMean();
    }

    bool doneIteration = false;

    while (!doneIteration)
    {
        vector<float> oldmeans;
        for (int i = 0; i < this->numOfClusters; i++)
        {
            oldmeans.push_back(this->clusters[i]->getMean());
            this->clusters[i]->clearAllImages();
        }

        for (int i = 0; i < ImagesAsFeatures.size(); i++)
        {
            float min = ImagesAsFeatures[i]->calculateDistance(clusters[0]->getMean());
            int index = 0;
            for (int j = 0; j < this->clusters.size(); j++)
            {

                if (ImagesAsFeatures[i]->calculateDistance(clusters[j]->getMean()) < min)
                {
                    min = ImagesAsFeatures[i]->calculateDistance(clusters[j]->getMean());
                    index = j;
                }
            }

            this->clusters[index]->addImage(ImagesAsFeatures[i]);

            this->clusters[index]->calculateNewMean();
        }

        doneIteration = iterationCheck(oldmeans, this->clusters);
    }
}

//helper method to know when iteration is done - returns true if there is a difference
bool TLDEDA001::Clusterer::iterationCheck(const vector<float> oldmeans, const vector<TLDEDA001::Cluster *> newmeans) const
{
    bool temp = true;
    for (int i = 0; i < this->numOfClusters; i++)
    {
        if (oldmeans[i] != this->clusters[i]->getMean())
        {
            temp = false;
        }
    }

    return temp;
}

//operator overloaded for input into a stream in correct format
ostream &TLDEDA001::operator<<(ostream &os, const TLDEDA001::Clusterer &clusterer)
{
    for (int i = 0; i < clusterer.numOfClusters; i++)
    {
        os << "Cluster " << i << ": ";
        for (int j = 0; j < clusterer.getCluster(i)->getAllClusterImages().size(); j++)
        {
            os << clusterer.getCluster(i)->getImage(j)->getName() << " ";
        }
        os << endl;
    }

    return os;
}
