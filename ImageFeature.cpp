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
    colourval = 256;
    hist = new int[(int)(std::ceil(colourval / binSize))];
    width = 32;
    height = 32;
    for (int i = 0; i < ((int)(std::ceil(colourval / binSize))); i++)
    {
        hist[i] = 0;
    }
    this->ClusterId=-1;
    this->mean = 0;
    this->colourval = 256;
    this->isColour=false;
}

//Destructor
TLDEDA001::ImageFeature::~ImageFeature()
{
    delete[] this->hist;
    delete[] this->pixels;
}

//Copy Constructor
TLDEDA001::ImageFeature::ImageFeature(const ImageFeature &rhs)
{
    this->binSize = rhs.binSize;
    this->mean = rhs.mean;
    this->colourval = rhs.colourval;
    this->height = rhs.height;
    this->width = rhs.width;
    this->hist = new int[(int)(std::ceil(colourval / binSize))];
    for (int i = 0; i < (int)(std::ceil(this->colourval / binSize)); i++)
    {
        hist[i] = rhs.hist[i];
    }
    this->pixels = new unsigned char[width * height * 3];
    for (int i = 0; i < width * height * 3; i++)
    {
        this->pixels[i] = rhs.pixels[i];
    }
}

//Move Constructor
TLDEDA001::ImageFeature::ImageFeature(ImageFeature &&rhs)
{
    this->binSize = std::move(rhs.binSize);
    this->mean = std::move(rhs.mean);
    this->colourval = std::move(rhs.colourval);
    this->height = std::move(rhs.height);
    this->width = std::move(rhs.width);
    this->hist = std::move(rhs.hist);
    this->pixels = std::move(rhs.pixels);
}

//Assignment Operator
TLDEDA001::ImageFeature &TLDEDA001::ImageFeature::operator=(const TLDEDA001::ImageFeature &rhs)
{
    this->binSize = rhs.binSize;
    this->mean = rhs.mean;
    this->colourval = rhs.colourval;
    this->height = rhs.height;
    this->width = rhs.width;
    this->hist = new int[(int)(std::ceil(colourval / binSize))];
    for (int i = 0; i < (int)(std::ceil(this->colourval / binSize)); i++)
    {
        hist[i] = rhs.hist[i];
    }
    this->pixels = new unsigned char[width * height * 3];
    for (int i = 0; i < width * height * 3; i++)
    {
        this->pixels[i] = rhs.pixels[i];
    }
}

//Move Assignment Operator
TLDEDA001::ImageFeature &TLDEDA001::ImageFeature::operator=(TLDEDA001::ImageFeature &&rhs)
{
    this->binSize = std::move(rhs.binSize);
    this->mean = std::move(rhs.mean);
    this->colourval = std::move(rhs.colourval);
    this->height = std::move(rhs.height);
    this->width = std::move(rhs.width);
    this->hist = std::move(rhs.hist);
    this->pixels = std::move(rhs.pixels);
}

//Parameter Constructor - takes in image in 2D unsigned char array
TLDEDA001::ImageFeature::ImageFeature(const std::string &name, unsigned char pic[]): TLDEDA001::ImageFeature::ImageFeature(name,pic,1,32,32,256,false)
{
    
}

//Parameter Constructor - takes in image in 2D unsigned char array and bin size
TLDEDA001::ImageFeature::ImageFeature(const std::string &name, unsigned char pic[], const int bin): TLDEDA001::ImageFeature::ImageFeature(name,pic,bin,32,32,256,false)
{
    
    
}

//Parameter Constructor - takes in image in 2D unsigned char array and bin size
TLDEDA001::ImageFeature::ImageFeature(const std::string &name, unsigned char pic[], const int bin,const bool colour): TLDEDA001::ImageFeature::ImageFeature(name,pic,bin,32,32,256,colour)
{
    
}

