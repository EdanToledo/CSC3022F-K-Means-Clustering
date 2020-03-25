//
// Created by edan on 2020/03/16.
//

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "Cluster.h"

namespace TLDEDA001
{
class Clusterer
{

    //list of all images
    std::vector<unsigned char *> AllImages;

    //bool to tell clusterer whether to use standard image features or colour image features
    bool inColour;

    //list of clusters
    std::vector<TLDEDA001::Cluster *> clusters;

    //number of clusters to use
    int numOfClusters;

public:
    //Constructor
    Clusterer();

    //Parameter Constructor
    Clusterer(const int NumOfClusters);

    //Parameter Constructor
    Clusterer(const int NumOfClusters, const bool inColour);

    //reads in single ppm image and returns char pointer to array of pixels
    unsigned char *ReadSingleImage(std::istream &inputStream,const int width,const int height);

    //Converts image to greyscale
    unsigned char *ConvertToGreyScale(unsigned char *ptr,const int width, const int height);

    //Prints PPM Image
    void PrintImage(std::ostream &outputStream, unsigned char *ptr, const int width,const int height, const int colourval);

    //Read in all images and convert them to greyscale from
    //folder directory "dataset"
    void readImagesInGreyScale(const std::string &dataset);

    //Reads in all images in colour
    void readImagesInColour(const std::string &dataset);

    //returns all images in dataset
    std::vector<unsigned char *> getAllImages() const;

    //returns all clusters in a vector
    std::vector<Cluster *> getAllClusters() const;

    //get specific cluster
    Cluster *getCluster(const int index) const;

    //separates greyscale images into their respective clusters
    void ClusterGreyScaleImages(const int binSize);

    //separates colour images into their respective clusters
    void ClusterColourImages(const int binSize);

    //operator overloaded for input into a stream in correct format
    friend std::ostream &operator<<(std::ostream &os, const Clusterer &clusterer);

    //Helper method to check if the values of the previous cluster means are different to the new means
    bool iterationCheck(const std::vector<float> oldmeans, const std::vector<TLDEDA001::Cluster *> newmeans) const;
};

} // namespace TLDEDA001