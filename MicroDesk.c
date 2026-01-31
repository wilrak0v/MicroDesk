#include <stdio.h>
#include "pico/stdlib.h"

#include "core/screen/screen.h"
#include "core/filesystem/filesystem.h"
#include "core/network/net.h"
#include "core/system.h"

int main()
{
    stdio_init_all();

    if (filesystemReady())
        printf("Filesystem exists and he is ready!\n");
    if (networkReady())
        printf("Network exists and he is ready!\n");
    if (screenReady())
        printf("The screen is ready!\n");
    if (!systemReady()) {
        printf("System isn't ready, we have to abort the program\n");
        exit(1);
    }

    while (true) {
    }
}
