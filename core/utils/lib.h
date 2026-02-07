#pragma once

#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>

// Outputs
typedef struct {
  void (*putc)(char c);
} stdout_t;

static stdout_t *stdout_dev;
void stdout_set(stdout_t *dev);

void putchar_std(char c);
void print(const char *s);


// Inputs
void uart_write_bytes(const void *buf, int len);
int uart_read_bytes(void *buf, int len, int timeout_us);
int fgets_non_blocking(char *str, int num, int time);
void serial_fgets(char *buf, size_t bufsize);