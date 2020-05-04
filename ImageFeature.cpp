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

    width = 32;
    height = 32;
    for (int i = 0; i < ((int)(std::ceil(colourval / binSize))); i++)
    {
        red.push_back(0);
        green.push_back(0);
        blue.push_back(0);
    }
    this->ClusterId = -1;

    this->colourval = 256;
    this->isColour = false;
}

//Destructor
TLDEDA001::ImageFeature::~ImageFeature()
{
}

//Copy Constructor
TLDEDA001::ImageFeature::ImageFeature(const ImageFeature &rhs)
{
    this->name = rhs.name;
    this->binSize = rhs.binSize;
    this->colourval = rhs.colourval;
    this->height = rhs.height;
    this->width = rhs.width;
    this->isColour = rhs.isColour;

    std::copy(rhs.red.begin(), rhs.red.end(), std::back_inserter(red));
    std::copy(rhs.green.begin(), rhs.green.end(), std::back_inserter(green));

    std::copy(rhs.blue.begin(), rhs.blue.end(), std::back_inserter(blue));

    std::copy(rhs.pixels.begin(), rhs.pixels.end(), std::back_inserter(pixels));
}

//Move Constructor
TLDEDA001::ImageFeature::ImageFeature(ImageFeature &&rhs)
{
    this->name = std::move(rhs.name);
    this->binSize = std::move(rhs.binSize);
    this->colourval = std::move(rhs.colourval);
    this->isColour = std::move(rhs.isColour);

    this->height = std::move(rhs.height);
    this->width = std::move(rhs.width);
    this->red = std::move(rhs.red);
    this->green = std::move(rhs.green);
    this->blue = std::move(rhs.blue);
    this->pixels = std::move(rhs.pixels);
}

//Assignment Operator
TLDEDA001::ImageFeature &TLDEDA001::ImageFeature::operator=(const TLDEDA001::ImageFeature &rhs)
{
    this->name = rhs.name;
    this->binSize = rhs.binSize;
    this->isColour = rhs.isColour;
    this->colourval = rhs.colourval;
    this->height = rhs.height;
    this->width = rhs.width;

    red.clear();
    green.clear();
    blue.clear();

    std::copy(rhs.red.begin(), rhs.red.end(), std::back_inserter(red));
    std::copy(rhs.green.begin(), rhs.green.end(), std::back_inserter(green));

    std::copy(rhs.blue.begin(), rhs.blue.end(), std::back_inserter(blue));

    this->pixels.clear();

    std::copy(rhs.pixels.begin(), rhs.pixels.end(), std::back_inserter(pixels));
}

//Move Assignment Operator
TLDEDA001::ImageFeature &TLDEDA001::ImageFeature::operator=(TLDEDA001::ImageFeature &&rhs)
{
    this->name = std::move(rhs.name);
    this->binSize = std::move(rhs.binSize);

    this->colourval = std::move(rhs.colourval);
    this->isColour = std::move(rhs.isColour);
    this->height = std::move(rhs.height);
    this->width = std::move(rhs.width);
    this->red = std::move(rhs.red);
    this->green = std::move(rhs.green);
    this->blue = std::move(rhs.blue);
    this->pixels = std::move(rhs.pixels);
}

//Parameter Constructor - takes in image in 2D unsigned char array
TLDEDA001::ImageFeature::ImageFeature(const std::string &name, std::vector<unsigned char> pic) : TLDEDA001::ImageFeature::ImageFeature(name, pic, 1, 32, 32, 256, false)
{
}

//Parameter Constructor - takes in image in 2D unsigned char array and bin size
TLDEDA001::ImageFeature::ImageFeature(const std::string &name, std::vector<unsigned char> pic, const int bin) : TLDEDA001::ImageFeature::ImageFeature(name, pic, bin, 32, 32, 256, false)
{
}

//Parameter Constructor - takes in image in 2D unsigned char array and bin size
TLDEDA001::ImageFeature::ImageFeature(const std::string &name, std::vector<unsigned char> pic, const int bin, const bool colour) : TLDEDA001::ImageFeature::ImageFeature(name, pic, bin, 32, 32, 256, colour)
{
}

