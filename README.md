# Instructions on how to use program

### Driver file : clustererDriver - makefile creates executable called clusterer 
- to run type in terminal ./clusterer <dataset directory> OPTIONAL FLAGS : [-o output] [-k n] [-bin b] [-color] [-edgefilter1] [-edgefilter2]

#### DEFAULT:

Output will be to console.
Number of clusters is 10.
Bin range is 1.
Colour is Greyscale.
Edgefilter is not used.


### FLAGS: [-o output] [-k n] [-bin b] [-color] [-edgefilter1] [-edgefilter2]

- -o : This flag specifies the output file name for the results of the clustering. It is used by typing -o followed by the name of the output file e.g. -o output.txt
	
- -k : This flag specifies the number of clusters that should be used in the clustering process. It is used by typing -k followed by the number of clusters desired. e.g. -k 10

- -bin : this flag specifies the range for the bins used by the histogram image feature. It is used by typing -bin followed by the number desired. e.g. -bin 4

- -color : this flag specifies whether the user wants to use color in their images to further differentiate images.

- -edgefilter1/2 : these flags implement a prewwit or sobel filter preprocessing to the image. This function only works on greyscale images and highlights edges in the images. 

Edgefilter1 is for prewwit filter and edgefilter2 is for sobel. To use this flag just type -edgefilter1 or -edgefilter2 after the necessary flags.

### PARAMETERS: 
	
\<Dataset Directory\> - this is the name of the directory that contains the images to be clustered.

### Examples on how to run:

./clusterer Gradient_Numbers_PPMS/ -o results.txt -bin 4

./clusterer Gradient_Numbers_PPMS/ -o results.txt -k 5

./clusterer Gradient_Numbers_PPMS/ -color

./clusterer Gradient_Numbers_PPMS/ -edgefilter1



