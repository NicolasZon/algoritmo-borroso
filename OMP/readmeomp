Para la correcta ejecución del programa es necesario instalar la librería OpenCV, la siguiente configuración es basada en linux.

•	sudo apt-get update
•	sudo apt-get install libopencv-dev python-opencv 

Una vez instalado necesitamos crear un CMakeLists que es un ejecutable creado a partir de archivos de código fuente, es necesario incluir aca las librerias de OMP y OPENCV.
Luego una vez se tengan el programa y el CMakeLists necesitamos compilar para la perfecta ejecución del programa. 

Los pasos para compilar son:
•	cmake .   (solo se hace una vez para guardar la configuración del programa, es necesario que este el espacio con el punto)
•	make (se usa cada vez que modificamos el código fuente)

Ya cuando tengamos el ambiente configurado solo nos basta correr el programa de la siguiente forma:

./name ruta kernel hilos 

Donde name es el nombre del programa
Ruta se refiere en donde está ubicada la imagen, en nuestro caso está en la misma carpeta ejemplo seria 720.jpg 
Kernel corresponde al número del tamaño del kernel, es decir las veces que el algoritmo blur va a ser ejecutado siendo este impar, 3, 5, 7, ... 
Hilos se refiere al número de hilos que vamos asignar teniendo en cuenta que si ponemos 1 es la forma secuencial y números pares para la forma paralela, 2, 4, 6, …

Adicionalmente tenemos un star.sh donde corremos todos lo casos de prueba de forma automática. Para la ejecución del sh usamos: bash name.sh 
Donde bash es una palabra reservada de Linux 
Y name.sh es el nombre que queremos ponerle al ejecutable.
