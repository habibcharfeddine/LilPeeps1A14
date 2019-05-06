prog:main.o menu.o animation.o  
	gcc main.o menu.o animation.o  -o prog -lSDL -lSDL_ttf -lSDL_image -lSDL_mixer -g
main.o:main.c
	gcc -c main.c -g
menu.o:menu.c
	gcc -c menu.c -g

animation.o:animation.c
	gcc -c animation.c -g


clean:
	rm -fr *.o
mrproper:clean
	rm -f prog
