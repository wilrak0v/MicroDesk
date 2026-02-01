#include "lib.h"

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