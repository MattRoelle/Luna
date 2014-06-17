flags = -o luna -lncurses -lm -llua -ldl

main: src/*.c
	gcc src/*.c $(flags)
