All:
	gcc -c lib/stb_image.c -lm -lglut -lGLU -lGL -o build/stb_image.h
	gcc -c src/vecteur.c -lm -lglut -lGLU -lGL -o build/vecteur.o
	gcc -c src/joueur.c -lm -lglut -lGLU -lGL -o build/joueur.o
	gcc -c src/ennemies.c -lm -lglut -lGLU -lGL -o build/ennemies.o
	gcc -c src/main.c -lm -lglut -lGLU -lGL -o build/main.o
	gcc build/main.o build/vecteur.o build/joueur.o build/ennemies.o -lm -lglut -lGLU -lGL -o main
clean :
	rm build/* main