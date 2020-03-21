
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
TLDEDA001::Clusterer::Clusterer() {
    this->numOfClusters = 10;
}

//Parameter Constructor
TLDEDA001::Clusterer::Clusterer(int NumOfClusters) {
    this->numOfClusters = NumOfClusters;
}

//Destructor
TLDEDA001::Clusterer::~Clusterer()
{

    for (int i = 0; i < this->images.size(); i++)
    {
        for (int j = 0; j < 32; j++)
        {
            delete[] this->images[i][j];
        }
        delete[] this->images[i];
    }
}

//FIX THIS METHOD

//Read in images and convert them to grayscale
void TLDEDA001::Clusterer::readImages(const string & dataset)
{
    vector<unsigned char **> temp;
    int width, height, colourval;
/*
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
*/
    vector<string> filenames;
    filenames.push_back("Gradient_Numbers_PPMS/one_1.ppm");
     filenames.push_back("Gradient_Numbers_PPMS/two_1.ppm");
     filenames.push_back("Gradient_Numbers_PPMS/three_1.ppm");
     filenames.push_back("Gradient_Numbers_PPMS/four_1.ppm");
     filenames.push_back("Gradient_Numbers_PPMS/five_1.ppm");
     filenames.push_back("Gradient_Numbers_PPMS/six_1.ppm");
     filenames.push_back("Gradient_Numbers_PPMS/seven_1.ppm");
     filenames.push_back("Gradient_Numbers_PPMS/eight_1.ppm");
     filenames.push_back("Gradient_Numbers_PPMS/nine_1.ppm");
     filenames.push_back("Gradient_Numbers_PPMS/zero_1.ppm");

    int count = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {

            //ifstream in(dataset + filenames[i] + to_string(j + 1) + ".ppm", ios::binary);
            ifstream in(filenames[i],ios::binary);
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

            temp.push_back(new unsigned char *[height]);

            for (int k = 0; k < height; k++)
            {
                temp[count][k] = new unsigned char[width];
                unsigned char colourvalues[width * 3];
                in.read(reinterpret_cast<char *>(colourvalues), width * 3);

                //Convert to greyscale
                for (int z = 0; z < width; z++)
                {
                    temp[count][k][z] = colourvalues[z * 3] * 0.21 + colourvalues[(z * 3) + 1] * 0.72 + colourvalues[(z * 3) + 2] * 0.07;
                    
                }
            }
           
            count++;
            
        }
    }
    this->images = temp;



    TLDEDA001::ImageFeature feat("nem",images[0]);
     TLDEDA001::ImageFeature feat2("nem2",images[50]);

     cout<<"first "<<feat.getMean()<<"    "<<feat2.getMean()<<endl;
     
     
}

//returns all images in dataset in greyscale
vector<unsigned char **> TLDEDA001::Clusterer::getAllImages()const
{
    return this->images;
}

//returns all clusters in a vector
vector<TLDEDA001::Cluster*> TLDEDA001::Clusterer::getAllClusters()const
{
    return this->clusters;
}

//get specific cluster
TLDEDA001::Cluster* TLDEDA001::Clusterer::getCluster(const int index)const
{
    return this->clusters[index];
}



//FIX THIS METHOD
//separates images into their respective clusters
void TLDEDA001::Clusterer::ClusterImages()
{
    vector<TLDEDA001::ImageFeature *> imagefeatures;

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
            imagefeatures.push_back(new TLDEDA001::ImageFeature(filenames[i] + to_string(j + 1), this->images[count]));
            
           
            count++;
            
        }
    }
   
    vector<int> randomIndexes;
   
    for (int i = 0; i < imagefeatures.size(); i++)
    {
        randomIndexes.push_back(i);
    }
   
    std::random_shuffle ( randomIndexes.begin(), randomIndexes.end() );

    for (int i = 0; i < numOfClusters; i++)
    {
        this->clusters.push_back(new TLDEDA001::Cluster(*imagefeatures[randomIndexes[i]]));
       // cout<<imagefeatures[randomIndexes[i]]->getMean()<<endl;
    }
    /*
    for (int i = 0; i < 100; i++)
    {
       float min = imagefeatures[i]->calculateDistance(clusters[0]->getMean());
    cout<<min;
    }
    
    float min = imagefeatures[0]->calculateDistance(clusters[0]->getMean());
    cout<<min;
      /*
    for (int i = 0; i < imagefeatures.size(); i++)
    {
        int index = 0;
        for (int j = 0; i < this->clusters.size(); i++)
        {
            
            if (imagefeatures[i]->calculateDistance(clusters[j]->getMean())<min)
            {
               min = imagefeatures[i]->calculateDistance(clusters[j]->getMean());
               index=j;
            }
            
        }
        this->clusters[index]->addImage(*imagefeatures[i]);
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
        vector<TLDEDA001::ImageFeature*> temp = clusterer.clusters[i]->getAllClusterImages();
        os << "cluster " << i << ": ";
        for (int j = 0; j < temp.size(); j++)
        {
            os << temp[i]->getName() << " ";
        }
    }
}
