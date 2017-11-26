# for para el tamano del kernel
for kernel in 3 5 7 9 11 13 15
do
	# for para el numero de hilos con respecto al kernel
	for NumHilos in 128 256 512 768 1024
	do
		
		
		printf "Tiempo para imagen de 720p con un kernel de $kernel y con # $NumHilos hilos \n" 
		time ./borrosoCUDA 720.jpg $kernel $NumHilos
		

		printf "Tiempo para imagen de 1080p con un kernel de $kernel y con # $NumHilos hilos \n" 
		time ./borrosoCUDA 1080.jpg $kernel $NumHilos
		

		printf "Tiempo para imagen de 4k con un kernel de $kernel y con # $NumHilos hilos \n" 
		time ./borrosoCUDA 4k.jpg $kernel $NumHilos
		
		
	done 
done


