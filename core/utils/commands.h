#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdio.h>
#include <string.h>
#include "../screen/screen.h"
#include "../filesystem/filesystem.h"
#include "../network/net.h"
#include "lib.h"

void neofetch();
void info(char args[15]);
void clear();
void help(char args[15]);
void version();
void about();

#endif