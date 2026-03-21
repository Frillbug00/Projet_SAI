All:
	gcc -c src/vecteur.c -lm -lglut -lGLU -lGL -o build/vecteur.o
	gcc -c src/joueur.c -lm -lglut -lGLU -lGL -o build/joueur.o
	gcc -c src/main.c -lm -lglut -lGLU -lGL -o build/main.o
	gcc build/main.o build/vecteur.o build/joueur.o -lm -lglut -lGLU -lGL -o main
clean :
	rm build/* main