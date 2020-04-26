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
   std::vector<TLDEDA001::ImageFeature *> AllImagesAsFeatures;
    //names of the images
    std::vector<std::string> filenames;
    //bool to tell clusterer whether to use standard image features or colour image features
    bool inColour;

    int binSize;

    //list of clusters
    std::vector<TLDEDA001::Cluster *> clusters;

    //number of clusters to use
    int numOfClusters;

public:
    //Constructor
    Clusterer();

    //Parameter Constructor
    Clusterer(const int binSize);

    //Parameter Constructor
    Clusterer(const int binSize,const int NumOfClusters);

    //Parameter Constructor
    Clusterer(const int binSize,const int NumOfClusters, const bool inColour);

    //reads in single ppm image and returns char pointer to array of pixels
    unsigned char *ReadSingleImage(std::istream &inputStream,const int width,const int height);

    //Converts image to greyscale
    unsigned char *ConvertToGreyScale(unsigned char *ptr,const int width, const int height);

    //Prints PPM Image
    void PrintImage(std::ostream &outputStream, unsigned char *ptr, const int width,const int height, const int colourval);

    //Reads in all images 
    void readImages(const std::string &dataset);

    //returns all images in dataset
    std::vector<TLDEDA001::ImageFeature *> getAllImages() const;

    //returns all clusters in a vector
    std::vector<Cluster *> getAllClusters() const;

    //get specific cluster
    Cluster *getCluster(const int index) const;

    //separates images into their respective clusters
    void ClusterImages();

    //Assign Images to cluster - single iteration
    bool AssignImageToCluster( std::vector<TLDEDA001::ImageFeature *> ImagesAsFeatures);

    //sets in colour
    void setColour(const bool inColour);

    //operator overloaded for input into a stream in correct format
    friend std::ostream &operator<<(std::ostream &os, const Clusterer &clusterer);

    //Run the images through a prewitt or sobel filter
    void RunThroughEdgeFilter(bool sobel);
};

} // namespace TLDEDA001