flags = -ggdb -o luna -lncurses

main: src/*.c
	gcc src/*.c $(flags)
