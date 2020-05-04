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

    //histogram feature values for the image colours
    std::vector<int> red;

    std::vector<int> green;

    std::vector<int> blue;

    //DEFAULT BINSIZE = 1, WIDTH & HEIGHT = 32
    int binSize, width, height;

    //colour value
    int colourval;

    //true if image has colour
    bool isColour;

    //raw data of image
    std::vector<unsigned char> pixels;

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
    ImageFeature(const std::string &name, std::vector<unsigned char> pic);

    //Parameter Constructor - takes in image in 2D unsigned char array and bin size
    ImageFeature(const std::string &name, std::vector<unsigned char> pic, const int bin);

    //Parameter Constructor - takes in image in 2D unsigned char array and bin size and whether or not there is colour
    ImageFeature(const std::string &name, std::vector<unsigned char> pic, const int bin, const bool colour);

    //Parameter Constructor - takes in image in 2D unsigned char array and bin size as well as width and height of image
    ImageFeature(const std::string &name, std::vector<unsigned char> pic, const int bin, const int width, const int height);

    //Parameter Constructor - takes in image in 2D unsigned char array and bin size as well as width and height of image and and whether or not there is colour
    ImageFeature(const std::string &name, std::vector<unsigned char> pic, const int bin, const int width, const int height, const bool colour);

    //Parameter Constructor - takes in image in 2D unsigned char array and bin size as well as width and height of image and colour value limit and whether or not you use colour
    ImageFeature(const std::string &name, std::vector<unsigned char> pic, const int bin, const int width, const int height, const int colourVal, const bool colour);

    //calculate distance from this image to the parameter image
    float calculateDistance(const std::vector<std::vector<int>> &othermean) const;

    //getter method for Red Hist array
    std::vector<int> getRed() const;

    //getter method for Green Hist array
    std::vector<int> getGreen() const;

    //getter method for Blue Hist array
    std::vector<int> getBlue() const;

    //setter method for Red Hist array
    void setRed(const std::vector<int> &redin);

    //setter method for Green Hist array
    void setGreen(const std::vector<int> &greenin);

    //setter method for Blue Hist array
    void setBlue(const std::vector<int> &bluein);

    //setter method for bin Size
    void setBinSize(const int bin);

    bool getIsColour() const;

    //get name of image
    std::string getName() const;

    //get mean of image
    int getBinSize() const;

    //get width
    int getWidth() const;

    //get height
    int getHeight() const;

    //get get Colour Value
    int getColourVal() const;

    //Get raw data of image
    std::vector<unsigned char> getPixels() const;

    void setClusterID(int id);

    int getClusterID() const;

    //Runs all the imagefeatures through a prewitt or sobel filter thereby highlighting the edges as the most important feature- image preprocessing
    void RunThroughEdgeFilter(const bool sobel);
};

} // namespace TLDEDA001
