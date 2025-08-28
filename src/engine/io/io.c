#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#include "../util.h"
#include "io.h"


// 20 Mib, can probably change this to higher value without issue
// Check your target platform.
#define IO_READ_CHUNK_SIZE 2097152
#define IO_READ_ERROR_GENERAL "Error reading file: %s,. errno: %d\n"
#define IO_READ_ERROR_MEMORY "Not enough free memory to read file: %s\n"

File io_file_read(const char *path){
    File file = { .is_valid = false};

    File *fp = (File *)fopen(path, "rb");
    if(!fp || ferror((FILE*)fp)){
        ERROR_RETURN(file, IO_READ_ERROR_GENERAL, path, errno);
    }

    char *data = NULL;
    char *tmp;
    size_t used = 0;
    size_t size = 0;
    size_t n;

    while(true){
        if (used + IO_READ_CHUNK_SIZE + 1 > size){
            size = used + IO_READ_CHUNK_SIZE +1;

            if(size <= used){
                free(data);
                ERROR_RETURN(file, "Input file too large: %s\n", path);
            }

            tmp = realloc(data, size);
            if(!tmp){
                free(data);
                ERROR_RETURN(file, IO_READ_ERROR_MEMORY, path);
            }
            data = tmp;
        }
        
        n = fread(data + used, 1, IO_READ_CHUNK_SIZE, (FILE*)fp);
        if (n ==0)
            break;

        used += n;
    }
    if(ferror((FILE*)fp)){
        free(data);
        ERROR_RETURN(file, IO_READ_ERROR_GENERAL, path, errno);
    }

    tmp = realloc(data, used + 1);
    if(!tmp){
        free(data);
        ERROR_RETURN(file, IO_READ_ERROR_MEMORY, path);
    }
    data = tmp;
    data[used] = 0;
    
    file.data = data;
    file.len = used;
    file.is_valid = true;

    return file;
}


int  io_file_write(void *buffer, size_t size, const char *path){
    File *fp = (File*)fopen(path, "wb");
    if (!fp || ferror((FILE*)fp))
        ERROR_RETURN(1, "Cannot write file: %s.\n", path);

    size_t chunks_written = fwrite(buffer, size, 1, (FILE*)fp);

    fclose((FILE*)fp);

    if(chunks_written!=1)
        ERROR_RETURN(1,"write error. Expected 1 chunk, got %zu.\n", chunks_written);

    return 0;
}
















