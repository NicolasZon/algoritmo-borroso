#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <cstdio>
#include <atomic>
#include <queue>
#include <cmath>
#include <sstream>
#include <thread>

using namespace cv;
using namespace std;

void promedio_actual (int, int);
void disponibilidad_cola(void);
//boleano en falso para el bloqueo
atomic_flag bloqueo = ATOMIC_FLAG_INIT;
Mat image, imgBorrosa;
double tam_kernel;

queue<pair<int,int>> aux_cola;

int main(int n, char* argv[])
{
  int numero_hilos = 0;
  //verifica los 3 parametros
  if( n <= 3) {
    cout <<" parametros: <ruta img> <tam_kernel> <thread>" << endl;
    return -1;
  }
  
  image = imread( argv[1], 2);
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
  //ingresar puntos en la cola
  for(int y = tam_kernel; y < image.rows - tam_kernel; y++){
		for(int x = tam_kernel; x < image.cols - tam_kernel; x++){
			aux_cola.push( make_pair(x,y) );
		}
  }

 //creacion de hilos
  vector<thread> hilos;
  for(int i = 0; i < numero_hilos ; i++){
  	hilos.push_back(thread(disponibilidad_cola));
  }
  

  for(auto &t: hilos){
  	t.join();
  }
  //namedWindow("copia", 1 );
  //imshow( "copia", imgBorrosa );
  
  //descomentar para guardar imagen en un archivo nuevo
  imwrite( "copia.jpg", imgBorrosa );
  //borrar los hilos
  hilos.erase(hilos.begin()+1,hilos.begin()+numero_hilos);
  waitKey(0);
  return 0;
}

void disponibilidad_cola (){
	while(aux_cola.size() > 1){
		while(bloqueo.test_and_set()){}
		pair<int,int> p = aux_cola.front();
		aux_cola.pop();
		bloqueo.clear();
		promedio_actual(p.first,p.second);
	}
	return;
}

void promedio_actual(int x, int y){
  
  float suma, suma_peso;
	suma = 0;
	suma_peso= 0;
	for(int k = -tam_kernel; k <= tam_kernel;k++){
		for(int j = -tam_kernel; j <=tam_kernel; j++){
			double peso = exp( -(k*k+j*j) / (double)(2*tam_kernel*tam_kernel) ) / (3.141592*2*tam_kernel*tam_kernel);
			suma +=  peso * image.at<uchar>(y - j, x - k);
			suma_peso += peso;

		}
	}
	imgBorrosa.at<uchar>(y,x) = floor(suma/suma_peso);//floor( suma/( pow(tam_kernel*2.+1.,2)) );
	return;
}
