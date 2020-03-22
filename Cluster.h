//
// Created by edan on 2020/03/16.
//

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "ImageFeature.h"

namespace TLDEDA001
{
class Cluster
{

    //Feature that describes this cluster
    float mean;

    //List of imagefeatures in this cluster
    std::vector<ImageFeature *> imageFeatures;

public:
    //Default Constructor
    Cluster();

    //Parameter Constructor
    Cluster(ImageFeature meanfeature);

    //Parameter constructor
    Cluster(float mean);

    //Destructor
    ~Cluster();

    //Set mean feature
    void setMean(float mean);

    //Add an image to this cluster
    void addImage(ImageFeature * Image);

    //Get an image for this cluster
    ImageFeature *getImage(int index) const;

    //Get the mean of this cluster
    float getMean() const;

    //Get all images from this cluster
    std::vector<ImageFeature *> getAllClusterImages() const;

    //calculate new mean based on image features inside this cluster
    void calculateNewMean();

    //clears all images for the cluster
    void clearAllImages();
};

} // namespace TLDEDA001
