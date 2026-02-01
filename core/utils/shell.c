#include "shell.h"

void serial_fgets(char *buf, size_t bufsize) {
    size_t idx = 0;
    int c;

    while (1) {
        c = getchar();   // BLOQUANT

        if (c == '\r' || c == '\n') {
            buf[idx] = '\0';
            return;
        }

        if (idx < bufsize - 1) {
            buf[idx++] = (char)c;
        }
        // sinon on ignore le surplus
    }
}

void getElements(char command[25], char function[10], char args[15]) {
    int i = 0;
    int j = 0;

    while (i < 25 && j < 9 && command[i] != ' ' && command[i] != '\0' && command[i] != '\n') {
        function[j++] = command[i++];
    }
    function[j] = '\0';

    while (command[i] == ' ') i++;

    j = 0;
    while (i < 25 && j < 14 && command[i] != '\n' && command[i] != '\0') {
        args[j++] = command[i++];
    }
    args[j] = '\0';
}

void execute(char command[25]) {
    char function[10];
    char args[15];
    getElements(command, function, args);
    function[strcspn(function, "\n")] = '\0';
    args[strcspn(args, "\n")] = '\0';

    if (strcmp(function, "neofetch") == 0) neofetch();
    else if (strcmp(function, "info") == 0) info(args);
    else if (strcmp(function, "clear") == 0 || !strcmp(function, "cls")) clear();
    else if (strcmp(function, "lua") == 0) luaInter();
}


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

void luaInter() {
    lua_State *lua;
    lua = lua_wrapper_new();
    char script[40];
    while(1) {
        printf("You can write your command just down\n");
        serial_fgets(script, sizeof script);
        int err = lua_dostring(lua, script);
        if (err) printf("ERROR: your script doesn't work I think.\n");
    }
}