#include "system.h"

void shell() {
    printf("Welcome into the WilShell!\n");
    char command[25];
    while(1) {
        serial_fgets(command, sizeof command);
        execute(command);
    }
}