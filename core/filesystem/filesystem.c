#include "filesystem.h"

char* path = "/";

int fs_ready() {
    char line[128];
    print("FS\n");
    if(fgets_non_blocking(line, sizeof(line), 5000000))
        return !strcmp(line, "OK");
    return 0;
}

int mkdir(const char* name) {
    if(!is_fs) return -1;
    printf("%d %s%s\n", MKDIR, path, name);
    int c = getchar_timeout_us(100000);
    if (c == PICO_ERROR_TIMEOUT) return -1;
    return c - '0';          // 1 si c'est bon, et tout le reste sera false
}

int touch(const char* name) {
    if(!is_fs) return -1;
    printf("%d %s%s\n", TOUCH, path, name);
    int c = getchar_timeout_us(100000);
    if (c == PICO_ERROR_TIMEOUT) return -1;
    return c - '0';
}

int rm(const char* name) {
    if(!is_fs) return -1;
    printf("%d %s%s\n", RM, path, name);
    int c = getchar_timeout_us(100000);
    if (c == PICO_ERROR_TIMEOUT) return -1;
    return c - '0';
}


int storage_open(const char *path) {
    printf("%d %s\n", OPEN, path);
    int c = getchar_timeout_us(100000);
    if (c == PICO_ERROR_TIMEOUT) return -1;
    return c - '0';
}

int storage_get_size(int handle) {
    printf("%d %d\n", LEN, handle);

    char resp[16];
    if (fgets_non_blocking(resp, sizeof(resp), 100000) <= 0)
        return -1;

    int size;
    if (sscanf(resp, "1 %d", &size) != 1)
        return -1;

    return size;
}

int storage_read(int handle, void *buf, uint32_t len) {
    printf("%d %d %lu\n", READ, handle, (unsigned long)len);

    char resp[16];
    if (fgets_non_blocking(resp, sizeof(resp), 100000) != 0)
        return -1;

    uint32_t recv_len;
    if (sscanf(resp, "1 %lu", &recv_len) != 1)
        return -1;

    if (recv_len > len)
        recv_len = len;

    if (uart_read_bytes(buf, recv_len, 200000) != (int)recv_len)
        return -1;

    return recv_len;
}

int storage_close(int handle) {
    printf("%d %d", CLOSE, handle);
    int c = getchar_timeout_us(100000);
    if (c == PICO_ERROR_TIMEOUT) return -1;
    return c - '0';
}


int md_fopen(FIL *f, const char *path, const char* mode) {
    if (!f || !path || !mode || !is_fs) return -1;
    int handle = storage_open(path);
    if (handle < 0) return -1;

    f->handle = handle;
    f->pos = 0;
    f->eof = 0;
    f->error = 0;

    strncpy(f->path, path, sizeof(f->path) - 1);

    if (mode[0] == 'r')
        f->mode = FIL_READ;
    else if (mode[0] == 'w')
        f->mode = FIL_WRITE;
    else if (mode[0] == 'a')
        f->mode = FIL_APPEND;

    f->size = storage_get_size(handle);
    return 0;
}

int md_fread(void *ptr, uint32_t size, uint32_t count, FIL *f) {
    if (!f || f->mode != FIL_READ || size < 0)
        return -1;

    uint32_t bytes = size * count;
    int response = storage_read(f->handle, ptr, bytes);

    if (response < 0) {
        f->error = 1;
        return -1;
    }

    f->pos += response;
    if (f->pos >= f->size)
        f->eof = 1;

    return response / size;
}

int md_write(const void *ptr, uint32_t size, uint32_t count, FIL *f) {
    if (!f || (f->mode != FIL_WRITE && f->mode != FIL_APPEND) || size < 0)
        return -1;
    uint32_t bytes = size * count;

    printf("%d %d %lu\n", WRITE, f->handle, (unsigned long)bytes);
    uart_write_bytes(ptr, bytes);

    char resp[16];
    if (fgets_non_blocking(resp, sizeof(resp), 200000) != 0) {
        f->error = 1;
        return -1;
    }

    uint32_t written;
    if (sscanf(resp, "1 %lu", &written) != 1) {
        f->error = 1;
        return -1;
    }

    f->pos += written;
    if (f->pos > f->size)
        f->size = f->pos;

    return written / size;
}

int md_fseek(FIL *f, uint32_t offset) {
    if (!f) return -1;

    printf("%d %d %lu\n", SEEK, f->handle, (unsigned long)offset);

    char resp[8];
    if (fgets_non_blocking(resp, sizeof(resp), 100000) != 0)
        return -1;

    if (resp[0] != '1') {
        f->error = 1;
        return -1;
    }

    f->pos = offset;
    f->eof = 0;
    return 0;
}

int md_ftell(FIL *f) {
    if (!f) return 0;
    return f->pos;
}

int md_feof(FIL *f) {
    if (!f) return 1;
    return f->eof;
}

int md_ferror(FIL *f) {
    if (!f) return 1;
    return f->error;
}

int md_fclose(FIL *f) {
    if (!f) return -1;
    storage_close(f->handle);
    f->handle = -1;
    f->mode = FIL_CLOSED;
    return 0;
}