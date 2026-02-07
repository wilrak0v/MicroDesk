#include "shell.h"

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
    else if (!strcmp(function, "version")) version();
    else if (!strcmp(function, "about")) about();
    else if (!strcmp(function, "mkdir")) ws_mkdir(args);
    else if (!strcmp(function, "touch")) ws_touch(args);
    else if (!strcmp(function, "rm")) ws_rm(args);
    else if (!strcmp(function, "pwd")) pwd();
}