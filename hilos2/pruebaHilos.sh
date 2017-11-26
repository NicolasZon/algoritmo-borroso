# for para el tamano del kernel
for kernel in 3 5 7 9 11 13 15
do
	# for para el numero de hilos con respecto al kernel
	for NumHilos in 1 2 4 6 8 12 16
	do
		
		
		printf "Tiempo para imagen de 720p con un kernel de $kernel y con # $NumHilos hilos \n" 
		time ./borroso 720.jpg $kernel $NumHilos
		

		printf "Tiempo para imagen de 1080p con un kernel de $kernel y con # $NumHilos hilos \n" 
		time ./borroso 1080.jpg $kernel $NumHilos
		

		printf "Tiempo para imagen de 4k con un kernel de $kernel y con # $NumHilos hilos \n" 
		time ./borroso 4k.jpg $kernel $NumHilos
		
		
	done 
done


