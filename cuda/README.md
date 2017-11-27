Algoritmo blur 
Para la correcta ejecución del programa es necesario instalar la librería OpenCV, la siguiente configuración es basada en linux.

•	sudo apt-get update
•	sudo apt-get install libopencv-dev python-opencv 
Es necesario tener una tarjeta gráfica Nvidia con cuda para poder ejecutar el programa. 
Se debe instalar cuda y seguimos lo que está en esta guía: http://www.nvidia.es/object/cuda-parallel-computing-es.html
Una vez instalado parte del ambiente necesitamos crear un Makefile que es un ejecutable creado a partir de archivos de código fuente, para hacer este archivo se tomó como base el de los ejemplos que nos trae esta herramienta.  En el Makefile tiene la configuración de la compilación del programa, pero este programa depende de la instalación de cuda entonces necesitamos agregar unas variables al path. Nos ubicamos en la siguiente ruta:  /usr/local/cuda-7.5 y ejecutamos las siguientes líneas de comando: 
•	export PATH=/usr/local/cuda-7.5/bin${PATH:+:${PATH}}
•	export LD_LIBRARY_PATH=/usr/local/cuda-7.5/lib64{LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}}
•	export LD_LIBRARY_PATH=/usr/local/cuda/lib64{LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}}
Para ejecutar el programa usamos
./name ruta kernel hilos 
Donde name es el nombre del programa
Ruta se refiere en donde está ubicada la imagen, en nuestro caso está en la misma carpeta ejemplo seria 720.jpg 
Kernel corresponde al número del tamaño del kernel, es decir las veces que el algoritmo blur va a ser ejecutado siendo este impar, 3, 5, 7, ..., 15
Hilos se refiere al número de hilos que vamos asignar dependiendo a los cores de nuestra GPU, en este caso usamos múltiplos de 192 hasta 1152.
Adicionalmente tenemos un star.sh donde corremos todos lo casos de prueba de forma automática. Para la ejecución del sh usamos: bash name.sh 
Donde bash es una palabra reservada de Linux 
Y name.sh es el nombre que queremos ponerle al ejecutable.
