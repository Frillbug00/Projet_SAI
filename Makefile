All:
	gcc -c src/main.c -lm -lglut -lGLU -lGL -o build/main.o
	gcc build/main.o -lm -lglut -lGLU -lGL -o build/main
clean :
	rm build/*