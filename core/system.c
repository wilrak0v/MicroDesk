#include "system.h"

int is_fs = 0;
int is_net = 0;
int is_screen = 0;

stdout_t stdout_uart = {
  .putc = putc_serial
};

void init() {
    stdout_set(&stdout_uart);
    is_fs = fs_ready();
    is_screen = screen_ready();
    is_net = net_ready();
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