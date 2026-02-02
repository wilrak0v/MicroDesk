#ifndef SYSTEM_H
#define SYSTEM_H

#include "utils/shell.h"
#include "utils/lib.h"
#include <string.h>
#include <stdio.h>

void init();
void putc_serial(char c);
void shell();

extern stdout_t stdout_uart;

#endif