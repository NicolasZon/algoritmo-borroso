#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <sstream>
#include <omp.h>

using namespace cv;
using namespace std;

// inicial funcion blur
void promedio_actual (int, uchar*DatoSalida);

Mat image, imgBorrosa;
double tam_kernel;
int numero_hilos = 0;
int columna;
int fila;

int main(int n, char* argv[])
{
  
  //verifica los 3 parametros
  if( n <= 3) {
    cout <<" parametros: <ruta img> <tam_kernel> <thread>" << endl;
    return -1;
  }
  
  image = imread( argv[1], 1);
  //verifica si carga la imagen
  if(! image.data ) {
    cout <<  "NO se pudo abrir la imagen" << endl ;
    return -1;
  }
  imgBorrosa = image.clone();
  //carga la imagen para el efecto borroso
  for(int y = 0; y < image.rows; y++){
		for(int x = 0; x < image.cols; x++){
			imgBorrosa.at<uchar>(y,x) = 0.0;
		}
  }
  
  stringstream ss;
	ss << argv[2] ;
	ss >> tam_kernel;
  //veriica el tamano del kernel
  if ((int)tam_kernel %2 == 0){
    cout <<  "Tamano del kernel debe ser impar" << endl ;
    return -1;
  }
  //numero de hilos
  stringstream aa;
  aa << argv[3];
  aa >> numero_hilos;
  fila = image.rows;
  columna = image.cols*image.channels();
  omp_set_num_threads(int(numero_hilos));
  #pragma omp parallel
	{
		int id = omp_get_thread_num();
		int n_threads = omp_get_num_threads();
  
		for(int y = id; y < fila*columna; y=y+n_threads){
		  uchar*DatoSalida = imgBorrosa.ptr<uchar>(y/columna);
		  promedio_actual(y,DatoSalida);
	    
	  }
	}
  
  //namedWindow("copia", 1 );
  //imshow( "copia", imgBorrosa );
  
  //descomentar para guardar imagen en un archivo nuevo
  imwrite( "copia.jpg", imgBorrosa );
 
  waitKey(0);
  return 0;
}

void promedio_actual(int x, uchar*DatoSalida){
  
  float suma=0, sumb=0, sumc=0, suma_peso=0;
  int a=x%(image.cols*image.channels());
  int b=x/(image.cols*image.channels());
  
	for(int k = -tam_kernel; k <= tam_kernel;k++){
	  uchar*DatoSalida =image.ptr<uchar>(b+k);
		for(int j = -tam_kernel; j <=tam_kernel; j++){
		  if (((a + j-3) >= 0 && (a + j-3) <  image.cols*image.channels() )&& ((b + k) >= 0 && (b + k) < image.rows)) {
  			double peso = exp( -(k*k+j*j) / (double)(2*tam_kernel*tam_kernel) ) / (3.141592*2*tam_kernel*tam_kernel);
  			suma = suma + (peso * DatoSalida[a+j*3-3]);
  			sumb = sumb + (peso * DatoSalida[a+j*3-2]);
  			sumc = sumc + (peso * DatoSalida[a+j*3-1]);
  			suma_peso =suma_peso + peso;
		  }
		}
	}
	if( a-3 >=0 )
  {
  	DatoSalida[a-3]= (uchar)floor(suma/suma_peso);
  	DatoSalida[a-2]= (uchar)floor(sumb/suma_peso);
  	DatoSalida[a-1]= (uchar)floor(sumc/suma_peso);
  }
	return;
}
