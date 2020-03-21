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
    class ImageFeature{
        //image name
        std::string name;
        //histogram feature values for the image
        int * hist;
        //DEFAULT BINSIZE = 1, WIDTH & HEIGHT = 32
        int binSize,width,height;
        //image feature mean
        float mean;

        public:

        //Default constructor
        ImageFeature();

        //Destructor
       ~ImageFeature();

        //Parameter Constructor - takes in image in 2D unsigned char array
        ImageFeature(const std::string & name,unsigned char * pic[]);

        //Parameter Constructor - takes in image in 2D unsigned char array and bin size
        ImageFeature(const std::string & name, unsigned char *pic[],const int bin);

        //Parameter Constructor - takes in image in 2D unsigned char array and bin size as well as width and height of image
        ImageFeature(const std::string & name, unsigned char *pic[], const int bin, const int width, const int height);

        //calculate distance from this image to the parameter image
        float calculateDistance(float othermean)const;

        //setter method for pixels array
        void setHist(int *histogram);

        //getter method for Hist array
        int* getHist();

        //setter method for bin Size
        void setBinSize(const int bin);

        //Print hist array
        void printHist();

        //get name of image
        std::string getName()const;

        //get mean of image
        float getMean()const;

        //get mean of image
        int getBinSize()const;



    };

} // namespace TLDEDA001
