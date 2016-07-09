all: first_zapusk second_zapusk
first_zapusk: first_zapusk.o 
	
first_zapusk.o: File2.c bin_sem.c 
	gcc File1.c bin_sem.c -o first_zapusk
second_zapusk: second_zapusk.o
	 
second_zapusk.o: File1.c bin_sem.c
	gcc File2.c bin_sem.c -o second_zapusk
clean:
	rm -f *.o first_zapusk second_zapusk
