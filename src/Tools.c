#include "Tools.h"
#include <stdlib.h>
#include <string.h>
#include "globalDefs.h"

char* readLine(FILE* file){
        static char* buffer = NULL;

        /*Clean function when file is NULL*/
        if(file == NULL){
                if(buffer != NULL){
                        free(buffer);
                }
                buffer = NULL;
                return NULL;
        }

        if(buffer != NULL){
                free(buffer);
                buffer = NULL;
        }

        unsigned int buffer_size = 0;
        unsigned int bytes_read = 0;
        unsigned int i;

        do{
                buffer_size += BLOCK_SIZE;

                buffer = realloc(buffer,buffer_size);
                if(buffer == NULL) return NULL;
                for(i = buffer_size-BLOCK_SIZE;i < buffer_size;i++) buffer[i] = 0;

                fgets(buffer+bytes_read,BLOCK_SIZE,file);
                bytes_read += BLOCK_SIZE-1; /*if we read less chars than that we exit the loop*/
        }while((feof(file) == 0) && (strchr(buffer,'\n') == NULL));

        return buffer;
}
