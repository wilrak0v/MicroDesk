#include "filesystem.h"

int fs_ready() {
    char line[128];
    print("FS\n");
    if(fgets_non_blocking(line, sizeof(line), 5000000))
        return !strcmp(line, "OK");
    return 0;
}