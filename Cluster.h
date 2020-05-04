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
    std::vector<std::vector<int>> histograms;
    int binSize;
    int colourval;

    //List of imagefeatures in this cluster
    std::vector<ImageFeature> imageFeatures;

public:
    //Default Constructor
    Cluster();

    //Parameter Constructor
    Cluster(const ImageFeature &meanfeature);

    //Add an image to this cluster
    void addImage(const ImageFeature & Image);

    //Get an image from this cluster
    ImageFeature getImage(const int index) const;

    //delete an Image
    void DelImage(const int index);

    //Get the RGB mean histograms
    const std::vector<std::vector<int>> & getMeanFeature() const;

    //Get all images from this cluster
    const std::vector<ImageFeature> & getAllClusterImages() const;

    //calculate new mean based on image features inside this cluster
    void calculateNewMean();

    //clears all images for the cluster
    void clearAllImages();
};

} // namespace TLDEDA001
