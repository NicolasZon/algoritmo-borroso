#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

void prom_punto (int, int);

Mat image, imgBorrosa;
double tam_kernel;


int main(int n, char* argv[])
{
  if( n <= 2) {
    cout <<" parametros: <ruta img> <tam_kernel>" << endl;
    return -1;
  }
  
  image = imread(argv[1], 2);
 
  if(! image.data ) {
    cout <<  "NO se pudo abrir la imagen" << endl ;
    return -1;
  }
  imgBorrosa = image.clone();
  
  stringstream ss;
	ss << argv[2] ;
	ss >> tam_kernel;
  
  for(int y = tam_kernel; y < image.rows - tam_kernel; y++){
    for(int x = tam_kernel; x < 3*image.cols - tam_kernel; x++){
      prom_punto(x,y);
    }
  }

  //namedWindow("copia", 1 );
  //imshow( "copia", imgBorrosa );
  
  //descomentar para guardar imagen en un archivo nuevo
  imwrite( "copia.jpg", imgBorrosa );

  waitKey(0);
  return 0;
}

void prom_punto(int x, int y){
  
  float sum, sum_peso;
	sum = 0;
	sum_peso= 0;
	for(int k = -tam_kernel; k <= tam_kernel;k++){
		for(int j = -tam_kernel; j <=tam_kernel; j++){
			double peso = exp( -(k*k+j*j) / (double)(2*tam_kernel*tam_kernel) ) / (3.141592*2*tam_kernel*tam_kernel);
			sum +=  peso * image.at<uchar>(y - j, x - k);
			sum_peso += peso;

		}
	}
	imgBorrosa.at<uchar>(y,x) = floor(sum/sum_peso);//floor( sum/( pow(tam_kernel*2.+1.,2)) );
	return;
}