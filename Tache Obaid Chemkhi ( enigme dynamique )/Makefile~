prog:*.h *.c
	gcc *.h *.c -lSDL -lSDL_ttf -lSDL_image -lSDL_mixer -lm  -o prog -g 
main.o:main.c
	gcc -c main.c -g
main_enigme.o:main_enigme.c
	gcc -c main_enigme.c -g
enigme1.o:enigme1.c
	gcc -c enigme1.c -g
random.o:random.c
	gcc -c random.c -g
clean:
	rm -fr *.o
mrproper:clean
	rm -f prog