//Parameter Constructor - takes in image in 2D unsigned char array and bin size as well as width and height of image
TLDEDA001::ImageFeature::ImageFeature(const std::string &name, unsigned char pic[], const int bin, const int width, const int height) : TLDEDA001::ImageFeature::ImageFeature(name,pic,bin,width,height,256,false)
{
}

//Parameter Constructor - takes in image in 2D unsigned char array and bin size as well as width and height of image and which colour
// it is creating a feature for
TLDEDA001::ImageFeature::ImageFeature(const std::string &name, unsigned char pic[], const int bin, const int width, const int height, const bool colour) : TLDEDA001::ImageFeature::ImageFeature(name,pic,bin,width,height,256,colour)
{
}

//Parameter Constructor - takes in image in 2D unsigned char array and bin size as well as width and height of image and colour value limit
TLDEDA001::ImageFeature::ImageFeature(const std::string &name, unsigned char pic[], const int bin, const int width, const int height, const int colourVal,const bool colour)
{
    this->name = name;
    binSize = bin;
    this->width = width;
    this->height = height;
    pixels = pic;
    this->colourval = colourVal;
    this->ClusterId=-1;

    hist = new int[(int)(std::ceil(colourVal / binSize))];
    for (int i = 0; i < ((int)(std::ceil(colourVal / binSize))); i++)
    {
        hist[i] = 0;
    }
    
     if (colour == true)
    {
        for (int i = 0; i < width * height * 3; i ++)
        {
            int index = std::floor(((int)pic[i]) / binSize);
            hist[index] += 1;
        }
    }else
    {
       for (int i = 0; i < width * height * 3; i +=3)
        {
            int index = std::floor(((int)pic[i]) / binSize);
            hist[index] += 1;
        }
    }

    float tempmean = 0;
    for (int i = 0; i < (int)(std::ceil(256 / binSize)); i++)
    {
        tempmean += hist[i] * i * binSize;
    }
    tempmean = tempmean / (width * height);
    this->mean = tempmean;
}

//calculate distance from this image to the parameter image
float TLDEDA001::ImageFeature::calculateDistance(TLDEDA001::ImageFeature othermean) const
{
    int binNumbers = (int)(std::ceil(this->colourval / binSize));
    float runningTotal = 0;
    for (int i = 0; i < binNumbers; i++)
    {
        float diff = hist[i]-othermean.hist[i];
       runningTotal+= pow(diff,2);
    }
    return runningTotal;
}

//setter method for hist array
void TLDEDA001::ImageFeature::setHist(int *histogram)
{
    for (int i = 0; i < ((int)(std::ceil(colourval / binSize))); i++)
    {
        this->hist[i] = histogram[i];
    }
}

//getter method for Hist array
int *TLDEDA001::ImageFeature::getHist()const
{
    return this->hist;
}

//setter method for bin Size
void TLDEDA001::ImageFeature::setBinSize(int bin)
{
    this->binSize = bin;
}

void TLDEDA001::ImageFeature::printHist()const
{
    for (int i = 0; i < ((int)(std::ceil(colourval / binSize))); i++)
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
float TLDEDA001::ImageFeature::getMean() const
{
    return this->mean;
}

//set mean of image
void TLDEDA001::ImageFeature::setMean(const float othermean){
    this->mean = othermean;
}
//get mean of image
int TLDEDA001::ImageFeature::getBinSize() const
{
    return this->binSize;
}

//get width
int TLDEDA001::ImageFeature::getWidth() const { return this->width; }

//get height
int TLDEDA001::ImageFeature::getHeight() const { return this->height; }

unsigned char *TLDEDA001::ImageFeature::getPixels()
{
    return this->pixels;
}

//get get Colour Value
    int TLDEDA001::ImageFeature::getColourVal() const{
        return this->colourval;
    }

    void  TLDEDA001::ImageFeature::setClusterID(int id){
        this->ClusterId = id;
    }

    int  TLDEDA001::ImageFeature::getClusterID()const{return this->ClusterId;}