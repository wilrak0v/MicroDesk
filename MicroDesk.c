#include <stdio.h>
#include "pico/stdlib.h"

#include "core/screen/screen.h"
#include "core/filesystem/filesystem.h"
#include "core/network/net.h"
#include "core/utils/shell.h"
#include "core/system.h"

int main()
{
    stdio_init_all();

    if (filesystemReady())
        printf("Filesystem exists and he is ready!\n");
    if (netReady())
        printf("Network exists and he is ready!\n");
    if (!screenReady())
        shell();

    while (true) {
    }
}
