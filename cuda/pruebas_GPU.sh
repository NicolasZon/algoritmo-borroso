# for para el tamano del kernel
for kernel in 3 5 7 9 11 13
do
	# for para el numero de hilos con respecto al kernel
	for NumHilos in 2 6 12 16
	do
		
		printf "Resultados con # $NumHilos hilos\n" 
		
		printf "Tiempo para imagen de 720p con un kernel de $kernel\n" 
		time ./borrosoCUDA 720.jpg $kernel $NumHilos
		sleep 5

		printf "Tiempo para imagen de 1080p con un kernel de $kernel\n" 
		time ./borrosoCUDA 1080.jpg $kernel $NumHilos
		sleep 5

		printf "Tiempo para imagen de 4k con un kernel de $kernel\n" 
		time ./borrosoCUDA 4k.jpg $kernel $NumHilos
		sleep 5
		
	done 
done




