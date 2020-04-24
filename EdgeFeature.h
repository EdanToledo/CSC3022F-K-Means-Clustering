//
// Created by edan on 2020/04/18.
//

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>


namespace TLDEDA001
{
class EdgeFeature
{
   std::vector<unsigned char> pixelEdges;

public:

    EdgeFeature();

    EdgeFeature(unsigned char * pixels);
    
    EdgeFeature(unsigned char * pixels,int width,int height);

    EdgeFeature(unsigned char * pixels,int width,int height,bool sobel);

    std::vector<unsigned char> getEdgeImage();

};

} 

// namespace TLDEDA001
