# The first target:
dict2: dict2.o search.o data.o
	gcc -o dict2 dict2.o search.o data.o

dict1: dict1.o search.o data.o
	gcc -o dict1 dict1.o search.o data.o

# Other targets specify how to get the .o files
dict2.o: dict2.c
	gcc -c dict2.c

dict1.o: dict1.c
	gcc -c dict1.c

search.o: search.c search.h
	gcc -c search.c

data.o: data.c data.h
	gcc -c data.c

clean:
	rm -f *.o combination
