//
// Created by edan on 2020/03/16.
//

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace TLDEDA001
{
class ImageFeature
{
    //image name
    std::string name;
    //histogram feature values for the image
    int *hist;
    //DEFAULT BINSIZE = 1, WIDTH & HEIGHT = 32
    int binSize, width, height;
    //image feature mean
    float mean;
    //colour value
    int colourval;

    //true if image has colour
    bool isColour;

    //raw data of image
    unsigned char *pixels;

    //Cluster ID
    int ClusterId;

public:
    //Default constructor
    ImageFeature();

    //Destructor
    ~ImageFeature();

    //Copy Constructor
    ImageFeature(const ImageFeature &rhs);

    //Move Constructor
    ImageFeature(ImageFeature &&rhs);

    //Assignment Operator
    ImageFeature &operator=(const ImageFeature &rhs);

    //Move Assignment Operator
    ImageFeature &operator=(ImageFeature &&rhs);

    //Parameter Constructor - takes in image in 2D unsigned char array
    ImageFeature(const std::string &name, unsigned char pic[]);

    //Parameter Constructor - takes in image in 2D unsigned char array and bin size
    ImageFeature(const std::string &name, unsigned char pic[], const int bin);

    //Parameter Constructor - takes in image in 2D unsigned char array and bin size and whether or not there is colour
    ImageFeature(const std::string &name, unsigned char pic[], const int bin, const bool colour);

    //Parameter Constructor - takes in image in 2D unsigned char array and bin size as well as width and height of image
    ImageFeature(const std::string &name, unsigned char pic[], const int bin, const int width, const int height);

    //Parameter Constructor - takes in image in 2D unsigned char array and bin size as well as width and height of image and and whether or not there is colour
    ImageFeature(const std::string &name, unsigned char pic[], const int bin, const int width, const int height, const bool colour);

    //Parameter Constructor - takes in image in 2D unsigned char array and bin size as well as width and height of image and colour value limit and whether or not you use colour
    ImageFeature(const std::string &name, unsigned char pic[], const int bin, const int width, const int height, const int colourVal ,const bool colour);

    //calculate distance from this image to the parameter image
    float calculateDistance(TLDEDA001::ImageFeature othermean) const;

    //setter method for hist array
    void setHist(int *histogram);

    //getter method for Hist array
    int *getHist();

    //setter method for bin Size
    void setBinSize(const int bin);

    //Print hist array
    void printHist();

    //get name of image
    std::string getName() const;

    //get mean of image
    float getMean() const;

    //set mean of image
    void setMean(const float othermean);

    //get mean of image
    int getBinSize() const;

    //get width
    int getWidth() const;

    //get height
    int getHeight() const;

    //get get Colour Value
    int getColourVal() const;

    //Get raw data of image
    unsigned char *getPixels();

    void setClusterID(int id);

    int getClusterID();
};

} // namespace TLDEDA001
