#pragma once

#include <stdio.h>
#include <string.h>
#include "../screen/screen.h"
#include "../filesystem/filesystem.h"
#include "../network/net.h"
#include "data.h"
#include "lib.h"

void neofetch();
void info(char args[15]);
void clear();
void help(char args[15]);
void version();
void about();
void ws_mkdir(char args[15]);
void ws_touch(char args[15]);
void ws_rm(char args[15]);
void pwd();