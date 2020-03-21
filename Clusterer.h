//
// Created by edan on 2020/03/16.
//

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "Cluster.h"


namespace TLDEDA001
{
    class Clusterer{

        //list of images
         std::vector<unsigned char **> images;

         //list of clusters
         std::vector<TLDEDA001::Cluster *> clusters;

        //number of clusters to use
        int numOfClusters;

        public:

        //Constructor
        Clusterer();

        //Parameter Constructor
        Clusterer(const int NumOfClusters);
        
        //Destructor
        ~Clusterer();

        //Read in all images and convert them to grayscale from
        //folder directory "dataset"
       void readImages(const std::string & dataset);

        //returns all images in dataset in greyscale
        std::vector<unsigned char **> getAllImages() const;

        //returns all clusters in a vector
         std::vector<Cluster *> getAllClusters()const;

        //get specific cluster
         Cluster* getCluster(const int index)const;

        //separates images into their respective clusters
         void ClusterImages();

        //operator overloaded for input into a stream in correct format
        friend std::ostream& operator<<(std::ostream&os,const Clusterer & clusterer);


    };

} // namespace TLDEDA001