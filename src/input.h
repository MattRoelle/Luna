#ifndef INPUT_H
#define INPUT_H

#include "types.h"

char input_buffer[32];

luna get_input();
luna push_input(char);

char* read_input(char);

#endif
