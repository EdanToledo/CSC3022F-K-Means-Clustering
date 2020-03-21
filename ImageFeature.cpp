//
// Created by edan on 2020/03/16.
//

#include "ImageFeature.h"
#include <math.h>
#include <cmath>

//Default constructor
TLDEDA001::ImageFeature::ImageFeature()
{
    this->name = "default";
    binSize = 1;

    hist = new int[(int)(std::ceil(256 / binSize))];
    width = 32;
    height = 32;
    for (int i = 0; i < ((int)(std::ceil(256 / binSize))); i++)
    {
        hist[i] = 0;
    }
    
    
    this->mean = 0;
}

//Destructor
TLDEDA001::ImageFeature::~ImageFeature()
{
    delete[] hist;
}

//Parameter Constructor - takes in image in 2D unsigned char array
TLDEDA001::ImageFeature::ImageFeature(const std::string &name, unsigned char *pic[])
{
    this->name = name;
    binSize = 1;
    width = 32;
    height = 32;
    hist = new int[(int)(std::ceil(256 / binSize))];

    for (int i = 0; i < ((int)(std::ceil(256 / binSize))); i++)
    {
        hist[i] = 0;
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            hist[(int)pic[i][j]] += 1;
        }
    }
    float tempmean=0;
    for (int i = 0; i < (int)(std::ceil(256 / binSize)); i++)
    {
       tempmean += hist[i];
    }
    tempmean = tempmean/(int)(std::ceil(256 / binSize));
    this->mean = tempmean;
}

//Parameter Constructor - takes in image in 2D unsigned char array and bin size
TLDEDA001::ImageFeature::ImageFeature(const std::string &name, unsigned char *pic[], const int bin)
{
    this->name = name;
    binSize = bin;
    width = 32;
    height = 32;

    hist = new int[(int)(std::ceil(256 / binSize))];
    for (int i = 0; i < ((int)(std::ceil(256 / binSize))); i++)
    {
        hist[i] = 0;
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int index = std::floor(((int)pic[i][j]) / binSize);

            hist[index] += 1;
        }
    }

    float tempmean=0;
    for (int i = 0; i < (int)(std::ceil(256 / binSize)); i++)
    {
       tempmean += hist[i];
    }
    tempmean = tempmean/(int)(std::ceil(256 / binSize));
    this->mean = tempmean;
}

//Parameter Constructor - takes in image in 2D unsigned char array and bin size as well as width and height of image
TLDEDA001::ImageFeature::ImageFeature(const std::string &name, unsigned char *pic[], const int bin, const int width, const int height)
{
    this->name = name;
    binSize = bin;
    this->width = width;
    this->height = height;

    hist = new int[(int)(std::ceil(256 / binSize))];
    for (int i = 0; i < ((int)(std::ceil(256 / binSize))); i++)
    {
        hist[i] = 0;
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int index = std::floor(((int)pic[i][j]) / binSize);

            hist[index] += 1;
        }
    }

    float tempmean=0;
    for (int i = 0; i < (int)(std::ceil(256 / binSize)); i++)
    {
       tempmean += hist[i];
    }
    tempmean = tempmean/(int)(std::ceil(256 / binSize));
    this->mean = tempmean;
}

//calculate distance from this image to the parameter image
float TLDEDA001::ImageFeature::calculateDistance(float othermean) const {
    return std::pow((othermean- this->mean),2);
}

//setter method for pixels array
void TLDEDA001::ImageFeature::setHist(int *histogram)
{

    for (int i = 0; i < ((int)(std::ceil(256 / binSize))); i++)
    {
        this->hist[i] = histogram[i];
    }
}

//getter method for Hist array
int *TLDEDA001::ImageFeature::getHist()
{
    return this->hist;
}

//setter method for bin Size
void TLDEDA001::ImageFeature::setBinSize(int bin)
{
    this->binSize = bin;
}

void TLDEDA001::ImageFeature::printHist()
{
    for (int i = 0; i < ((int)(std::ceil(256 / binSize))); i++)
    {
        std::cout << this->hist[i] << std::endl;
    }
}

//get name of image
std::string TLDEDA001::ImageFeature::getName() const
{
    return this->name;
}

//get mean of image
float TLDEDA001::ImageFeature::getMean() const {
    return this->mean;
}


        //get mean of image
        int TLDEDA001::ImageFeature::getBinSize()const{
            return this->binSize;
        }