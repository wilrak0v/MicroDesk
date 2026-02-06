#include <stdio.h>
#include "pico/stdlib.h"

#include "core/screen/screen.h"
#include "core/filesystem/filesystem.h"
#include "core/network/net.h"
#include "core/utils/shell.h"
#include "core/system.h"
#include "core/utils/lib.h"

int main()
{
    stdio_init_all();
    sleep_ms(1000);
    print("System Ready\n");

    init();
    if (filesystemReady())
        print("Filesystem exists and he is ready!\n");
    if (netReady())
        print("Network exists and he is ready!\n");
    if (!screenReady())
        shell();

    while (true) {
        filesystemReady();
    }
}
