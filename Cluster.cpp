//
// Created by edan on 2020/03/16.
//

#include "Cluster.h"
#include <math.h>
#include <cmath>

//Default Constructor
TLDEDA001::Cluster::Cluster() {}

//Parameter Constructor
TLDEDA001::Cluster::Cluster(const ImageFeature &meanfeature)
{

    histograms.push_back(std::vector<int>(meanfeature.getRed()));
    histograms.push_back(std::vector<int>(meanfeature.getGreen()));
    histograms.push_back(std::vector<int>(meanfeature.getBlue()));
    binSize = meanfeature.getBinSize();
    colourval = meanfeature.getColourVal();
}

//Add an image to this cluster
void TLDEDA001::Cluster::addImage(const ImageFeature &Image)
{
    this->imageFeatures.push_back(Image);
}

//Get an image from this cluster
TLDEDA001::ImageFeature TLDEDA001::Cluster::getImage(const int index) const
{
    return this->imageFeatures[index];
}

//Get all images from this cluster
const std::vector<TLDEDA001::ImageFeature> & TLDEDA001::Cluster::getAllClusterImages() const
{
    return this->imageFeatures;
}

//Get the mean image feature of this cluster
const std::vector<std::vector<int>> & TLDEDA001::Cluster::getMeanFeature() const
{
    return this->histograms;
}

//calculate new mean based on image features inside this cluster
void TLDEDA001::Cluster::calculateNewMean()
{

    int numOfBins = ((int)(std::ceil((colourval) / binSize)));
    std::vector<int> tempRed(numOfBins);
    std::vector<int> tempGreen(numOfBins);
    std::vector<int> tempBlue(numOfBins);
    
    for (int j = 0; j < numOfBins; j++)
    {
        tempRed[j] = 0;
        tempGreen[j] = 0;
        tempBlue[j] = 0;
    }

    for (int i = 0; i < imageFeatures.size(); i++)
    {

        for (int j = 0; j < numOfBins; j++)
        {
            tempRed[j] += imageFeatures[i].getRed()[j];

            tempGreen[j] += imageFeatures[i].getGreen()[j];

            tempBlue[j] += imageFeatures[i].getBlue()[j];
        }
    }

    for (int k = 0; k < numOfBins; k++)
    {
        if (imageFeatures.size() > 0)
        {

            tempRed[k] /= imageFeatures.size();
            tempGreen[k] /= imageFeatures.size();
            tempBlue[k] /= imageFeatures.size();
        }
    }

    histograms[0] = tempRed;
    histograms[1] = tempGreen;
    histograms[2] = tempBlue;
}

//clears all images for the cluster
void TLDEDA001::Cluster::clearAllImages()
{
    this->imageFeatures.clear();
}

//delete an Image
void TLDEDA001::Cluster::DelImage(const int index)
{
    imageFeatures.erase(imageFeatures.begin() + index);
}
