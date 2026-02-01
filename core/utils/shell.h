#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include "../screen/screen.h"
#include "../filesystem/filesystem.h"
#include "../network/net.h"

// Utils function
void getElements(char command[25], char function[10], char args[15]);
void execute(char command[25]);
void serial_fgets(char *buf, size_t bufsize);

// Shell execution
void neofetch();
void info(char args[15]);
void clear();

#endif