# for para el tamano del kernel
for kernel in 3 5 7 9 11 13 15
do
	
	printf "Tiempo para imagen de 720p con un kernel de $kernel \n" 
	time ./borroso 720.jpg $kernel
	

	printf "Tiempo para imagen de 1080p con un kernel de $kernel  \n" 
	time ./borroso 1080.jpg $kernel
	

	printf "Tiempo para imagen de 4k con un kernel de $kernel  \n" 
	time ./borroso 4k.jpg $kernel 

done

