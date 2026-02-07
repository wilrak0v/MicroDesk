#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "../utils/lib.h"
#include "../utils/data.h"
#include <stdio.h>
#include <string.h>

enum commands {
    MKDIR,
    TOUCH,
    RM,
    OPEN,
    LEN,
    READ,
    WRITE,
    SEEK,
    CLOSE
};
typedef enum {
    FIL_CLOSED = 0,
    FIL_READ,
    FIL_WRITE,
    FIL_APPEND
} fil_mode;

typedef struct {
    int handle;
    fil_mode mode;
    uint32_t pos;
    uint32_t size;
    uint32_t eof;
    uint32_t error;
    char path[64];
} FIL;

int fs_ready();
extern char* path;

int mkdir(const char *name);
int touch(const char *name);
int rm(const char *name);

int md_fopen(FIL *f, const char *path, const char *mode);
int md_fread(void *ptr, uint32_t size, uint32_t count, FIL *f);
int md_write(const void *ptr, uint32_t size, uint32_t count, FIL *f);
int md_fseek(FIL *f, uint32_t offset);
int md_ftell(FIL *f);
int md_feof(FIL *f);
int md_ferror(FIL *f);
int md_fclose(FIL *f);

#endif