//Parameter Constructor - takes in image in 2D unsigned char array and bin size as well as width and height of image
TLDEDA001::ImageFeature::ImageFeature(const std::string &name, std::vector<unsigned char> pic, const int bin, const int width, const int height) : TLDEDA001::ImageFeature::ImageFeature(name, pic, bin, width, height, 256, false)
{
}

//Parameter Constructor - takes in image in 2D unsigned char array and bin size as well as width and height of image and which colour
// it is creating a feature for
TLDEDA001::ImageFeature::ImageFeature(const std::string &name, std::vector<unsigned char> pic, const int bin, const int width, const int height, const bool colour) : TLDEDA001::ImageFeature::ImageFeature(name, pic, bin, width, height, 256, colour)
{
}

//Parameter Constructor - takes in image in 2D unsigned char array and bin size as well as width and height of image and colour value limit
TLDEDA001::ImageFeature::ImageFeature(const std::string &name, std::vector<unsigned char> pic, const int bin, const int width, const int height, const int colourVal, const bool colour)
{
    this->name = name;
    this->binSize = bin;
    this->width = width;
    this->height = height;
    this->pixels = pic;
    this->colourval = colourVal;
    this->ClusterId = -1;
    this->isColour = colour;
    red = std::vector<int>(((int)(std::ceil(colourVal / binSize))),0);
    green = std::vector<int>(((int)(std::ceil(colourVal / binSize))),0);
    blue = std::vector<int>(((int)(std::ceil(colourVal / binSize))),0);
   

    for (int i = 0; i < width * height * 3; i += 3)
    {

        int index1 = std::floor(((int)pic[i]) / binSize);
        int index2 = std::floor(((int)pic[i + 1]) / binSize);
        int index3 = std::floor(((int)pic[i + 2]) / binSize);

        this->red[index1] += 1;
        this->green[index2] += 1;
        this->blue[index3] += 1;
    }

    

}

//calculate distance from this image to the parameter image
float TLDEDA001::ImageFeature::calculateDistance(const std::vector<std::vector<int>> &othermean) const
{
     

    int binNumbers = (int)(std::ceil(this->colourval / binSize));

    float runningTotal = 0;

    if (this->isColour)
    {
        for (int i = 0; i < binNumbers; i++)
        {

            runningTotal += pow(this->red[i] - othermean[0][i], 2.0);

            runningTotal += pow(this->green[i] - othermean[1][i], 2.0);

            runningTotal += pow(this->blue[i] - othermean[2][i], 2.0);
        }
    }
    else
    {

        for (int i = 0; i < binNumbers; i++)
        {

            float diff1 = red[i] - othermean[0][i];

            runningTotal += (pow(diff1, 2));
        }
    }

    return (runningTotal);
}

//getter method for Hist array
std::vector<int> TLDEDA001::ImageFeature::getRed() const
{
    return this->red;
}

//getter method for Hist array
std::vector<int> TLDEDA001::ImageFeature::getGreen() const
{
    return this->green;
}

//getter method for Hist array
std::vector<int> TLDEDA001::ImageFeature::getBlue() const
{
    return this->blue;
}

//setter method for bin Size
void TLDEDA001::ImageFeature::setBinSize(int bin)
{
    this->binSize = bin;
}

//get name of image
std::string TLDEDA001::ImageFeature::getName() const
{
    return this->name;
}

//get bin size
int TLDEDA001::ImageFeature::getBinSize() const
{
    return this->binSize;
}

//get width
int TLDEDA001::ImageFeature::getWidth() const { return this->width; }

//get height
int TLDEDA001::ImageFeature::getHeight() const { return this->height; }

std::vector<unsigned char> TLDEDA001::ImageFeature::getPixels() const
{
    return this->pixels;
}

//get get Colour Value
int TLDEDA001::ImageFeature::getColourVal() const
{
    return this->colourval;
}

void TLDEDA001::ImageFeature::setClusterID(int id)
{
    this->ClusterId = id;
}

int TLDEDA001::ImageFeature::getClusterID() const { return this->ClusterId; }

