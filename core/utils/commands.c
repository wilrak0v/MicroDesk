#include "commands.h"

void neofetch() {
    print(".-.-.-..-.,-. \tRPi Pico 2\n");
    print("| | | || . <  \tCPU: 150 MHz\n");
    print("`-----'`-'`-' \tRAM: 520Kb\n#\n");
}

void info(char args[15]) {
    print("# ");
    if (strcmp(args, "screen") == 0) {
        if (screenReady()) print("Screen OK\n");
        else print("Screen NO\n");
    }
    else if (strcmp(args, "network") == 0 || strcmp(args, "net") == 0) {
        if (netReady()) print("Net OK\n");
        else print("Net NO\n");
    }
    else if (strcmp(args, "sd") == 0) {
        if (filesystemReady()) print("SD \033[32mOK[0m\n");
        else print("SD NO\n");
    }

    else {
        print("ERROR: info takes 1 argument or your module doesn't exist.\n# EXAMPLE: info screen\n");
    }
}

void clear() {
    for (char i=0; i<20; i++) print("\n");
}

void version() {
    print("# MicrOS v0.000000001\tWork in progress...\n");
}

void about() {
    print(".-.-.-..-.,-. \n");
    print("| | | || . <  \n");
    print("`-----'`-'`-' \n");
    print("# MicroDesk - Simple Microcomputer based on RPi Pico 2.\n");
}