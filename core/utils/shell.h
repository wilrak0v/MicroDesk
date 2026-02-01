#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include "commands.h"
#include "luastd.h"
#include "lib.h"

// Utils function
void getElements(char command[25], char function[10], char args[15]);
void execute(char command[25]);

#endif