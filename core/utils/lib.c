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

int fgets_non_blocking(char *str, int num, int time) {
    static int index = 0;
    int c = getchar_timeout_us(time);
    while (c != PICO_ERROR_TIMEOUT) {
        if (c == '\r' || c == '\n') {
            str[index] = '\0';
            index = 0;
            return 1;
        } else if (index < num - 1) {
            str[index++] = (char)c;
        }
        c = getchar_timeout_us(time);
    }

    return 0;
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