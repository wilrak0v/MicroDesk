#pragma once

#include "core/screen/screen.h"
#include "core/filesystem/filesystem.h"
#include "core/network/net.h"
#include "utils/shell.h"
#include "utils/lib.h"
#include "utils/data.h"
#include <string.h>
#include <stdio.h>

void init();
void putc_serial(char c);
void shell();

extern stdout_t stdout_uart;