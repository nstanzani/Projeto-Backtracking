all:

	@gcc -std=c99 -c main.c
	@gcc -std=c99 -c Lista.c
	@gcc -std=c99 -c grafolista.c
	@gcc main.o Lista.o grafolista.o -o executar

run:

	@./executar