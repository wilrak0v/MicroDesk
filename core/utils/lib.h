#ifndef LIB_H
#define LIB_H

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
void serial_fgets(char *buf, size_t bufsize);

#endif