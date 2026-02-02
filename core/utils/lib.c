#include "lib.h"

void stdout_set(stdout_t *dev) {
  stdout_dev = dev;
}

void putchar_std(char c) {
  if (stdout_dev && stdout_dev->putc)
    stdout_dev->putc(c);
}

void print(const char *s) {
  if (stdout_dev && stdout_dev->putc)
    while(*s) stdout_dev->putc(*s++);
}



void serial_fgets(char *buf, size_t bufsize) {
    size_t idx = 0;
    int c;
    while (1) {
        c = getchar();
        if (c == '\r' || c == '\n') {
            buf[idx] = '\0';
            return;
        }
        if (idx < bufsize - 1) {
            buf[idx++] = (char)c;
        }
    }
}