//setter method for Red Hist array
void TLDEDA001::ImageFeature::setRed(const std::vector<int> &redin)
{
    this->red.clear();
    std::copy(redin.begin(), redin.end(), std::back_inserter(this->red));
}

//setter method for Green Hist array
void TLDEDA001::ImageFeature::setGreen(const std::vector<int> &greenin)
{
    this->green.clear();
    std::copy(greenin.begin(), greenin.end(), std::back_inserter(this->green));
}

//setter method for Blue Hist array
void TLDEDA001::ImageFeature::setBlue(const std::vector<int> &bluein)
{
    this->blue.clear();
    std::copy(bluein.begin(), bluein.end(), std::back_inserter(this->blue));
}

//Run the images through a prewitt or sobel filter - image preprocessing
void TLDEDA001::ImageFeature::RunThroughEdgeFilter(const bool sobel)
{

    // Prewitt matrices value
    int GX[3][3] =
        {
            {-1, 0, 1},
            {-1, 0, 1},
            {-1, 0, 1}};

    int GY[3][3] =
        {
            {-1, -1, -1},
            {0, 0, 0},
            {1, 1, 1}};

    if (sobel)
    {
        //Sobel matrices value
        GX[0][0] = -1;
        GX[0][1] = 0;
        GX[0][2] = 1;

        GX[1][0] = -2;
        GX[1][1] = 0;
        GX[1][2] = 2;

        GX[2][0] = -1;
        GX[2][1] = 0;
        GX[2][2] = 1;

        GY[0][0] = -1;
        GY[0][1] = -2;
        GY[0][2] = -1;

        GY[1][0] = 0;
        GY[1][1] = 0;
        GY[1][2] = 0;

        GY[2][0] = 1;
        GY[2][1] = 2;
        GY[2][2] = 1;
    }

    int gx, gy;

    for (int i = 0; i < width * height * 3; i += 3)
    {
        gx = this->pixels[i] * GX[0][0] + this->pixels[i + 1] * GX[0][1] + this->pixels[i + 2] * GX[0][2] + this->pixels[i + width * 3] * GX[1][0] + this->pixels[i + width * 3 + 1] * GX[1][1] + this->pixels[i + width * 3 + 2] * GX[1][2] + this->pixels[i + width * 3 + width * 3] * GX[2][0] + this->pixels[i + width * 3 + width * 3 + 1] * GX[2][1] + this->pixels[i + width * 3 + width * 3 + 2] * GX[2][2];

        gy = this->pixels[i] * GY[0][0] + this->pixels[i + 1] * GY[0][1] + this->pixels[i + 2] * GY[0][2] + this->pixels[i + width * 3] * GY[1][0] + this->pixels[i + width * 3 + 1] * GY[1][1] + this->pixels[i + width * 3 + 2] * GY[1][2] + this->pixels[i + width * 3 + width * 3] * GY[2][0] + this->pixels[i + width * 3 + width * 3 + 1] * GY[2][1] + this->pixels[i + width * 3 + width * 3 + 2] * GY[2][2];

        if (sqrt(pow(gx, 2) + pow(gy, 2)) > 255)
        {
            this->pixels[i] = ((unsigned char)255);
            this->pixels[i + 1] = ((unsigned char)255);
            this->pixels[i + 2] = ((unsigned char)255);
        }
        else if (sqrt(pow(gx, 2) + pow(gy, 2)) < 0)
        {
            this->pixels[i] = ((unsigned char)0);
            this->pixels[i + 1] = ((unsigned char)0);
            this->pixels[i + 2] = ((unsigned char)0);
        }
        else
        {
            this->pixels[i] = ((unsigned char)sqrt(pow(gx, 2) + pow(gy, 2)));
            this->pixels[i + 1] = ((unsigned char)sqrt(pow(gx, 2) + pow(gy, 2)));
            this->pixels[i + 2] = ((unsigned char)sqrt(pow(gx, 2) + pow(gy, 2)));
        }
    }
}

bool TLDEDA001::ImageFeature::getIsColour() const { return this->isColour; }