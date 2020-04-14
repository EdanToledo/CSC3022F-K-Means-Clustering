//
// Created by edan on 2020/03/16.
//

#include "Cluster.h"
#include <math.h>
#include <cmath>

//Default Constructor
TLDEDA001::Cluster::Cluster() {}

//Parameter Constructor
TLDEDA001::Cluster::Cluster(ImageFeature* meanfeature)
{

    this->MeanHist = new ImageFeature(*meanfeature);
   
}

//Destructor
TLDEDA001::Cluster::~Cluster()
{
    delete(MeanHist);
    for (int i = 0; i < imageFeatures.size(); i++)
    {
        delete (imageFeatures[i]);
    }
}



//Add an image to this cluster
void TLDEDA001::Cluster::addImage(ImageFeature *Image)
{
    this->imageFeatures.push_back(Image);
}

//Get an image for this cluster
TLDEDA001::ImageFeature *TLDEDA001::Cluster::getImage(int index) const
{
    return this->imageFeatures[index];
}

//Get all images from this cluster
std::vector<TLDEDA001::ImageFeature *> TLDEDA001::Cluster::getAllClusterImages() const
{
    return this->imageFeatures;
}

//Get the mean image  feature of this cluster
TLDEDA001::ImageFeature TLDEDA001::Cluster::getMeanFeature() const
{
    return *this->MeanHist;
}

//calculate new mean based on image features inside this cluster
void TLDEDA001::Cluster::calculateNewMean()
{

    int numOfBins = ((int)(std::ceil((MeanHist->getColourVal()) / (MeanHist->getBinSize()))));

    for (int j = 0; j < numOfBins; j++)
    {
        MeanHist->getHist()[j] = 0;
    }

    for (int i = 0; i < imageFeatures.size(); i++)
    {

        for (int j = 0; j < numOfBins; j++)
        {
            MeanHist->getHist()[j] += imageFeatures[i]->getHist()[j];
        }
    }

    for (int k = 0; k < numOfBins; k++)
    {
        MeanHist->getHist()[k] /= imageFeatures.size();
    }

}

//clears all images for the cluster
void TLDEDA001::Cluster::clearAllImages()
{
    this->imageFeatures.clear();
}