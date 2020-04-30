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
    //Mean Histogram
    ImageFeature *MeanHist;

    //List of imagefeatures in this cluster
    std::vector<ImageFeature *> imageFeatures;

public:
    //Default Constructor
    Cluster();

    //Parameter Constructor
    Cluster(const ImageFeature *meanfeature);

    //Destructor
    ~Cluster();

    //Add an image to this cluster
    void addImage( ImageFeature *Image);

    //Get an image from this cluster
    ImageFeature *getImage(const int index) const;

    //Get the mean Feature of this cluster
    TLDEDA001::ImageFeature getMeanFeature() const;

    //Get all images from this cluster
    std::vector<ImageFeature *> getAllClusterImages() const;

    //calculate new mean based on image features inside this cluster
    void calculateNewMean();

    //clears all images for the cluster
    void clearAllImages();
};

} // namespace TLDEDA001
