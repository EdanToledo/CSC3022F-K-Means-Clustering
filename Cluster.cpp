//
// Created by edan on 2020/03/16.
//

#include "Cluster.h"
#include <math.h>
#include <cmath>

//Default Constructor
TLDEDA001::Cluster::Cluster() {}

//Parameter Constructor
TLDEDA001::Cluster::Cluster(ImageFeature meanfeature)
{
    
    this->mean = meanfeature.getMean();
}

//Parameter Constructor
TLDEDA001::Cluster::Cluster(float mean)
{

    this->mean = mean;
}

//Destructor
TLDEDA001::Cluster::~Cluster()
{
    for (int i = 0; i < imageFeatures.size(); i++)
    {
        delete(imageFeatures[i]);
    }
}

//Set mean feature
void TLDEDA001::Cluster::setMean(float mean)
{
    this->mean = mean;
}

//Add an image to this cluster
void TLDEDA001::Cluster::addImage(ImageFeature* Image)
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
float TLDEDA001::Cluster::getMean() const
{
    return this->mean;
}

//calculate new mean based on image features inside this cluster
void TLDEDA001::Cluster::calculateNewMean()
{
    
    float temp = 0;
    for (int i = 0; i < imageFeatures.size(); i++)
    {
        temp += imageFeatures[i]->getMean();
    }
    temp = temp / imageFeatures.size();
    this->mean = temp;
}

//clears all images for the cluster
    void TLDEDA001::Cluster::clearAllImages(){
        this->imageFeatures.clear();
    }