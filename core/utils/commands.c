#include "commands.h"

void neofetch() {
    printf(".-.-.-..-.,-. \tRPi Pico 2\n");
    printf("| | | || . <  \tCPU: 150 MHz\n");
    printf("`-----'`-'`-' \tRAM: 520Kb\n#\n");
}

void info(char args[15]) {
    printf("# ");
    if (strcmp(args, "screen") == 0) {
        if (screenReady()) printf("Screen OK\n");
        else printf("Screen NO\n");
    }
    else if (strcmp(args, "network") == 0 || strcmp(args, "net") == 0) {
        if (netReady()) printf("Net OK\n");
        else printf("Net NO\n");
    }
    else if (strcmp(args, "sd") == 0) {
        if (filesystemReady()) printf("SD \033[32mOK[0m\n");
        else printf("SD NO\n");
    }

    else {
        printf("ERROR: info takes 1 argument or your module doesn't exist.\n# EXAMPLE: info screen\n");
    }
}

void clear() {
    for (char i=0; i<20; i++) printf("\n");
}

void help(char args[15]) {
    if (!strcmp(args, "info")) printf("# Usage: info <modules>\n");
    else if(!strcmp(args, "neofetch")) printf("# Draw some infos about the project\n");
    else if(!strcmp(args, "lua")) printf("# Start Lua Interpretor, write exit() to quit it\n");
    else if(!strcmp(args, "clear")) printf("# Clear the screen\n");
    else printf("ERROR: command \"%s\" doesn't exist", args);
}

void version() {
    printf("# MicrOS v0.000000001\tWork in progress...\n");
}

void about() {
    printf(".-.-.-..-.,-. \n");
    printf("| | | || . <  \n");
    printf("`-----'`-'`-' \n");
    printf("# MicroDesk - Simple Microcomputer based on RPi Pico 2.\n");
}