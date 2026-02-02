#include "system.h"

stdout_t stdout_uart = {
  .putc = putc_serial
};

void init() {
    stdout_set(&stdout_uart);
}

void shell() {
    printf("Welcome into the WilShell!\n");
    char command[25];
    while(1) {
        serial_fgets(command, sizeof command);
        execute(command);
    }
}

void putc_serial(char c) {
  putchar(c);
  // uart_send_blocking(c);
}