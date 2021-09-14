#To Run
#make -B
#./voronoi1 dataset.csv polygon.txt outfile.txt<split.txt

voronoi1: main.o dataset.o polygon.o split.o region.o
	gcc -Wall -o voronoi1 main.o dataset.o polygon.o split.o region.o

main.o: main.c dataset.h polygon.h
	gcc -Wall -o main.o main.c -c

dataset.o: dataset.h dataset.c
	gcc -Wall -o dataset.o dataset.c -c

polygon.o: polygon.h polygon.c
	gcc -Wall -o polygon.o polygon.c -c

split.o: split.h split.c
	gcc -Wall -o split.o split.c -c

region.o: region.h region.c
	gcc -Wall -o region.o region.c -c
