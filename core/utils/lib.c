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


void uart_write_bytes(const void *buf, int len) {
    const uint8_t *p = buf;
    for (int i = 0; i < len; i++) {
        putchar_raw(p[i]);   // ou uart_putc_raw()
    }
}

int uart_read_bytes(void *buf, int len, int timeout_us) {
    uint8_t *p = buf;
    int received = 0;
    absolute_time_t start = get_absolute_time();

    while (received < len) {
        int c = getchar_timeout_us(0);

        if (c >= 0) {
            p[received++] = (uint8_t)c;
        }

        if (absolute_time_diff_us(start, get_absolute_time()) > timeout_us)
            return -1;
    }

    return received;
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