
#include "EdgeFeature.h"
#include <math.h>

TLDEDA001::EdgeFeature::EdgeFeature() {}

TLDEDA001::EdgeFeature::EdgeFeature(unsigned char *pixels) : TLDEDA001::EdgeFeature::EdgeFeature(pixels, 32, 32) {}

TLDEDA001::EdgeFeature::EdgeFeature(unsigned char *pixels, int width, int height) : TLDEDA001::EdgeFeature::EdgeFeature(pixels, 32, 32, false) {}

TLDEDA001::EdgeFeature::EdgeFeature(unsigned char *pixels, int width, int height, bool sobel)
{

   

    int GX[3][3] = // Prewitt matrices value
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
        GX[0][0]=-1;
        GX[0][1]=0;
        GX[0][2]=1;

        GX[1][0]=-2;
        GX[1][1]=0;
        GX[1][2]=2;

        GX[2][0]=-1;
        GX[2][1]=0;
        GX[2][2]=1;


        GY[0][0] =-1;
        GY[0][1] =-2;
        GY[0][2] =-1;

        GY[1][0] =0;
        GY[1][1] =0;
        GY[1][2] =0;

        GY[2][0] =1;
        GY[2][1] =2;
        GY[2][2] =1;

/*
        int GX[3][3] = 
            {
                {-1, 0, 1},
                {-2, 0, 2},
                {-1, 0, 1}};
                
         int GY[3][3] =
            {
                {-1, -2, -1},
                {0, 0, 0},
                {1, 2, 1}};
       */
      
       
    }
    
    int gx, gy;

    for (int i = 0; i < width * height * 3; i +=3)
    {
        gx = pixels[i] * GX[0][0] + pixels[i + 1] * GX[0][1] + pixels[i + 2] * GX[0][2] + pixels[i + width * 3] * GX[1][0] + pixels[i + width * 3 + 1] * GX[1][1] + pixels[i + width * 3 + 2] * GX[1][2] + pixels[i + width * 3 + width * 3] * GX[2][0] + pixels[i + width * 3 + width * 3 + 1] * GX[2][1] + pixels[i + width * 3 + width * 3 + 2] * GX[2][2];

        gy = pixels[i] * GY[0][0] + pixels[i + 1] * GY[0][1] + pixels[i + 2] * GY[0][2] + pixels[i + width * 3] * GY[1][0] + pixels[i + width * 3 + 1] * GY[1][1] + pixels[i + width * 3 + 2] * GY[1][2] + pixels[i + width * 3 + width * 3] * GY[2][0] + pixels[i + width * 3 + width * 3 + 1] * GY[2][1] + pixels[i + width * 3 + width * 3 + 2] * GY[2][2];

           if (sqrt(pow(gx, 2) + pow(gy, 2)) > 255)
        {
            this->pixelEdges.push_back((unsigned char)255);
        }
        else if (sqrt(pow(gx, 2) + pow(gy, 2)) < 0)
        {
            this->pixelEdges.push_back((unsigned char)0);
        }
        else
        {
            this->pixelEdges.push_back((unsigned char)sqrt(pow(gx, 2) + pow(gy, 2)));
        }
    }
}

std::vector<unsigned char> TLDEDA001::EdgeFeature::getEdgeImage() { return this->pixelEdges; }