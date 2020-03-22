
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

using namespace std;

//Default Constructor
TLDEDA001::Clusterer::Clusterer()
{
    this->numOfClusters = 10;
}

//Parameter Constructor
TLDEDA001::Clusterer::Clusterer(int NumOfClusters)
{
    this->numOfClusters = NumOfClusters;
}

//Destructor
TLDEDA001::Clusterer::~Clusterer()
{

    for (int i = 0; i < this->AllImages.size(); i++)
    {
        delete[] this->AllImages[i];
    }
}

//Reads a single image and puts it into a char ptr and returns it
unsigned char *TLDEDA001::Clusterer::ReadSingleImage(istream &inputStream, int width, int height)
{
    int size = width * height * 3;
    unsigned char *ptr = new unsigned char[size];
    inputStream.read(reinterpret_cast<char *>(ptr), size);
    return ptr;
}

//Converts image to greyscale
unsigned char *TLDEDA001::Clusterer::ConvertToGreyScale(unsigned char *ptr, int width, int height)
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
void TLDEDA001::Clusterer::PrintImage(ostream &outputStream, unsigned char *ptr, int width, int height, int colourval)
{
    outputStream << "P6"
                 << " "
                 << width << " "
                 << height << " "
                 << colourval << " ";

    outputStream.write(reinterpret_cast<char *>(ptr), width * height * 3);
}

//Read in images and convert them to grayscale
void TLDEDA001::Clusterer::readImages(const string &dataset)
{

    int width, height, colourval;

    vector<string> filenames;

    //HARDCODED NAMES

    filenames.push_back("one_");
    filenames.push_back("two_");
    filenames.push_back("three_");
    filenames.push_back("four_");
    filenames.push_back("five_");
    filenames.push_back("six_");
    filenames.push_back("seven_");
    filenames.push_back("eight_");
    filenames.push_back("nine_");
    filenames.push_back("zero_");

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {

            ifstream in(dataset + filenames[i] + to_string(j + 1) + ".ppm", ios::binary);

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

            this->AllImages.push_back(ConvertToGreyScale(ReadSingleImage(in, width, height), width, height));
            in.close();
        }
    }

    
}

//returns all images in dataset in greyscale
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

//FIX THIS METHOD
//separates images into their respective clusters
void TLDEDA001::Clusterer::ClusterImages()
{

    vector<TLDEDA001::ImageFeature *> ImagesAsFeatures;

    //HARDCODED NAMES
    vector<string> filenames;
    filenames.push_back("one_");
    filenames.push_back("two_");
    filenames.push_back("three_");
    filenames.push_back("four_");
    filenames.push_back("five_");
    filenames.push_back("six_");
    filenames.push_back("seven_");
    filenames.push_back("eight_");
    filenames.push_back("nine_");
    filenames.push_back("zero_");

    int count = 0;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {

            ImagesAsFeatures.push_back(new TLDEDA001::ImageFeature(filenames[i] + to_string(j + 1), this->AllImages[count]));

            count++;
        }
    }
    
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
    
    
    
    float min = ImagesAsFeatures[0]->calculateDistance(clusters[0]->getMean());
        
  
    for (int i = 0; i < ImagesAsFeatures.size(); i++)
    {
         
        int index = 0;
        for (int j = 0; j < this->clusters.size(); j++)
        {
             
            if (ImagesAsFeatures[i]->calculateDistance(clusters[j]->getMean())<min)
            {
               min = ImagesAsFeatures[i]->calculateDistance(clusters[j]->getMean());
               index=j;
            }
            
        }
        

        this->clusters[index]->addImage(ImagesAsFeatures[i]);
        
        this->clusters[index]->calculateNewMean();
       
    }
    
    /*
    while (true)
    {
       
       for (int i = 0; i < imagefeatures.size(); i++)
    {
        float min = INT16_MAX;
        int index = 0;
        for (int j = 0; i < this->clusters.size(); i++)
        {
            
            if (imagefeatures[i].calculateDistance(clusters[j].getMean())<min)
            {
               min = imagefeatures[i].calculateDistance(clusters[j].getMean());
               index=j;
            }
            
        }
        this->clusters[index].addImage(imagefeatures[i]);
        this->clusters[index].calculateNewMean();
    }

    }
    
*/
}

//operator overloaded for input into a stream in correct format
ostream &TLDEDA001::operator<<(ostream &os, const TLDEDA001::Clusterer &clusterer)
{

    for (int i = 0; i < clusterer.clusters.size(); i++)
    {
        
        os << "cluster " << i << ": ";
        for (int j = 0; j < clusterer.clusters[i]->getAllClusterImages().size(); j++)
        {
            os << clusterer.clusters[i]->getAllClusterImages()[i]->getName() << " ";
        }
    }
}
