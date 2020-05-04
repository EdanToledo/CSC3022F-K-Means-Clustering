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

    //list of all images in their imagefeature object container
    std::vector<TLDEDA001::ImageFeature> AllImagesAsFeatures;

    //bool to tell clusterer whether to use greyscale image features or colour image features
    bool inColour;

    //bool to tell clusterer whether to use edge filter preprocessing on images
    bool EdgeFilter, sobel;

    //Bin range
    int binSize;

    //list of clusters
    std::vector<TLDEDA001::Cluster> clusters;

    //number of clusters to use
    int numOfClusters;

public:
    //Constructor
    Clusterer();

    //Parameter Constructor
    Clusterer(const int binSize);

    //Parameter Constructor
    Clusterer(const int binSize, const int NumOfClusters);

    //Parameter Constructor
    Clusterer(const int binSize, const int NumOfClusters, const bool inColour);

    //Parameter Constructor
    Clusterer(const int binSize, const int NumOfClusters, const bool inColour, const bool EdgeFilter);

    //reads in single ppm image and returns a vector of unsigned chars
    std::vector<unsigned char> ReadSingleImage(std::istream &inputStream, const int width, const int height);

    //Converts an image to greyscale and returns the greyscale image in a vector of unsigned chars
    std::vector<unsigned char> ConvertToGreyScale(std::vector<unsigned char> , const int width, const int height);

    //Prints PPM Image used for testing
    void PrintImage(std::ostream &outputStream, std::vector<unsigned char>, const int width, const int height, const int colourval);

    //Reads in all images from given directory and creates imagefeature objects for them. This function will convert all the images to greyscale if specified.
    void readImages(const std::string &dataset);

    //returns all clusters in the vector
    const std::vector<Cluster> & getAllClusters() const;

    //separates images into their respective clusters - runs the algorithm
    void ClusterImages();

    //Assign Images to cluster - single iteration
    bool AssignImageToCluster(std::vector<TLDEDA001::ImageFeature> ImagesAsFeatures);

    //sets the incolour boolean.
    void setColour(const bool inColour);

    //operator overloaded for input into a stream in correct format
    friend std::ostream &operator<<(std::ostream &os, const Clusterer &clusterer);

    void setEdge(const bool edge, const bool sobel);
};

} // namespace TLDEDA001