all:
	gcc -I src/include -L src/lib -o JeuDeLaVie jeudelavie.c -lmingw32 -lSDL2main -lSDL2