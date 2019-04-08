prog:*.h *.c
	gcc *.h *.c -lSDL -lSDL_ttf -lSDL_image -lSDL_mixer -lm  -o prog -g 
main.o:main.c
	gcc -c main.c -g
menu.o:menu.c
	gcc -c menu.c -g
map.o:map.c
	gcc -c map.c -g
monster.o:monster.c
	gcc -c monster.c -g
input.o:input.c
	gcc -c input.c -g
init.o:init.c
	gcc -c init.c -g
player.o:player.c
	gcc -c player.c -g
draw.o:draw.c
	gcc -c draw.c -g
animation.o:animation.c
	gcc -c animation.c -g
sounds.o:sounds.c
	gcc -c sounds.c -g
font.o:font.c
	gcc -c font.c -g
clean:
	rm -fr *.o
mrproper:clean
	rm -f prog
